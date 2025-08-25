#ifndef TCP_CLIENT_C
#define TCP_CLIENT_C

#include "client.h"

#include <stdio.h>

PxSocketTcp
tcpClientStart(PxArena* arena, PxAddressType type)
{
    return pxSocketTcpCreate(arena, type);
}

void
tcpClientStop(PxSocketTcp self)
{
    pxSocketTcpDestroy(self);
}

pxb8
tcpClientConnect(PxSocketTcp self, PxAddress address, pxu16 port)
{
    printf(TRACE " Apertura sessione con {addr = [");

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

    printf("], port = " YLW("%u") "}: ", port);

    pxb8 state = pxSocketTcpConnect(self, address, port);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

pxb8
tcpClientWrite(PxSocketTcp self, PxBuffer8* buffer)
{
    printf(TRACE " Scrittura richiesta di " YLW("%lliB") ": ",
        buffer->size);

    pxb8 state = pxSocketTcpWrite(self, buffer);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

pxb8
tcpClientRead(PxSocketTcp self, PxBuffer8* buffer)
{
    printf(TRACE " Lettura risposta ");

    pxb8 state = pxSocketTcpRead(self, buffer);

    printf("di " YLW("%lliB") ": ", buffer->size);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

#endif // TCP_CLIENT_C
