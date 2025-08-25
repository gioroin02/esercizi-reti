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
    PxSocketTcp socket;
}
ServerState;

typedef struct ServerSession
{
    PxSocketTcp socket;
    PxBuffer8   request;
    PxBuffer8   response;
}
ServerSession;

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

    server.socket = tcpServerStart(&arena,
        pxAddressAny(PX_ADDRESS_TYPE_IP4), config.port);

    if (server.socket == 0) return 1;

    ServerSession session = {0};

    session.socket = tcpSessionOpen(server.socket, &arena);

    session.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    session.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    tcpServerStop(server.socket);

    pxiword offset = pxArenaOffset(&arena);
    pxu32   result = 0;
    pxu32   number = 0;

    do {
        pxb8 state = tcpSessionRead(session.socket,
            &session.request);

        if (state == 0) continue;

        number = 0;

        pxBuffer8ReadMemoryHead(&session.request,
            pxCast(pxu8*, &number), PX_U32_SIZE);

        number  = pxU32LocalFromNet(number);
        result += number;

        printf(INFO " number = " YLW("%lu") ", result = " YLW("%lu") "\n",
            number, result);

        pxu32 temp = pxU32NetFromLocal(result);

        pxBuffer8Clear(&session.response);

        pxBuffer8WriteMemoryTail(&session.response,
            pxCast(pxu8*, &temp), PX_U32_SIZE);

        tcpSessionWrite(session.socket,
            &session.response);
    } while (number != 0);

    tcpSessionClose(session.socket);

    pxNetworkStop();
}
