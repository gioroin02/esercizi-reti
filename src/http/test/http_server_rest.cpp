#include "../exports.hpp"

#include "../../tcp/exports.hpp"
#include "../../pax/storage/exports.hpp"

#include <stdio.h>

static const str8 SERVER_ARG_PORT = pax_str8("--port=");

struct Server
{
    Socket_TCP socket = 0;

    u16 port = 8000;
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
http_server_fallback(Arena* arena, Server* server, Session* session);

int
main(int argc, char** argv)
{
    Arena arena = system_reserve(128);

    if (system_network_start() == 0) return 1;

    Server server = {};

    if (argc != 1) {
        Format_Options opts = format_options_base(10);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server.port);
            }
        }
    }

    server.socket = server_tcp_start(&arena, server.port, address_any(ADDRESS_KIND_IP4));

    if (server.socket == 0) return 1;

    uptr offset = arena_offset(&arena);

    while (1) {
        Session session = {};

        session.socket = session_tcp_open(&arena, server.socket);
        session.reader = http_request_reader_init(&arena, 4 * MEMORY_KIB);
        session.writer = http_response_writer_init(&arena, 32 * MEMORY_KIB);

        session.heading = http_request_heading(&session.reader, &arena, session.socket);

        uptr payload = http_heading_get_content_length(&session.heading, 0);

        if (payload != 0)
            session.content = http_request_content(&session.reader, &arena, payload, session.socket);

        /* Begin debug */

        printf(DEBUG " Heading (%llu):\n", session.heading.inner.size);

        for (uptr i = 0; i < session.heading.inner.size; i += 1) {
            str8 key   = array_get_or(&session.heading.key,   i, pax_str8(""));
            str8 value = array_get_or(&session.heading.value, i, pax_str8(""));

            printf(DEBUG "     - " YLW("'%.*s'") " => " BLU("'%.*s'") "\n",
                pax_cast(int, key.length), key.memory,
                pax_cast(int, value.length), value.memory);
        }

        printf(DEBUG " Content (%llu)\n", session.content.size);

        /* End debug */

        str8 method = http_heading_get_method(&session.heading, pax_str8(""));
        b32  state  = 0;

        if (str8_is_equal(method, HTTP_METHOD_GET) != 0)
            state = http_server_on_get(&arena, &server, &session);

        if (state == 0)
            http_server_fallback(&arena, &server, &session);

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

    buf8 buffer = buf8_reserve(arena, 31 * MEMORY_KIB);

    if (str8_is_equal(resource, pax_str8("calcola-somma")) != 0) {
        str8 argx = hash_map_get_or(&params, pax_str8("x"), pax_str8(""));
        str8 argy = hash_map_get_or(&params, pax_str8("y"), pax_str8(""));

        i32 x = 0;
        i32 y = 0;

        Format_Options opts = format_options_base(10);

        i32_from_str8(argx, opts, &x);
        i32_from_str8(argy, opts, &y);

        argx = str8_from_i32(arena, opts, x);
        argy = str8_from_i32(arena, opts, y);

        str8 result = str8_from_i32(arena, opts, x + y);

        buf8_write_str8_tail(&buffer, pax_str8("{"));
        buf8_write_str8_tail(&buffer, pax_str8("\"x\":"));
        buf8_write_str8_tail(&buffer, argx);
        buf8_write_str8_tail(&buffer, pax_str8(","));
        buf8_write_str8_tail(&buffer, pax_str8("\"y\":"));
        buf8_write_str8_tail(&buffer, argy);
        buf8_write_str8_tail(&buffer, pax_str8(","));
        buf8_write_str8_tail(&buffer, pax_str8("\"result\":"));
        buf8_write_str8_tail(&buffer, result);
        buf8_write_str8_tail(&buffer, pax_str8("}"));

        str8 type   = MIME_APPLICATION_JSON;
        str8 length = str8_from_uptr(arena, opts, buffer.size);

        http_response_write_start(&session->writer, HTTP_VERSION_1_1,
            HTTP_STATUS_OK, HTTP_MESSAGE_OK);

        http_response_write_header(&session->writer, HTTP_HEADER_CONTENT_TYPE, type);
        http_response_write_header(&session->writer, HTTP_HEADER_CONTENT_LENGTH, length);

        http_response_write_content(&session->writer, &buffer);
        http_response_write(&session->writer, session->socket);
    }

    if (str8_is_equal(resource, pax_str8("calcola-primi")) != 0) {
        str8 argmin = hash_map_get_or(&params, pax_str8("min"), pax_str8(""));
        str8 argmax = hash_map_get_or(&params, pax_str8("max"), pax_str8(""));

        u32 min = 0;
        u32 max = 0;

        Format_Options opts = format_options_base(10);

        u32_from_str8(argmin, opts, &min);
        u32_from_str8(argmax, opts, &max);

        argmin = str8_from_u32(arena, opts, min);
        argmax = str8_from_u32(arena, opts, max);

        // compute

        http_response_write_start(&session->writer, HTTP_VERSION_1_1,
            HTTP_STATUS_OK, HTTP_MESSAGE_OK);

        http_response_write_header(&session->writer, HTTP_HEADER_CONTENT_TYPE,
            MIME_APPLICATION_JSON);

        buf8_write_str8_tail(&buffer, pax_str8("{"));
        buf8_write_str8_tail(&buffer, pax_str8("\"min\":"));
        buf8_write_str8_tail(&buffer, argmin);
        buf8_write_str8_tail(&buffer, pax_str8(","));
        buf8_write_str8_tail(&buffer, pax_str8("\"max\":"));
        buf8_write_str8_tail(&buffer, argmax);
        buf8_write_str8_tail(&buffer, pax_str8(","));
        buf8_write_str8_tail(&buffer, pax_str8("\"result\":"));
        buf8_write_str8_tail(&buffer, pax_str8("["));

        uptr temp = arena_offset(arena);

        min = pax_max(min, 2);

        b32 first = 1;

        for (uptr i = min; i <= max; i += 1) {
            b32 prime = 1;

            for (uptr j = 2; j <= i / 2 && prime != 0; j += 1) {
                if (i % j == 0) prime = 0;
            }

            if (prime != 0) {
                str8 number = str8_from_uptr(arena, format_options_base(10), i);
                uptr state  = 0;

                Format_Options opts = format_options_base(16);

                if (first == 0) {
                    state = buf8_write_str8_tail(&buffer, pax_str8(","));

                    if (state == 0) {
                        http_response_write_content(&session->writer, &buffer);
                        http_response_write(&session->writer, session->socket);

                        buf8_write_str8_tail(&buffer, number);
                    }
                } else
                    first = 0;

                state = buf8_write_str8_tail(&buffer, number);

                if (state == 0) {
                    http_response_write_content(&session->writer, &buffer);
                    http_response_write(&session->writer, session->socket);

                    buf8_write_str8_tail(&buffer, number);
                }
            }

            arena_rewind(arena, temp);
        }

        buf8_write_str8_tail(&buffer, pax_str8("]"));
        buf8_write_str8_tail(&buffer, pax_str8("}"));

        http_response_write_content(&session->writer, &buffer);
        http_response_write(&session->writer, session->socket);
    }

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
