#ifndef UDP_SERVER_CPP
#define UDP_SERVER_CPP

#include "server.hpp"

#include <stdio.h>

Socket_UDP
server_udp_start(Arena* arena, u16 port, Address address)
{
    uptr       offset = arena_offset(arena);
    Socket_UDP result = socket_udp_create(arena, address.kind);

    if (result != 0) {
        printf(TRACE " Attivazione porta " YLW("%u") ": ", port);

        b32 state = socket_udp_bind(result, port, address);

        printf("%s\n", state != 0 ? SUCC : FAIL);

        if (state != 0) return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
server_udp_stop(Socket_UDP self)
{
    socket_udp_destroy(self);
}

b32
server_udp_write(Socket_UDP self, Buffer* buffer, u16 port, Address address)
{
    printf(TRACE " Scrittura risposta di " YLW("%lluB") " a {addr = [",
        buffer->size);

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

    b32 state = socket_udp_write_to(self, buffer, port, address);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

b32
server_udp_read(Socket_UDP self, Buffer* buffer, u16* port, Address* address)
{
    printf(TRACE " Lettura richiesta ");

    b32 state = socket_udp_read_from(self, buffer, port, address);

    printf("di " YLW("%lluB") " da {addr = [", buffer->size);

    if (state != 0 && address != 0) {
        switch (address->kind) {
            case ADDRESS_KIND_IP4: {
                for (uptr i = 0; i < ADDRESS_IP4_GROUPS; i += 1) {
                    printf(YLW("%u"), address->ip4.memory[i]);

                    if (i + 1 != ADDRESS_IP4_GROUPS)
                        printf(YLW("."));
                }
            } break;

            case ADDRESS_KIND_IP6: {
                for (uptr i = 0; i < ADDRESS_IP6_GROUPS; i += 1) {
                    printf(YLW("%x"), address->ip6.memory[i]);

                    if (i + 1 != ADDRESS_IP6_GROUPS)
                        printf(YLW(":"));
                }
            } break;

            default: break;
        }
    }

    printf("]");

    if (port != 0) printf(", port = " YLW("%u"), *port);

    printf("}: %s\n", state != 0 ? SUCC : FAIL);

    return state;
}

#endif // UDP_SERVER_CPP
