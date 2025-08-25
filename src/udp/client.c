#ifndef UDP_CLIENT_C
#define UDP_CLIENT_C

#include "client.h"

#include <stdio.h>

PxSocketUdp
udpClientStart(PxArena* arena, PxAddressType type)
{
    return pxSocketUdpCreate(arena, type);
}

void
udpClientStop(PxSocketUdp self)
{
    pxSocketUdpDestroy(self);
}

pxb8
udpClientWrite(PxSocketUdp self, PxBuffer8* buffer, PxAddress address, pxu16 port)
{
    printf(TRACE " Scrittura richiesta di " YLW("%lliB") " a {addr = [",
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
udpClientRead(PxSocketUdp self, PxBuffer8* buffer, PxAddress* address, pxu16* port)
{
    printf(TRACE " Lettura risposta ");

    pxb8 state = pxSocketUdpReadAddr(self, buffer, address, port);

    printf("di " YLW("%lliB") " da {addr = [", buffer->size);

    if (state != 0 && address != 0) {
        switch (address->type) {
            case PX_ADDRESS_TYPE_IP4: {
                for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1) {
                    printf(YLW("%u"), address->ip4.memory[i]);

                    if (i + 1 != PX_ADDRESS_IP4_GROUPS)
                        printf(YLW("."));
                }
            } break;

            case PX_ADDRESS_TYPE_IP6: {
                for (pxiword i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1) {
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

#endif // UDP_CLIENT_C
