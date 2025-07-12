#ifndef TCP_CLIENT_CPP
#define TCP_CLIENT_CPP

#include "client.hpp"

#include <stdio.h>

Socket_TCP
client_tcp_start(Arena* arena, Address_Kind kind)
{
    return socket_tcp_create(arena, kind);
}

void
client_tcp_stop(Socket_TCP self)
{
    socket_tcp_destroy(self);
}

b32
client_tcp_connect(Socket_TCP self, u16 port, Address address)
{
    printf(TRACE " Apertura sessione con {addr = [");

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

    printf("], port = " YLW("%u") "}: ", port);

    b32 state = socket_tcp_connect(self, port, address);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

b32
client_tcp_write(Socket_TCP self, buf8* buffer)
{
    printf(TRACE " Scrittura richiesta di " YLW("%lluB") ": ",
        buffer->size);

    b32 state = socket_tcp_write(self, buffer);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

b32
client_tcp_read(Socket_TCP self, buf8* buffer)
{
    printf(TRACE " Lettura risposta ");

    b32 state = socket_tcp_read(self, buffer);

    printf("di " YLW("%lluB") ": ", buffer->size);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

#endif // TCP_CLIENT_CPP
