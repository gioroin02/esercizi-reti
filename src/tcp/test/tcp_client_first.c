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
    PxSocketTcp socket;
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

    client.socket = tcpClientStart(&arena, PX_ADDRESS_TYPE_IP4);

    if (client.socket == 0) return 1;

    if (tcpClientConnect(client.socket, config.addr, config.port) == 0)
        return 1;

    client.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    client.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxBuffer8WriteStringTail(&client.request, CLIENT_MSG);

    tcpClientWrite(client.socket, &client.request);

    if (tcpClientRead(client.socket, &client.response) != 0) {
        PxString8 string = pxBuffer8ReadStringHead(
            &client.response, &arena, client.response.size);

        printf(INFO " " BLU("'%s'") "\n", string.memory);
    }

    tcpClientStop(client.socket);

    pxNetworkStop();
}
