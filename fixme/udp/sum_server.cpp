#include "common.hpp"

#include <stdio.h>

int
main()
{
    Arena arena = system_reserve(4);

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    if (system_network_start() == 0) return 1;

    Address    server_addr = address_any(ADDRESS_KIND_IP4);
    Socket_UDP server      = server_start(&arena, SERVER_PORT, server_addr);

    if (server == 0) return 1;

    uptr total  = 0;
    uptr number = 0;

    Address addr = {};
    u16     port = 0;

    do {
        server_read(server, &request, &port, &addr);

        if (buffer_decode_u64(&request, &number) == 0)
            continue;

        number  = u64_host_from_net(number);
        total  += number;

        if (number == 0) break;

        printf(INFO " total, number = " YLW("%lli") ", " YLW("%lli") "\n",
            total, number);
    } while (true);

    buffer_encode_u64(&response, total);

    server_write(server, response, port, addr);
    server_stop(server);

    system_network_stop();
}
