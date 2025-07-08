#include "common.hpp"

#include <stdio.h>

static const str8 CLIENT_MSG = pax_str8("Ciao, sono il client!");

int
main()
{
    Arena arena = system_reserve(4);

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    buffer_write_str8(&request, CLIENT_MSG);

    if (system_network_start() == 0) return 1;

    Address server_addr = {};

    if (str8_parse_address(SERVER_ADDR, ADDRESS_KIND_IP4, &server_addr) == 0)
        return 1;

    Socket_UDP client = client_start(&arena, ADDRESS_KIND_IP4);

    if (client_write(client, request, SERVER_PORT, server_addr) == 0)
        return 1;

    Address addr = {};
    u16     port = 0;

    client_read(client, &response, &port, &addr);

    if (address_is_equal(addr, server_addr) != 0 && port == SERVER_PORT) {
        char* memory = pax_cast(char*, response.memory);
        int   length = pax_cast(int, response.size);

        printf(INFO " " PRP("'%.*s'") "\n", length, memory);
    } else
        printf(ERROR " Indirizzo o porta inaspettati...\n");

    client_stop(client);

    system_network_stop();
}
