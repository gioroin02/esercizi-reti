#include "../export.h"

#include <stdio.h>

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

pxiword
fileRead(void* self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword amount = 0;

    fgets(pxCast(char*, memory), size, self);

    while (memory[amount] != 0)
        amount += 1;

    buffer->size += amount;
    buffer->tail  = (buffer->tail + amount) % buffer->length;

    return amount;
}

PxReader
fileReader(void* self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &fileRead,
    };
}

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

    PxBuffer8 input_buffer = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    PxReader  input_reader = fileReader(stdin, &input_buffer);

    ClientState client = {0};

    client.socket = tcpClientStart(&arena, PX_ADDRESS_TYPE_IP4);

    if (client.socket == 0) return 1;

    if (tcpClientConnect(client.socket, config.addr, config.port) == 0)
        return 1;

    client.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    client.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxiword offset = pxArenaOffset(&arena);
    pxu32   number = 0;

    do {
        printf("-> ");

        PxString8 line =
            pxReaderLine(&input_reader, &arena, PX_MEMORY_KIB);

        PxFormatOptions options = pxFormatOptions(10,
            PX_FORMAT_FLAG_LEADING_ZERO | PX_FORMAT_FLAG_LEADING_PLUS);

        if (pxU32FromString8(&number, options, line) == 0)
            number = 0;

        number = pxU32NetFromLocal(number);

        pxBuffer8Clear(&client.request);

        pxBuffer8WriteMemoryTail(&client.request,
            pxCast(pxu8*, &number), PX_U32_SIZE);

        tcpClientWrite(client.socket, &client.request);

        pxb8 state = tcpClientRead(client.socket, &client.response);

        if (state != 0) {
            pxu32 result = 0;

            pxBuffer8ReadMemoryHead(&client.response,
                pxCast(pxu8*, &result), PX_U32_SIZE);

            result = pxU32LocalFromNet(result);

            printf(INFO " result = " YLW("%lu")  "\n", result);
        }

        pxArenaRewind(&arena, offset);
    } while (number != 0);

    tcpClientStop(client.socket);

    pxNetworkStop();
}
