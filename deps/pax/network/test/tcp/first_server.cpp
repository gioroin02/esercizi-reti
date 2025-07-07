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

    server_stop(server);

    session_read(session, &request);

    uptr input = 0;

    buffer_decode_u64(&request, &input);
    buffer_encode_u64(&response, input);

    session_write(session, response);
    session_close(session);

    system_network_stop();
}
