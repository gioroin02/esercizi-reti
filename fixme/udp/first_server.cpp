#include "common.hpp"

#include <stdio.h>

static const str8 SERVER_MSG       = pax_str8("Ciao, sono il server!");
static const str8 SERVER_COUNT_PFX = pax_str8("--count=");

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(4);

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    buffer_write_str8(&response, SERVER_MSG);

    if (system_network_start() == 0) return 1;

    Address    server_addr = address_any(ADDRESS_KIND_IP4);
    Socket_UDP server      = server_start(&arena, SERVER_PORT, server_addr);

    if (server == 0) return 1;

    uptr lifetime = 1;

    Format_Options opts = {};

    opts.base  = 10;
    opts.flags = FORMAT_FLAG_LEADING_ZERO |
                 FORMAT_FLAG_LEADING_PLUS;

    if (argc == 2) {
        str8 input = str8_count_max(pax_cast(u8*, argv[1]), 32);
        str8 count = str8_trim_prefix(input, SERVER_COUNT_PFX);

        if (str8_starts_with(input, SERVER_COUNT_PFX) != 0)
            str8_parse_u64(count, opts, &lifetime);
    }

    Address addr = {};
    u16     port = 0;

    for (uptr i = 0; i < lifetime; i += 1) {
        server_read(server, &request, &port, &addr);

        char* memory = pax_cast(char*, request.memory);
        int   length = pax_cast(int, request.size);

        printf(INFO " " PRP("'%.*s'") "\n", length, memory);

        server_write(server, response, port, addr);
    }

    server_stop(server);

    system_network_stop();
}
