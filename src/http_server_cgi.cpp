#include "tcp/exports.hpp"
#include "http/exports.hpp"

#include "pax/storage/exports.hpp"

#include <stdio.h>

b32
http_server_on_get(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer);

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer);

static const str8 HTML_BEGIN = pax_str8(
    "<!DOCTYPE html> <html lang=\"it\"> <head>"
        "<meta charset=\"utf-8\">"
    "</head> <body>"
);

static const str8 HTML_END = pax_str8("</body> </html>");

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

    buf8 buffer = buf8_reserve(arena, 4 * MEMORY_KIB);

    if (str8_is_equal(resource, pax_str8("add")) != 0) {
        str8 argx = hash_map_get_or(&params, pax_str8("x"), pax_str8(""));
        str8 argy = hash_map_get_or(&params, pax_str8("y"), pax_str8(""));

        i32 x = 0;
        i32 y = 0;

        Format_Options opts = format_options(10, FORMAT_FLAG_LEADING_PLUS |
            FORMAT_FLAG_LEADING_ZERO);

        i32_from_str8(argx, opts, &x);
        i32_from_str8(argy, opts, &y);

        str8 result = str8_from_i32(arena, opts, x + y);

        buf8_write_str8_tail(&buffer, HTML_BEGIN);
        buf8_write_str8_tail(&buffer, result);
        buf8_write_str8_tail(&buffer, HTML_END);
    }

    if (str8_is_equal(resource, pax_str8("sub")) != 0) {
        str8 argx = hash_map_get_or(&params, pax_str8("x"), pax_str8(""));
        str8 argy = hash_map_get_or(&params, pax_str8("y"), pax_str8(""));

        i32 x = 0;
        i32 y = 0;

        Format_Options opts = format_options(10, FORMAT_FLAG_LEADING_PLUS |
            FORMAT_FLAG_LEADING_ZERO);

        i32_from_str8(argx, opts, &x);
        i32_from_str8(argy, opts, &y);

        str8 result = str8_from_i32(arena, opts, x - y);

        buf8_write_str8_tail(&buffer, HTML_BEGIN);
        buf8_write_str8_tail(&buffer, result);
        buf8_write_str8_tail(&buffer, HTML_END);
    }

    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_OK, HTTP_MESSAGE_OK);

    http_response_write_content(writer, &buffer);

    return 1;
}

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer)
{
    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_METHOD_NOT_ALLOWED, HTTP_MESSAGE_METHOD_NOT_ALLOWED);

    return 1;
}
