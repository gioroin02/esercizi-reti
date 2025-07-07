#include "tcp/exports.hpp"
#include "http/exports.hpp"

#include <stdio.h>

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

        Hash_Map<str8, str8> heading = http_request_heading(&reader, &arena, session);
        Buffer               content = {};

        uptr payload = http_heading_get_content_length(&heading, 0);

        if (payload != 0)
            content = http_request_content(&reader, &arena, 0, session);

        /* Begin debug */

        printf(DEBUG " Heading (%llu):\n", heading.inner.size);

        for (uptr i = 0; i < heading.inner.size; i += 1) {
            str8 key   = array_get_or(&heading.key,   i, pax_str8("<empty>"));
            str8 value = array_get_or(&heading.value, i, pax_str8("<empty>"));

            printf(DEBUG "     - " YLW("'%.*s'") " => " PRP("'%.*s'") "\n",
                pax_cast(int, key.length), key.memory,
                pax_cast(int, value.length), value.memory);
        }

        printf(DEBUG " Content (%llu)\n", content.size);

        /* End debug */

        http_response_write_start(&writer,
            HTTP_VERSION_1_1, HTTP_STATUS_200, HTTP_MESSAGE_OK);

        http_response_write(&writer, session);

        session_close(session);

        arena_rewind(&arena, offset);
    }

    server_stop(server);

    system_network_stop();
}
