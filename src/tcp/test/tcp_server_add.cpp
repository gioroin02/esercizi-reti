#include "../exports.hpp"

#include <stdio.h>

static const str8 SERVER_ARG_PORT = pax_str8("--port=");

struct Server
{
    Socket_TCP socket = 0;

    u16 port = 8000;
};

struct Session
{
    Socket_TCP socket = 0;

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
        Format_Options opts = format_options_simple(10);

        for (usiz i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server.port);
            }
        }
    }

    server.socket = server_tcp_start(&arena, server.port, address_any(ADDRESS_TYPE_IP4));

    if (server.socket == 0) return 1;

    Session session = {};

    session.socket = session_tcp_open(&arena, server.socket);

    server_tcp_stop(server.socket);

    if (session.socket == 0) return 1;

    session.request  = buf8_reserve(&arena, MEMORY_KIB);
    session.response = buf8_reserve(&arena, MEMORY_KIB);

    usiz offset = arena_offset(&arena);
    u32  result = 0;
    u32  number = 0;

    do {
        if (session_tcp_read(session.socket, &session.request) == 0)
            continue;

        number = 0;

        buf8_read_mem8_head(&session.request,
            pax_as_u8p(&number), pax_size_of(u32));

        number  = u32_host_from_net(number);
        result += number;

        printf(INFO " number = " YLW("%u") ", result = " YLW("%u") "\n",
            number, result);

        result = u32_net_from_host(result);

        buf8_write_mem8_tail(&session.response,
            pax_as_u8p(&result), pax_size_of(u32));

        session_tcp_write(session.socket, &session.response);

        result = u32_host_from_net(result);
    } while (number != 0);

    session_tcp_close(session.socket);

    system_network_stop();
}
