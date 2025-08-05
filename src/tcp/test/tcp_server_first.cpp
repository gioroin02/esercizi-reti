#include "../exports.hpp"

#include <stdio.h>

static const str8 SERVER_MSG = pax_str8("Ciao, sono il server!");

static const str8 SERVER_ARG_PORT     = pax_str8("--port=");
static const str8 SERVER_ARG_LIFETIME = pax_str8("--lifetime=");

struct Server
{
    Socket_TCP socket = 0;

    u16 port     = 8000;
    u32 lifetime = 1;
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

            if (str8_starts_with(arg, SERVER_ARG_LIFETIME) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_LIFETIME);
                arg = str8_trim_spaces(arg);

                u32_from_str8(arg, opts, &server.lifetime);
            }
        }
    }

    server.socket = server_tcp_start(&arena, server.port, address_any(ADDRESS_TYPE_IP4));

    if (server.socket == 0) return 1;

    usiz offset = arena_offset(&arena);

    for (usiz i = 0; i < server.lifetime; i += 1) {
        Session session = {};

        session.socket   = session_tcp_open(&arena, server.socket);
        session.request  = buf8_reserve(&arena, MEMORY_KIB);
        session.response = buf8_reserve(&arena, MEMORY_KIB);

        if (session_tcp_read(session.socket, &session.request) != 0) {
            str8 string = buf8_read_str8_head(&session.request,
                &arena, session.request.size);

            printf(INFO " " BLU("'%.*s'") "\n",
                pax_as(int, string.length), string.memory);

            buf8_write_str8_tail(&session.response, SERVER_MSG);

            session_tcp_write(session.socket, &session.response);
        }

        session_tcp_close(session.socket);

        arena_rewind(&arena, offset);
    }

    server_tcp_stop(server.socket);

    system_network_stop();
}
