#ifndef COMMON_CPP
#define COMMON_CPP

#include "common.hpp"

#include <stdio.h>

Socket_UDP
client_start(Arena* arena, Address_Kind kind)
{
    return socket_udp_create(arena, kind);
}

void
client_stop(Socket_UDP self)
{
    socket_udp_destroy(self);
}

b32
client_write(Socket_UDP self, Buffer buffer, u16 port, Address address)
{
    printf(DEBUG " Scrittura richiesta di " YLW("%lluB") " a {addr = [",
        buffer.size);

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

void
client_read(Socket_UDP self, Buffer* buffer, u16* port, Address* address)
{
    printf(DEBUG " Lettura risposta ");

    socket_udp_read_from(self, buffer, port, address);

    printf("di " YLW("%lluB") " da {addr = [", buffer->size);

    if (address != 0) {
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

    printf("}: %s\n", buffer->size > 0 ? SUCC : FAIL);
}

Socket_UDP
server_start(Arena* arena, u16 port, Address address)
{
    uptr       offset = arena_offset(arena);
    Socket_UDP result = socket_udp_create(arena, address.kind);

    if (result != 0) {
        printf(INFO " Attivazione porta " YLW("%u") ": ", port);

        b32 state = socket_udp_bind(result, port, address);

        printf("%s\n", state != 0 ? SUCC : FAIL);

        if (state != 0) return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
server_stop(Socket_UDP self)
{
    socket_udp_destroy(self);
}

b32
server_write(Socket_UDP self, Buffer buffer, u16 port, Address address)
{
    printf(DEBUG " Scrittura risposta di " YLW("%lluB") " a {addr = [",
        buffer.size);

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

void
server_read(Socket_UDP self, Buffer* buffer, u16* port, Address* address)
{
    printf(DEBUG " Lettura richiesta ");

    socket_udp_read_from(self, buffer, port, address);

    printf("di " YLW("%lluB") " da {addr = [", buffer->size);

    if (address != 0) {
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

    printf("}: %s\n", buffer->size > 0 ? SUCC : FAIL);
}

str8
str8_read_from_stdin(Arena* arena, uptr length)
{
    str8 result = str8_reserve(arena, length);

    fgets(pax_cast(char*, result.memory),
        pax_cast(int, result.length), stdin);

    return result;
}

#endif // COMMON_CPP
