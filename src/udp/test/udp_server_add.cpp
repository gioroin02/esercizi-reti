#include "../exports.hpp"

#include <stdio.h>

static const str8 SERVER_ARG_PORT = pax_str8("--port=");

struct Server
{
    Socket_UDP socket = 0;

    u16 port = 8000;
};

struct Session
{
    Address addr = {};
    u16     port = 0;

    buf8 request  = {};
    buf8 response = {};
};

int
main(int argc, char** argv)
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    Server server = {};

    if (argc != 1) {
        Format_Options opts = format_options_base(10);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server.port);
            }
        }
    }

    server.socket = server_udp_start(&arena, server.port, address_any(ADDRESS_KIND_IP4));

    if (server.socket == 0) return 1;

    uptr offset = arena_offset(&arena);
    u32  result = 0;
    u32  number = 0;

    do {
        Session session = {};

        session.request  = buf8_reserve(&arena, MEMORY_KIB);
        session.response = buf8_reserve(&arena, MEMORY_KIB);

        b32 state = server_udp_read(server.socket, &session.request,
            &session.port, &session.addr);

        if (state == 0) continue;

        number = 0;

        buf8_read_mem8_head(&session.request,
            pax_cast(u8*, &number), pax_size_of(u32));

        number  = u32_host_from_net(number);
        result += number;

        printf(INFO " number = " YLW("%u") ", result = " YLW("%u") "\n",
            number, result);

        result = u32_net_from_host(result);

        buf8_write_mem8_tail(&session.response,
            pax_cast(u8*, &result), pax_size_of(u32));

        server_udp_write(server.socket, &session.response,
            session.port, session.addr);

        result = u32_host_from_net(result);
    } while (number != 0);

    server_udp_stop(server.socket);

    system_network_stop();
}
