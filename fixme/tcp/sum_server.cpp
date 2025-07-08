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
    Socket_TCP server      = server_start(&arena, SERVER_PORT, server_addr);

    if (server == 0) return 1;

    Socket_TCP session = session_open(server, &arena);

    if (session == 0) return 1;

    server_stop(server);

    uptr total  = 0;
    uptr number = 0;

    do {
        session_read(session, &request);

        if (buffer_decode_u64(&request, &number) == 0)
            continue;

        number  = u64_host_from_net(number);
        total  += number;

        if (number == 0) break;

        printf(DEBUG " total, number = " YLW("%llu") ", " YLW("%llu") "\n",
            total, number);
    } while (true);

    buffer_encode_u64(&response, total);

    session_write(session, response);
    session_close(session);

    system_network_stop();
}
