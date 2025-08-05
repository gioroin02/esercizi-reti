#include "../exports.hpp"

#include "../../tcp/exports.hpp"
#include "../../pax/storage/exports.hpp"

#include <stdio.h>

static const str8 SERVER_PATH = pax_str8("./data/http_server");

static const str8 SERVER_ARG_PORT = pax_str8("--port=");
static const str8 SERVER_ARG_PATH = pax_str8("--path=");

struct Server
{
    Socket_TCP socket = 0;

    u16  port = 8000;
    str8 path = SERVER_PATH;
};

struct Session
{
    Socket_TCP socket = 0;

    HTTP_Request_Reader  reader = {};
    HTTP_Response_Writer writer = {};

    HTTP_Heading heading = {};
    buf8         content = {};
};

b32
http_server_on_get(Arena* arena, Server* server, Session* session);

b32
http_server_on_post(Arena* arena, Server* server, Session* session);

b32
http_server_fallback(Arena* arena, Server* server, Session* session);

b32
http_server_on_multipart_form_data(Arena* arena, Server* server, Session* session, str8 payload);

b32
http_server_on_application_form_url_encoded(Arena* arena, Server* server, Session* session);

int
main(int argc, char** argv)
{
    Arena arena = system_reserve(128);

    if (system_network_start() == 0) return 1;

    Server server = {};

    if (argc != 1) {
        Format_Options opts = format_options_simple(10);

        for (usiz i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server.port);
            }

            if (str8_starts_with(arg, SERVER_ARG_PATH) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PATH);
                arg = str8_trim_spaces(arg);

                server.path = str8_copy(&arena, arg);
            }
        }
    }

    server.socket = server_tcp_start(&arena, server.port, address_any(ADDRESS_TYPE_IP4));

    if (server.socket == 0) return 1;

    usiz offset = arena_offset(&arena);

    while (1) {
        Session session = {};

        session.socket = session_tcp_open(&arena, server.socket);
        session.reader = http_request_reader_init(&arena, 4 * MEMORY_KIB);
        session.writer = http_response_writer_init(&arena, 4 * MEMORY_KIB);

        session.heading = http_request_heading(&session.reader, &arena, session.socket);

        usiz payload = http_heading_get_content_length(&session.heading, 0);

        if (payload != 0)
            session.content = http_request_content(&session.reader, &arena, payload, session.socket);

        /* Begin debug */

        printf(DEBUG " Heading (%llu):\n", session.heading.inner.size);

        for (usiz i = 0; i < session.heading.inner.size; i += 1) {
            str8 key   = array_get_or(&session.heading.key,   i, pax_str8(""));
            str8 value = array_get_or(&session.heading.value, i, pax_str8(""));

            printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
                pax_as(int, key.length), key.memory,
                pax_as(int, value.length), value.memory);
        }

        printf(DEBUG " Content (%llu)\n", session.content.size);

        /* End debug */

        str8 method = http_heading_get_method(&session.heading, pax_str8(""));
        b32  state  = 0;

        if (str8_is_equal(method, HTTP_METHOD_GET) != 0)
            state = http_server_on_get(&arena, &server, &session);

        if (str8_is_equal(method, HTTP_METHOD_POST) != 0)
            state = http_server_on_post(&arena, &server, &session);

        if (state == 0) http_server_fallback(&arena, &server, &session);

        session_tcp_close(session.socket);

        arena_rewind(&arena, offset);
    }

    server_tcp_stop(server.socket);

    system_network_stop();
}

b32
http_server_on_get(Arena* arena, Server* server, Session* session)
{
    str8 resource = http_heading_get_resource(&session->heading, pax_str8(""));

    HTTP_Heading params = http_parse_resource(arena, &resource);

    resource = str8_trim_prefix(resource, pax_str8("/"));

    printf(INFO " Requested resource " BLU("'%.*s'") "\n",
        pax_as(int, resource.length), resource.memory);

    /* Begin debug */

    printf(DEBUG " Params (%llu):\n", params.inner.size);

    for (usiz i = 0; i < params.inner.size; i += 1) {
        str8 key   = array_get_or(&params.key,   i, pax_str8(""));
        str8 value = array_get_or(&params.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_as(int, key.length), key.memory,
            pax_as(int, value.length), value.memory);
    }

    /* End debug */

    if (resource.length == 0) resource = pax_str8("index.html");

    File_Attribs attribs = file_attribs(arena, server->path, resource);

    if (file_size(&attribs) <= 0)
        printf(ERROR " Unable to locate resource\n");

    buf8 buffer = buf8_reserve(arena, file_size(&attribs));

    if (buffer.length != 0) {
        File file = file_open(arena, server->path, resource, FILE_PERM_READ);

        if (file != 0) {
            if (file_read(file, &buffer) != 0) {
                printf(INFO " Responding with content of " BLU("'%.*s'") "\n",
                    pax_as(int, resource.length), resource.memory);
            }
        } else
            printf(ERROR " Unable to open file for reading\n");

        file_close(file);
    }

    str8 type   = pax_str8("");
    str8 length = str8_from_usiz(arena, format_options_simple(10), buffer.size);

    if (str8_ends_with(resource, pax_str8(".html")) != 0) type = MIME_TEXT_HTML;
    if (str8_ends_with(resource, pax_str8(".js"))   != 0) type = MIME_TEXT_JAVASCRIPT;
    if (str8_ends_with(resource, pax_str8(".css"))  != 0) type = MIME_TEXT_CSS;
    if (str8_ends_with(resource, pax_str8(".csv"))  != 0) type = MIME_TEXT_CSV;
    if (str8_ends_with(resource, pax_str8(".ico"))  != 0) type = MIME_IMAGE_VND_MICROSOFT_ICON;
    if (str8_ends_with(resource, pax_str8(".json")) != 0) type = MIME_APPLICATION_JSON;

    http_response_write_start(&session->writer, HTTP_VERSION_1_1,
        HTTP_STATUS_OK, HTTP_MESSAGE_OK);

    if (type.length != 0 && str8_is_equal(length, pax_str8("0")) == 0) {
        http_response_write_header(&session->writer, HTTP_HEADER_CONTENT_TYPE, type);
        http_response_write_header(&session->writer, HTTP_HEADER_CONTENT_LENGTH, length);
    }

    http_response_write_content(&session->writer, &buffer);
    http_response_write(&session->writer, session->socket);

    return 1;
}

b32
http_server_on_post(Arena* arena, Server* server, Session* session)
{
    str8 content_type = http_heading_get_content_type(&session->heading, pax_str8(""));

    HTTP_Heading content_args = http_parse_content_type(arena, &content_type);

    /* Begin debug */

    printf(DEBUG " Content Args (%llu):\n", content_args.inner.size);

    for (usiz i = 0; i < content_args.inner.size; i += 1) {
        str8 key   = array_get_or(&content_args.key,   i, pax_str8(""));
        str8 value = array_get_or(&content_args.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_as(int, key.length), key.memory,
            pax_as(int, value.length), value.memory);
    }

    /* End debug */

    if (str8_is_equal(content_type, MIME_MULTIPART_FORM_DATA) != 0) {
        str8 boundary = {};

        if (hash_map_get(&content_args, pax_str8("boundary"), &boundary) == 0) {
            http_response_write_start(&session->writer, HTTP_VERSION_1_1,
                HTTP_STATUS_BAD_REQUEST, HTTP_MESSAGE_BAD_REQUEST);

            http_response_write(&session->writer, session->socket);

            return 1;
        }

        str8 start = str8_chain(arena, pax_str8("--"), boundary);
        str8 stop  = str8_chain(arena, start, pax_str8("--"));

        str8 string = buf8_read_str8_head(&session->content,
            arena, session->content.size);

        string = str8_slice_since_first(string, start);
        string = str8_slice_until_first(string, stop);
        string = str8_trim_spaces(string);

        return http_server_on_multipart_form_data(arena, server, session, string);
    }

    if (str8_is_equal(content_type, MIME_APPLICATION_FORM_URL_ENCODED) != 0)
        return http_server_on_application_form_url_encoded(arena, server, session);

    http_response_write_start(&session->writer, HTTP_VERSION_1_1,
        HTTP_STATUS_I_AM_A_TEAPOT, HTTP_MESSAGE_I_AM_A_TEAPOT);

    http_response_write(&session->writer, session->socket);

    return 1;
}

b32
http_server_on_multipart_form_data(Arena* arena, Server* server, Session* session, str8 payload)
{
    HTTP_Heading payload_args = http_parse_multipart(arena, &payload);

    /* Begin debug */

    printf(DEBUG " Multipart Args (%llu):\n", payload_args.inner.size);

    for (usiz i = 0; i < payload_args.inner.size; i += 1) {
        str8 key   = array_get_or(&payload_args.key,   i, pax_str8(""));
        str8 value = array_get_or(&payload_args.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_as(int, key.length), key.memory,
            pax_as(int, value.length), value.memory);
    }

    /* End debug */

    str8 contdisp = {};

    if (hash_map_get(&payload_args, HTTP_HEADER_CONTENT_DISP, &contdisp) == 0) {
        http_response_write_start(&session->writer, HTTP_VERSION_1_1,
            HTTP_STATUS_BAD_REQUEST, HTTP_MESSAGE_BAD_REQUEST);

        http_response_write(&session->writer, session->socket);

        return 1;
    }

    HTTP_Heading contdisp_args = http_parse_content_disp(arena, &contdisp);

    /* Begin debug */

    printf(DEBUG " Content Disposition Args (%llu):\n", contdisp_args.inner.size);

    for (usiz i = 0; i < contdisp_args.inner.size; i += 1) {
        str8 key   = array_get_or(&contdisp_args.key,   i, pax_str8(""));
        str8 value = array_get_or(&contdisp_args.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_as(int, key.length), key.memory,
            pax_as(int, value.length), value.memory);
    }

    /* End debug */

    str8 name = {};

    if (hash_map_get(&contdisp_args, pax_str8("filename"), &name) == 0) {
        http_response_write_start(&session->writer, HTTP_VERSION_1_1,
            HTTP_STATUS_BAD_REQUEST, HTTP_MESSAGE_BAD_REQUEST);

        http_response_write(&session->writer, session->socket);

        return 1;
    }

    name = str8_slice_since_first(name, pax_str8("\""));
    name = str8_slice_until_first(name, pax_str8("\""));
    name = str8_trim_spaces(name);

    File file = file_open_new(arena, server->path, name, FILE_PERM_WRITE);

    if (file != 0) {
        buf8 buffer = buf8_full(payload.memory, payload.length);

        if (file_write(file, &buffer) != 0) {
            printf(INFO " Wrote content to " BLU("'%.*s'") "\n",
                pax_as(int, name.length), name.memory);

            file_close(file);

            http_response_write_start(&session->writer, HTTP_VERSION_1_1,
                HTTP_STATUS_OK, HTTP_MESSAGE_OK);

            http_response_write(&session->writer, session->socket);

            return 1;
        }
    }

    printf(ERROR " Unable to create new file for writing\n");

    http_response_write_start(&session->writer, HTTP_VERSION_1_1,
        HTTP_STATUS_UNPROCESSABLE_CONTENT, HTTP_MESSAGE_UNPROCESSABLE_CONTENT);

    http_response_write(&session->writer, session->socket);

    return 1;
}

b32
http_server_on_application_form_url_encoded(Arena* arena, Server* server, Session* session)
{
    str8 payload = buf8_read_str8_head(&session->content,
        arena, session->content.size);

    HTTP_Heading params = http_parse_url_encoded(arena, payload);

    /* Begin debug */

    printf(DEBUG " Params (%llu):\n", params.inner.size);

    for (usiz i = 0; i < params.inner.size; i += 1) {
        str8 key   = array_get_or(&params.key,   i, pax_str8(""));
        str8 value = array_get_or(&params.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_as(int, key.length), key.memory,
            pax_as(int, value.length), value.memory);
    }

    /* End debug */

    http_response_write_start(&session->writer, HTTP_VERSION_1_1,
        HTTP_STATUS_OK, HTTP_MESSAGE_OK);

    http_response_write(&session->writer, session->socket);

    return 1;
}

b32
http_server_fallback(Arena* arena, Server* server, Session* session)
{
    http_response_write_start(&session->writer, HTTP_VERSION_1_1,
        HTTP_STATUS_METHOD_NOT_ALLOWED, HTTP_MESSAGE_METHOD_NOT_ALLOWED);

    http_response_write(&session->writer, session->socket);

    return 1;
}
