#include "../export.h"

#include <stdio.h>

#define SERVER_ARG_PORT pxs8("--server-port=")

typedef struct ServerConfig
{
    pxu16 port;
}
ServerConfig;

typedef struct ServerState
{
    PxSocketUdp socket;
    PxBuffer8   request;
    PxBuffer8   response;
}
ServerState;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    ServerConfig config = {
        .port = 8000,
    };

    if (argc > 1) {
        PxFormatOptions options = pxFormatOptionsRadix(10);

        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8BeginsWith(arg, SERVER_ARG_PORT) != 0) {
                arg = pxString8TrimPrefix(arg, SERVER_ARG_PORT);
                arg = pxString8TrimSpaces(arg);

                pxU16FromString8(&config.port, options, arg);
            }
        }
    }

    ServerState server = {0};

    server.socket = udpServerStart(&arena,
        pxAddressAny(PX_ADDRESS_TYPE_IP4), config.port);

    if (server.socket == 0) return 1;

    server.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    server.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxiword offset = pxArenaOffset(&arena);
    pxu32   result = 0;
    pxu32   number = 0;

    do {
        PxAddress addr = {0};
        pxu16     port = 0;

        pxb8 state = udpServerRead(server.socket,
            &server.request, &addr, &port);

        if (state == 0) continue;

        number = 0;

        pxBuffer8ReadMemoryHead(&server.request,
            pxCast(pxu8*, &number), PX_U32_SIZE);

        number  = pxU32LocalFromNet(number);
        result += number;

        printf(INFO " number = " YLW("%lu") ", result = " YLW("%lu") "\n",
            number, result);

        pxu32 temp = pxU32NetFromLocal(result);

        pxBuffer8Clear(&server.response);

        pxBuffer8WriteMemoryTail(&server.response,
            pxCast(pxu8*, &temp), PX_U32_SIZE);

        udpServerWrite(server.socket,
            &server.response, addr, port);
    } while (number != 0);

    udpServerStop(server.socket);

    pxNetworkStop();
}
