#include "tcp/exports.hpp"
#include "http/exports.hpp"

#include "pax/storage/exports.hpp"

#include <stdio.h>

b32
http_server_on_get(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer);

b32
http_server_on_post(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer);

b32
http_server_on_multipart_form_data(Arena* arena, HTTP_Heading* heading, str8 multipart, HTTP_Response_Writer* writer);

b32
http_server_on_application_form_url_encoded(Arena* arena, HTTP_Heading* heading, str8 application, HTTP_Response_Writer* writer);

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer);

static const str8 SERVER_DATA_PATH = pax_str8("./data/http_server");

static const str8 SERVER_ARG_PORT = pax_str8("--port=");

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(128);

    if (system_network_start() == 0) return 1;

    u16 server_port = 8000;

    if (argc != 1) {
        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server_port);
            }
        }
    }

    Socket_TCP server = server_tcp_start(&arena,
        server_port, address_any(ADDRESS_KIND_IP4));

    if (server == 0) return 1;

    uptr offset = arena_offset(&arena);

    while (1) {
        Socket_TCP session = session_tcp_open(&arena, server);

        HTTP_Request_Reader  reader = http_request_reader_init(&arena, 4 * MEMORY_KIB);
        HTTP_Response_Writer writer = http_response_writer_init(&arena, 4 * MEMORY_KIB);

        HTTP_Heading heading = http_request_heading(&reader, &arena, session);

        buf8 content = {};
        uptr payload = http_heading_get_content_length(&heading, 0);

        if (payload != 0)
            content = http_request_content(&reader, &arena, payload, session);

        /* Begin debug */

        printf(DEBUG " Heading (%llu):\n", heading.inner.size);

        for (uptr i = 0; i < heading.inner.size; i += 1) {
            str8 key   = array_get_or(&heading.key,   i, pax_str8(""));
            str8 value = array_get_or(&heading.value, i, pax_str8(""));

            printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
                pax_cast(int, key.length), key.memory,
                pax_cast(int, value.length), value.memory);
        }

        printf(DEBUG " Content (%llu)\n", content.size);

        /* End debug */

        str8 method = http_heading_get_method(&heading, pax_str8(""));
        b32  state  = 0;

        if (str8_is_equal(method, HTTP_METHOD_GET) != 0)
            state = http_server_on_get(&arena, &heading, &content, &writer);

        if (str8_is_equal(method, HTTP_METHOD_POST) != 0)
            state = http_server_on_post(&arena, &heading, &content, &writer);

        if (state == 0) http_server_fallback(&arena, &heading, &content, &writer);

        http_response_write(&writer, session);

        session_tcp_close(session);

        arena_rewind(&arena, offset);
    }

    server_tcp_stop(server);

    system_network_stop();
}

b32
http_server_on_get(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer)
{
    str8 fallback = pax_str8("not_found.html");
    str8 resource = http_heading_get_resource(heading, pax_str8(""));

    HTTP_Heading params = http_parse_resource(arena, &resource);

    resource = str8_trim_prefix(resource, pax_str8("/"));

    printf(INFO " Requested resource " BLU("'%.*s'") "\n",
        pax_cast(int, resource.length), resource.memory);

    /* Begin debug */

    printf(DEBUG " Params (%llu):\n", params.inner.size);

    for (uptr i = 0; i < params.inner.size; i += 1) {
        str8 key   = array_get_or(&params.key,   i, pax_str8(""));
        str8 value = array_get_or(&params.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_cast(int, key.length), key.memory,
            pax_cast(int, value.length), value.memory);
    }

    /* End debug */

    if (resource.length == 0) resource = pax_str8("index.html");

    File_Props properties = {};

    if (file_props(&properties, arena, SERVER_DATA_PATH, resource) == 0) {
        resource = fallback;

        if (file_props(&properties, arena, SERVER_DATA_PATH, resource) == 0)
            printf(ERROR " Unable to locate resource and fallback\n");
    }

    buf8 buffer = buf8_reserve(arena, file_size(&properties));

    if (buffer.length != 0) {
        File file = file_open(arena, SERVER_DATA_PATH, resource, FILE_PERM_READ);

        if (file != 0) {
            if (file_read(file, &buffer) != 0) {
                printf(INFO " Responding with content of " BLU("'%.*s'") "\n",
                    pax_cast(int, resource.length), resource.memory);
            }
        } else
            printf(ERROR " Unable to open file for reading\n");

        file_close(file);
    }

    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_OK, HTTP_MESSAGE_OK);

    http_response_write_content(writer, &buffer);

    return 1;
}

b32
http_server_on_post(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer)
{
    str8 content_type = http_heading_get_content_type(heading, pax_str8(""));

    HTTP_Heading content_args = http_parse_content_type(arena, &content_type);

    /* Begin debug */

    printf(DEBUG " Content Args (%llu):\n", content_args.inner.size);

    for (uptr i = 0; i < content_args.inner.size; i += 1) {
        str8 key   = array_get_or(&content_args.key,   i, pax_str8(""));
        str8 value = array_get_or(&content_args.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_cast(int, key.length), key.memory,
            pax_cast(int, value.length), value.memory);
    }

    /* End debug */

    if (str8_is_equal(content_type, MIME_MULTIPART_FORM_DATA) != 0) {
        str8 boundary = {};

        if (hash_map_get(&content_args, pax_str8("boundary"), &boundary) == 0) {
            http_response_write_start(writer, HTTP_VERSION_1_1,
                HTTP_STATUS_BAD_REQUEST, HTTP_MESSAGE_BAD_REQUEST);

            return 1;
        }

        str8 start = str8_chain(arena, pax_str8("--"), boundary);
        str8 stop  = str8_chain(arena, start, pax_str8("--"));

        str8 string = str8_make(content->memory, content->size);

        string = str8_slice_since_first(string, start);
        string = str8_slice_until_first(string, stop);
        string = str8_trim_spaces(string);

        return http_server_on_multipart_form_data(arena, heading, string, writer);
    }

    if (str8_is_equal(content_type, MIME_APPLICATION_FORM_URL_ENCODED) != 0) {
        str8 string = str8_make(content->memory, content->size);

        return http_server_on_application_form_url_encoded(arena, heading, string, writer);
    }

    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_I_AM_A_TEAPOT, HTTP_MESSAGE_I_AM_A_TEAPOT);

    return 1;
}

b32
http_server_on_multipart_form_data(Arena* arena, HTTP_Heading* heading, str8 multipart, HTTP_Response_Writer* writer)
{
    HTTP_Heading multipart_args = http_parse_multipart(arena, &multipart);

    /* Begin debug */

    printf(DEBUG " Multipart Args (%llu):\n", multipart_args.inner.size);

    for (uptr i = 0; i < multipart_args.inner.size; i += 1) {
        str8 key   = array_get_or(&multipart_args.key,   i, pax_str8(""));
        str8 value = array_get_or(&multipart_args.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_cast(int, key.length), key.memory,
            pax_cast(int, value.length), value.memory);
    }

    /* End debug */

    str8 contdisp = {};

    if (hash_map_get(&multipart_args, HTTP_HEADER_CONTENT_DISP, &contdisp) == 0) {
        http_response_write_start(writer, HTTP_VERSION_1_1,
            HTTP_STATUS_BAD_REQUEST, HTTP_MESSAGE_BAD_REQUEST);

        return 1;
    }

    HTTP_Heading contdisp_args = http_parse_content_disp(arena, &contdisp);

    /* Begin debug */

    printf(DEBUG " Content Disposition Args (%llu):\n", contdisp_args.inner.size);

    for (uptr i = 0; i < contdisp_args.inner.size; i += 1) {
        str8 key   = array_get_or(&contdisp_args.key,   i, pax_str8(""));
        str8 value = array_get_or(&contdisp_args.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_cast(int, key.length), key.memory,
            pax_cast(int, value.length), value.memory);
    }

    /* End debug */

    str8 name = {};

    if (hash_map_get(&contdisp_args, pax_str8("filename"), &name) == 0) {
        http_response_write_start(writer, HTTP_VERSION_1_1,
            HTTP_STATUS_BAD_REQUEST, HTTP_MESSAGE_BAD_REQUEST);

        return 1;
    }

    name = str8_slice_since_first(name, pax_str8("\""));
    name = str8_slice_until_first(name, pax_str8("\""));
    name = str8_trim_spaces(name);

    File file = file_open_new(arena, SERVER_DATA_PATH, name, FILE_PERM_WRITE);

    if (file != 0) {
        buf8 buffer = buf8_full(multipart.memory, multipart.length);

        if (file_write(file, &buffer) != 0) {
            printf(INFO " Wrote content to " BLU("'%.*s'") "\n",
                pax_cast(int, name.length), name.memory);

            file_close(file);

            http_response_write_start(writer, HTTP_VERSION_1_1,
                HTTP_STATUS_OK, HTTP_MESSAGE_OK);

            return 1;
        }
    }

    printf(ERROR " Unable to create new file for writing\n");

    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_UNPROCESSABLE_CONTENT, HTTP_MESSAGE_UNPROCESSABLE_CONTENT);

    return 1;
}

b32
http_server_on_application_form_url_encoded(Arena* arena, HTTP_Heading* heading, str8 application, HTTP_Response_Writer* writer)
{
    HTTP_Heading params = http_parse_url_encoded(arena, application);

    /* Begin debug */

    printf(DEBUG " Params (%llu):\n", params.inner.size);

    for (uptr i = 0; i < params.inner.size; i += 1) {
        str8 key   = array_get_or(&params.key,   i, pax_str8(""));
        str8 value = array_get_or(&params.value, i, pax_str8(""));

        printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
            pax_cast(int, key.length), key.memory,
            pax_cast(int, value.length), value.memory);
    }

    /* End debug */

    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_OK, HTTP_MESSAGE_OK);

    return 1;
}

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer)
{
    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_METHOD_NOT_ALLOWED, HTTP_MESSAGE_METHOD_NOT_ALLOWED);

    return 1;
}
