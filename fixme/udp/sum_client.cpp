#include "common.hpp"

#include <stdio.h>

int
main()
{
    Arena arena = system_reserve(4);

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    if (system_network_start() == 0) return 1;

    Address server_addr = {};

    if (str8_parse_address(SERVER_ADDR, ADDRESS_KIND_IP4, &server_addr) == 0)
        return 1;

    Socket_UDP client = client_start(&arena, ADDRESS_KIND_IP4);

    uptr number = 0;

    Format_Options opts = {};

    opts.base  = 10;
    opts.flags = FORMAT_FLAG_LEADING_ZERO |
                 FORMAT_FLAG_LEADING_PLUS;

    do {
        uptr offset = arena_offset(&arena);

        printf("-> ");

        str8 input = str8_read_from_stdin(&arena, MEMORY_KIB);
        str8 line  = str8_slice_until_first(input, pax_str8("\n"));

        if (str8_parse_u64(line, opts, &number) == 0) continue;

        arena_rewind(&arena, offset);

        buffer_encode_u64(&request, u64_net_from_host(number));
        client_write(client, request, SERVER_PORT, server_addr);

        if (number == 0) break;
    } while (true);

    Address addr = {};
    u16     port = 0;

    client_read(client, &response, &port, &addr);

    if (address_is_equal(addr, server_addr) != 0 && port == SERVER_PORT) {
        uptr total = 0;

        if (buffer_decode_u64(&response, &total) != 0)
            printf(INFO " total = " YLW("%lli")  "\n", total);
        else
            printf(ERROR " Errore nella lettura del risultato...\n");
    } else
        printf(ERROR " Indirizzo o porta inaspettati...\n");

    client_stop(client);

    system_network_stop();
}
