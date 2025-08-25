#include "../export.h"

#include <stdio.h>

#define CLIENT_MSG pxs8("Ciao, sono il client!")

#define CLIENT_ARG_ADDR pxs8("--server-addr=")
#define CLIENT_ARG_PORT pxs8("--server-port=")

typedef struct ClientConfig
{
    PxAddress addr;
    pxu16     port;
}
ClientConfig;

typedef struct ClientState
{
    PxSocketUdp socket;
    PxBuffer8   request;
    PxBuffer8   response;
}
ClientState;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    ClientConfig config = {
        .addr = pxAddressLocalHost(PX_ADDRESS_TYPE_IP4),
        .port = 8000,
    };

    if (argc > 1) {
        PxFormatOptions options = pxFormatOptionsRadix(10);

        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8BeginsWith(arg, CLIENT_ARG_ADDR) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_ADDR);
                arg = pxString8TrimSpaces(arg);

                pxAddressFromString(&config.addr, PX_ADDRESS_TYPE_IP4, arg);
            }

            if (pxString8BeginsWith(arg, CLIENT_ARG_PORT) != 0) {
                arg = pxString8TrimPrefix(arg, CLIENT_ARG_PORT);
                arg = pxString8TrimSpaces(arg);

                pxU16FromString8(&config.port, options, arg);
            }
        }
    }

    ClientState client = {0};

    client.socket = udpClientStart(&arena, PX_ADDRESS_TYPE_IP4);

    if (client.socket == 0) return 1;

    client.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    client.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxBuffer8WriteStringTail(&client.request, CLIENT_MSG);

    udpClientWrite(client.socket, &client.request,
        config.addr, config.port);

    PxAddress addr = {0};
    pxu16     port = 0;

    pxb8 state = udpClientRead(client.socket, &client.response, &addr, &port);

    if (state != 0) {
        if (port == config.port && pxAddressIsEqual(addr, config.addr) != 0) {
            PxString8 string = pxBuffer8ReadStringHead(
                &client.response, &arena, client.response.size);

            printf(INFO " " BLU("'%s'") "\n", string.memory);
        } else
            printf(ERROR " Indirizzo o porta inaspettati...\n");
    }

    udpClientStop(client.socket);

    pxNetworkStop();
}
