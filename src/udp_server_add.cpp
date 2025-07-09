#include "udp/exports.hpp"

#include <stdio.h>

static const str8 SERVER_ARG_PORT = pax_str8("--port=");

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    u16 server_port = 8000;

    if (argc != 1) {
        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server_port);
            }
        }
    }

    Socket_UDP server = server_udp_start(&arena,
        server_port, address_any(ADDRESS_KIND_IP4));

    if (server == 0) return 1;

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    Address client_addr = {};
    u16     client_port = 0;

    u32 result = 0;

    do {
        Address addr = {};
        u16     port = 0;

        server_udp_read(server, &request, &port, &addr);

        if (client_port == 0) {
            client_addr = addr;
            client_port = port;
        }

        if (client_port == port && address_is_equal(client_addr, addr) != 0) {
            u32 input = 0;

            buffer_read_mem8(&request, 0, pax_cast(u8*, &input),
                pax_size_of(u32));

            buffer_clear(&request);

            input = u32_host_from_net(input);

            if (input == 0) break;

            result += input;

            printf(INFO " input = " YLW("%lu") ", result = " YLW("%lu") "\n",
                input, result);
        } else
            printf(ERROR " Indirizzo o porta inaspettati...\n");
    } while (true);

    result = u32_net_from_host(result);

    buffer_write_mem8(&response, pax_cast(u8*, &result),
        pax_size_of(u32));

    server_udp_write(server, response, client_port, client_addr);
    server_udp_stop(server);

    system_network_stop();
}
