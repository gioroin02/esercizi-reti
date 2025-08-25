#ifndef TCP_SERVER_C
#define TCP_SERVER_C

#include "server.h"

#include <stdio.h>

PxSocketTcp
tcpServerStart(PxArena* arena, PxAddress address, pxu16 port)
{
    pxiword     offset = pxArenaOffset(arena);
    PxSocketTcp result = pxSocketTcpCreate(arena, address.type);

    if (result != 0) {
        printf(TRACE " Attivazione porta " YLW("%u") ": ", port);

        pxb8 state = pxSocketTcpBind(result, address, port);

        printf("%s\n", state != 0 ? SUCC : FAIL);

        if (state != 0) {
            printf(TRACE " Attivazione porta in ascolto: ");

            state = pxSocketTcpListen(result);

            printf("%s\n", state != 0 ? SUCC : FAIL);

            if (state != 0) return result;
        }

        pxArenaRewind(arena, offset);
    }

    return 0;
}

void
tcpServerStop(PxSocketTcp self)
{
    pxSocketTcpDestroy(self);
}

PxSocketTcp
tcpSessionOpen(PxSocketTcp server, PxArena* arena)
{
    printf(TRACE " Apertura sessione ");

    PxSocketTcp result = pxSocketTcpAccept(server, arena);

    printf("con {addr = [");

    PxAddress address = pxSocketTcpGetAddress(result);
    pxu16     port    = pxSocketTcpGetPort(result);

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1) {
                printf(YLW("%u"), address.ip4.memory[i]);

                if (i + 1 != PX_ADDRESS_IP4_GROUPS)
                    printf(YLW("."));
            }
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            for (pxiword i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1) {
                printf(YLW("%x"), address.ip6.memory[i]);

                if (i + 1 != PX_ADDRESS_IP6_GROUPS)
                    printf(YLW(":"));
            }
        } break;

        default: break;
    }

    printf("], port = " YLW("%u") "}: %s\n", port, result != 0 ? SUCC : FAIL);

    return result;
}

void
tcpSessionClose(PxSocketTcp self)
{
    pxSocketTcpDestroy(self);
}

pxb8
tcpSessionWrite(PxSocketTcp self, PxBuffer8* buffer)
{
    printf(TRACE " Scrittura risposta di " YLW("%lliB") ": ",
        buffer->size);

    pxb8 state = pxSocketTcpWrite(self, buffer);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

pxb8
tcpSessionRead(PxSocketTcp self, PxBuffer8* buffer)
{
    printf(TRACE " Lettura richiesta ");

    pxb8 state = pxSocketTcpRead(self, buffer);

    printf("di " YLW("%lliB") ": ", buffer->size);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

#endif // TCP_SERVER_C
