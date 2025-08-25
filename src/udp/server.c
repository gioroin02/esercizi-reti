#ifndef UDP_SERVER_C
#define UDP_SERVER_C

#include "server.h"

#include <stdio.h>

PxSocketUdp
udpServerStart(PxArena* arena, PxAddress address, pxu16 port)
{
    pxiword     offset = pxArenaOffset(arena);
    PxSocketUdp result = pxSocketUdpCreate(arena, address.type);

    if (result != 0) {
        printf(TRACE " Attivazione porta " YLW("%u") ": ", port);

        pxb8 state = pxSocketUdpBind(result, address, port);

        printf("%s\n", state != 0 ? SUCC : FAIL);

        if (state != 0) return result;

        pxArenaRewind(arena, offset);
    }

    return 0;
}

void
udpServerStop(PxSocketUdp self)
{
    pxSocketUdpDestroy(self);
}

pxb8
udpServerWrite(PxSocketUdp self, PxBuffer8* buffer, PxAddress address, pxu16 port)
{
    printf(TRACE " Scrittura risposta di " YLW("%lliB") " a {addr = [",
        buffer->size);

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

    pxb8 state = pxSocketUdpWriteAddr(self, buffer, address, port);

    printf("%s\n", state != 0 ? SUCC : FAIL);

    return state;
}

pxb8
udpServerRead(PxSocketUdp self, PxBuffer8* buffer, PxAddress* address, pxu16* port)
{
    printf(TRACE " Lettura richiesta ");

    pxb8 state = pxSocketUdpReadAddr(self, buffer, address, port);

    printf("di " YLW("%lliB") " da {addr = [", buffer->size);

    if (state != 0 && address != 0) {
        switch (address->type) {
            case PX_ADDRESS_TYPE_IP4: {
                for (pxuword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1) {
                    printf(YLW("%u"), address->ip4.memory[i]);

                    if (i + 1 != PX_ADDRESS_IP4_GROUPS)
                        printf(YLW("."));
                }
            } break;

            case PX_ADDRESS_TYPE_IP6: {
                for (pxuword i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1) {
                    printf(YLW("%x"), address->ip6.memory[i]);

                    if (i + 1 != PX_ADDRESS_IP6_GROUPS)
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

#endif // UDP_SERVER_C
