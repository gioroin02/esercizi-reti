#include "tcp/exports.hpp"
#include "http/exports.hpp"

#include <stdio.h>

b32
http_server_on_get(Arena* arena, HTTP_Heading* heading, Buffer* content, HTTP_Response_Writer* writer);

b32
http_server_on_post(Arena* arena, HTTP_Heading* heading, Buffer* content, HTTP_Response_Writer* writer);

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, Buffer* content, HTTP_Response_Writer* writer);

int
main()
{
    Arena arena = system_reserve(64);

    if (system_network_start() == 0) return 1;

    Socket_TCP server = server_start(&arena, 8000, address_any(ADDRESS_KIND_IP4));
    uptr       offset = arena_offset(&arena);

    if (server == 0) return 1;

    while (1) {
        Socket_TCP session = session_open(server, &arena);

        HTTP_Request_Reader  reader = http_request_reader_init(&arena, MEMORY_KIB);
        HTTP_Response_Writer writer = http_response_writer_init(&arena);

        HTTP_Heading heading = http_request_heading(&reader, &arena, session);
        Buffer       content = {};

        uptr payload = http_heading_get_content_length(&heading, 0);

        if (payload != 0)
            content = http_request_content(&reader, &arena, 0, session);

        /* Begin debug */

        printf(DEBUG " Heading (%llu):\n", heading.inner.size);

        for (uptr i = 0; i < heading.inner.size; i += 1) {
            str8 key   = array_get_or(&heading.key,   i, pax_str8(""));
            str8 value = array_get_or(&heading.value, i, pax_str8(""));

            printf(DEBUG "     - " YLW("'%.*s'") " => " PRP("'%.*s'") "\n",
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

        session_close(session);

        arena_rewind(&arena, offset);
    }

    server_stop(server);

    system_network_stop();
}

b32
http_server_on_get(Arena* arena, HTTP_Heading* heading, Buffer* content, HTTP_Response_Writer* writer)
{
    http_response_write_start(writer,
        HTTP_VERSION_1_1, HTTP_STATUS_OK, HTTP_MESSAGE_OK);

    return 1;
}

b32
http_server_on_post(Arena* arena, HTTP_Heading* heading, Buffer* content, HTTP_Response_Writer* writer)
{
    http_response_write_start(writer,
        HTTP_VERSION_1_1, HTTP_STATUS_OK, HTTP_MESSAGE_OK);

    return 1;
}

b32
http_server_fallback(Arena* arena, HTTP_Heading* heading, Buffer* content, HTTP_Response_Writer* writer)
{
    http_response_write_start(writer,
        HTTP_VERSION_1_1, HTTP_STATUS_METHOD_NOT_ALLOWED, HTTP_MESSAGE_METHOD_NOT_ALLOWED);

    return 1;
}