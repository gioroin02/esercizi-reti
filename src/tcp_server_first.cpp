#include "tcp/exports.hpp"

#include <stdio.h>

static const str8 SERVER_MSG = pax_str8("Ciao, sono il server!");

static const str8 SERVER_ARG_PORT     = pax_str8("--port=");
static const str8 SERVER_ARG_LIFETIME = pax_str8("--lifetime=");

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    u16 server_port     = 8000;
    u32 server_lifetime = 1;

    if (argc != 1) {
        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server_port);
            }

            if (str8_starts_with(arg, SERVER_ARG_LIFETIME) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_LIFETIME);
                arg = str8_trim_spaces(arg);

                u32_from_str8(arg, opts, &server_lifetime);
            }
        }
    }

    Socket_TCP server = server_tcp_start(&arena,
        server_port, address_any(ADDRESS_KIND_IP4));

    if (server == 0) return 1;

    uptr offset = arena_offset(&arena);

    for (uptr i = 0; i < server_lifetime; i += 1) {
        Socket_TCP session = session_tcp_open(&arena, server);

        buf8 request  = buf8_reserve(&arena, MEMORY_KIB);
        buf8 response = buf8_reserve(&arena, MEMORY_KIB);

        if (session_tcp_read(session, &request) != 0) {
            buf8_normalize(&request);

            printf(INFO " " BLU("'%.*s'") "\n",
                pax_cast(int, request.size), request.memory);

            buf8_write_str8_tail(&response, SERVER_MSG);

            session_tcp_write(session, &response);
        }

        session_tcp_close(session);

        arena_rewind(&arena, offset);
    }

    server_tcp_stop(server);

    system_network_stop();
}
