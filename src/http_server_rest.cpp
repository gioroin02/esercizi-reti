#include "tcp/exports.hpp"
#include "http/exports.hpp"

#include "pax/storage/exports.hpp"

#include <stdio.h>

b32
http_server_on_get(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer, Socket_TCP session);

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer, Socket_TCP session);

static const str8 SERVER_ARG_PORT = pax_str8("--port=");

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(256);

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
        HTTP_Response_Writer writer = http_response_writer_init(&arena, 16 * MEMORY_KIB);

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
            state = http_server_on_get(&arena, &heading, &content, &writer, session);

        if (state == 0)
            http_server_fallback(&arena, &heading, &content, &writer, session);

        session_tcp_close(session);

        arena_rewind(&arena, offset);
    }

    server_tcp_stop(server);

    system_network_stop();
}

b32
http_server_on_get(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer, Socket_TCP session)
{
    str8         resource = http_heading_get_resource(heading, pax_str8(""));
    HTTP_Heading params   = http_parse_resource(arena, &resource);

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

    buf8 buffer = buf8_reserve(arena, 16 * MEMORY_KIB);

    if (str8_is_equal(resource, pax_str8("calcola-somma")) != 0) {
        str8 argx = hash_map_get_or(&params, pax_str8("x"), pax_str8(""));
        str8 argy = hash_map_get_or(&params, pax_str8("y"), pax_str8(""));

        i32 x = 0;
        i32 y = 0;

        Format_Options opts = format_options_base(10);

        i32_from_str8(argx, opts, &x);
        i32_from_str8(argy, opts, &y);

        str8 result = str8_from_i32(arena, opts, x + y);

        buf8_write_str8_tail(&buffer, pax_str8("{ \"result\": "));
        buf8_write_str8_tail(&buffer, result);
        buf8_write_str8_tail(&buffer, pax_str8(" }"));

        http_response_write_start(writer, HTTP_VERSION_1_1,
            HTTP_STATUS_OK, HTTP_MESSAGE_OK);

        str8 length = str8_from_uptr(arena, format_options_base(10), buffer.size);

        http_response_write_header(writer, HTTP_HEADER_CONTENT_TYPE, MIME_APPLICATION_JSON);
        http_response_write_header(writer, HTTP_HEADER_CONTENT_LENGTH, length);

        http_response_write_content(writer, &buffer);
    }

    if (str8_is_equal(resource, pax_str8("calcola-primi")) != 0) {
        str8 argx = hash_map_get_or(&params, pax_str8("x"), pax_str8(""));
        str8 argy = hash_map_get_or(&params, pax_str8("y"), pax_str8(""));

        u32 x = 0;
        u32 y = 0;

        Format_Options opts = format_options_base(10);

        u32_from_str8(argx, opts, &x);
        u32_from_str8(argy, opts, &y);

        // compute

        http_response_write_start(writer, HTTP_VERSION_1_1,
            HTTP_STATUS_OK, HTTP_MESSAGE_OK);

        http_response_write_header(writer, HTTP_HEADER_CONTENT_TYPE, MIME_APPLICATION_JSON);

        buf8_write_str8_tail(&buffer, pax_str8("{ \"result\": [ "));

        uptr temp = arena_offset(arena);

        x = pax_max(x, 2);
        y = pax_max(y, x);

        for (uptr i = x; i < y; i += 1) {
            b32 prime = 1;

            for (uptr j = 2; j <= i / 2 && prime != 0; j += 1) {
                if (i % j == 0) prime = 0;
            }

            if (prime != 0) {
                str8 number = str8_from_uptr(arena, format_options_base(10), i);

                if (i != x)
                    buf8_write_str8_tail(&buffer, pax_str8(", "));

                buf8_write_str8_tail(&buffer, number);
            }

            arena_rewind(arena, temp);

            if (buffer.size + 1024 >= buffer.length) {
                http_response_write_content(writer, &buffer);
                http_response_write(writer, session);
            }
        }

        buf8_write_str8_tail(&buffer, pax_str8(" ] }"));
    }

    http_response_write_content(writer, &buffer);
    http_response_write(writer, session);

    return 1;
}

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, buf8* content, HTTP_Response_Writer* writer, Socket_TCP session)
{
    http_response_write_start(writer, HTTP_VERSION_1_1,
        HTTP_STATUS_METHOD_NOT_ALLOWED, HTTP_MESSAGE_METHOD_NOT_ALLOWED);

    http_response_write(writer, session);

    return 1;
}
