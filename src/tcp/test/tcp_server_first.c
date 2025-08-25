#include "../export.h"

#include <stdio.h>

#define SERVER_MSG pxs8("Ciao, sono il server!")

#define SERVER_ARG_PORT     pxs8("--server-port=")
#define SERVER_ARG_LIFETIME pxs8("--server-lifetime=")

typedef struct ServerConfig
{
    pxu16 port;
    pxu32 lifetime;
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
        .port = 8000, .lifetime = 1,
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

            if (pxString8BeginsWith(arg, SERVER_ARG_LIFETIME) != 0) {
                arg = pxString8TrimPrefix(arg, SERVER_ARG_LIFETIME);
                arg = pxString8TrimSpaces(arg);

                pxU32FromString8(&config.lifetime, options, arg);
            }
        }
    }

    ServerState server = {0};

    server.socket = tcpServerStart(&arena,
        pxAddressAny(PX_ADDRESS_TYPE_IP4), config.port);

    if (server.socket == 0) return 1;

    pxiword offset = pxArenaOffset(&arena);

    for (pxu32 i = 0; i < config.lifetime; i += 1) {
        ServerSession session = {0};

        session.socket = tcpSessionOpen(server.socket, &arena);

        session.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
        session.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

        pxb8 state = tcpSessionRead(session.socket, &session.request);

        if (state != 0) {
            PxString8 string = pxBuffer8ReadStringHead(
                &session.request, &arena, session.request.size);

            printf(INFO " " BLU("'%s'") "\n", string.memory);

            pxBuffer8WriteStringTail(&session.response, SERVER_MSG);

            tcpSessionWrite(session.socket, &session.response);
        }

        tcpSessionClose(session.socket);

        pxArenaRewind(&arena, offset);
    }

    tcpServerStop(server.socket);

    pxNetworkStop();
}
