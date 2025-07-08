#include "tcp/exports.hpp"

#include <stdio.h>

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    u16 server_port = 8000;

    if (argc == 2) {
        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        str8 arg = str8_count_max(pax_cast(const u8*, argv[1]), 128);

        u16_from_str8(arg, opts, &server_port);
    }

    Socket_TCP server = server_start(&arena,
        server_port, address_any(ADDRESS_KIND_IP4));

    if (server == 0) return 1;

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    Socket_TCP session = session_open(server, &arena);

    if (session == 0) return 1;

    server_stop(server);

    u32 input  = 0;
    u32 result = 0;

    do {
        buffer_clear(&request);

        if (session_read(session, &request) == 0)
            break;

        input = 0;

        buffer_read_mem8(&request, 0, pax_cast(u8*, &input),
            pax_size_of(u32));

        input = u32_host_from_net(input);

        printf(INFO " input  = %lu\n", input);

        result += input;

        printf(INFO " result = %lu\n", result);
    } while (input != 0);

    result = u32_net_from_host(result);

    buffer_write_mem8(&response, pax_cast(u8*, &result),
        pax_size_of(u32));

    session_write(session, response);
    session_close(session);

    system_network_stop();
}