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

    Socket_TCP client = client_start(&arena, ADDRESS_KIND_IP4);

    if (client_connect(client, SERVER_PORT, server_addr) == 0)
        return 1;

    printf("-> ");

    str8 input = str8_read_from_stdin(&arena, MEMORY_KIB);
    str8 line  = str8_slice_until_first(input, pax_str8("\n"));

    uptr number = 0;

    Format_Spec spec = {};

    spec.base  = 10;
    spec.flags = FORMAT_FLAG_LEADING_ZERO |
                 FORMAT_FLAG_LEADING_PLUS;

    str8_parse_u64(line, spec, &number);

    buffer_encode_u64(&request, u64_net_from_host(number));

    client_write(client, request);
    client_read(client, &response);

    b32 state = buffer_decode_u64(&response, &number);

    printf(INFO " " YLW("%llu") "\n", u64_host_from_net(number));

    client_stop(client);

    system_network_stop();
}
