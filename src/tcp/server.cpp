#ifndef TCP_SERVER_CPP
#define TCP_SERVER_CPP

#include "server.hpp"

#include <stdio.h>

Socket_TCP
server_tcp_start(Arena* arena, u16 port, Address address)
{
    uptr       offset = arena_offset(arena);
    Socket_TCP result = socket_tcp_create(arena, address.kind);

    if (result != 0) {
        printf(TRACE " Attivazione porta " YLW("%u") ": ", port);

        b32 state = socket_tcp_bind(result, port, address);

        printf("%s\n", state != 0 ? SUCC : FAIL);

        if (state != 0) {
            printf(TRACE " Attivazione porta in ascolto: ");

            state = socket_tcp_listen(result);

            printf("%s\n", state != 0 ? SUCC : FAIL);

            if (state != 0) return result;
        }

        arena_rewind(arena, offset);
    }

    return 0;
}

void
server_tcp_stop(Socket_TCP self)
{
    socket_tcp_destroy(self);
}

Socket_TCP
session_tcp_open(Socket_TCP self, Arena* arena)
{
    printf(TRACE " Apertura sessione ");

    Socket_TCP result = socket_tcp_accept(self, arena);

    printf("con {addr = [");

    Address address = socket_tcp_get_address(result);
    u16     port    = socket_tcp_get_port(result);

    switch (address.kind) {
        case ADDRESS_KIND_IP4: {
            for (uptr i = 0; i < ADDRESS_IP4_GROUPS; i += 1) {
                printf(YLW("%u"), address.ip4.memory[i]);

                if (i + 1 != ADDRESS_IP4_GROUPS)
                    printf(YLW("."));
            }
        } break;

        case ADDRESS_KIND_IP6: {
            for (uptr i = 0; i < ADDRESS_IP6_GROUPS; i += 1) {
                printf(YLW("%x"), address.ip6.memory[i]);

                if (i + 1 != ADDRESS_IP6_GROUPS)
                    printf(YLW(":"));
            }
        } break;

        default: break;
    }

    printf("], port = " YLW("%u") "}: %s\n", port, result != 0 ? SUCC : FAIL);

    return result;
}

void
session_tcp_close(Socket_TCP self)
{
    socket_tcp_destroy(self);
}

b32
session_tcp_write(Socket_TCP self, Buffer buffer)
{
    printf(TRACE " Scrittura risposta di " YLW("%lluB") ": ",
        buffer.size);

    b32 state = socket_tcp_write(self, buffer);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

b32
session_tcp_read(Socket_TCP self, Buffer* buffer)
{
    printf(TRACE " Lettura richiesta ");

    b32 state = socket_tcp_read(self, buffer);

    printf("di " YLW("%lluB") ": ", buffer->size);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

#endif // TCP_SERVER_CPP
