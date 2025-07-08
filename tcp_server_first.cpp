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

        str8 arg1 = str8_count_max(
            pax_cast(const u8*, argv[1]), 128);

        u16_from_str8(arg1, opts, &server_port);
    }

    Socket_TCP server = server_start(&arena,
        server_port, address_any(ADDRESS_KIND_IP4));

    if (server == 0) return 1;

    Buffer buffer = buffer_reserve(&arena, MEMORY_KIB);

    Socket_TCP session = session_open(server, &arena);

    server_stop(server);

    session_read(session, &buffer);

    session_write(session, buffer);
    session_close(session);

    system_network_stop();
}
