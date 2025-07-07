#ifndef COMMON_CPP
#define COMMON_CPP

#include "common.hpp"

#include <stdio.h>

Socket_TCP
client_start(Arena* arena, Address_Kind kind)
{
    return socket_tcp_create(arena, kind);
}

void
client_stop(Socket_TCP self)
{
    socket_tcp_destroy(self);
}

b32
client_connect(Socket_TCP self, u16 port, Address address)
{
    printf(INFO " Apertura sessione con {addr = [");

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
client_write(Socket_TCP self, Buffer buffer)
{
    printf(DEBUG " Scrittura richiesta di " YLW("%lluB") ": ",
        buffer.size);

    b32 state = socket_tcp_write(self, buffer);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

void
client_read(Socket_TCP self, Buffer* buffer)
{
    printf(DEBUG " Lettura risposta ");

    socket_tcp_read(self, buffer);

    printf("di " YLW("%lluB") ": ", buffer->size);

    printf("%s\n", buffer->size > 0 ? SUCC : FAIL);
}

Socket_TCP
server_start(Arena* arena, u16 port, Address address)
{
    uptr       offset = arena_offset(arena);
    Socket_TCP result = socket_tcp_create(arena, address.kind);

    if (result != 0) {
        printf(INFO " Attivazione porta " YLW("%u") ": ", port);

        b32 state = socket_tcp_bind(result, port, address);

        printf("%s\n", state != 0 ? SUCC : FAIL);

        if (state != 0) {
            printf(INFO " Attivazione porta in ascolto: ");

            state = socket_tcp_listen(result);

            printf("%s\n", state != 0 ? SUCC : FAIL);

            if (state != 0) return result;
        }

        arena_rewind(arena, offset);
    }

    return 0;
}

void
server_stop(Socket_TCP self)
{
    socket_tcp_destroy(self);
}

Socket_TCP
session_open(Socket_TCP self, Arena* arena)
{
    printf(INFO " Apertura sessione ");

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
session_close(Socket_TCP self)
{
    socket_tcp_destroy(self);
}

b32
session_write(Socket_TCP self, Buffer buffer)
{
    printf(DEBUG " Scrittura risposta di " YLW("%lluB") ": ",
        buffer.size);

    b32 state = socket_tcp_write(self, buffer);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

void
session_read(Socket_TCP self, Buffer* buffer)
{
    printf(DEBUG " Lettura richiesta ");

    socket_tcp_read(self, buffer);

    printf("di " YLW("%lluB") ": ", buffer->size);

    printf("%s\n", buffer->size > 0 ? SUCC : FAIL);
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
