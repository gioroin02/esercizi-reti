#include "../exports.hpp"

#include <stdio.h>

static const str8 CLIENT_ARG_ADDR = pax_str8("--addr=");
static const str8 CLIENT_ARG_PORT = pax_str8("--port=");

static const str8 CLIENT_CMD_EXIT = pax_str8("exit");
static const str8 CLIENT_CMD_FILE = pax_str8("file ");

enum Command_Type
{
    COMMAND_EXIT,
    COMMAND_FILE_CONTENT,
    COMMAND_FILE_SIZE,
};

struct Server
{
    Address addr = {};
    u16     port = 8000;
};

struct Client
{
    Socket_TCP socket = 0;

    buf8 request  = {};
    buf8 response = {};
};

str8
stdin_read_str8(Arena* arena, uptr length);

int
main(int argc, char** argv)
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    Server server = {};

    address_from_str8(pax_str8("localhost"), ADDRESS_KIND_IP4, &server.addr);

    if (argc != 1) {
        Format_Options opts = format_options_base(10);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, CLIENT_ARG_ADDR) != 0) {
                arg = str8_trim_prefix(arg, CLIENT_ARG_ADDR);
                arg = str8_trim_spaces(arg);

                address_from_str8(arg, ADDRESS_KIND_IP4, &server.addr);
            }

            if (str8_starts_with(arg, CLIENT_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, CLIENT_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server.port);
            }
        }
    }

    Client client = {};

    client.socket = client_tcp_start(&arena, ADDRESS_KIND_IP4);

    if (client.socket == 0) return 1;

    if (client_tcp_connect(client.socket, server.port, server.addr) == 0)
        return 1;

    client.request  = buf8_reserve(&arena, MEMORY_KIB);
    client.response = buf8_reserve(&arena, MEMORY_KIB);

    uptr offset = arena_offset(&arena);
    b32  loop   = 1;

    do {
        printf("-> ");

        str8 input = stdin_read_str8(&arena, 128);
        str8 line  = str8_split_on(input, pax_str8("\n"), &input);

        if (str8_starts_with(line, CLIENT_CMD_EXIT) != 0) {
            u8 type = COMMAND_EXIT;

            buf8_write_mem8_tail(&client.request, &type, 1);

            client_tcp_write(client.socket, &client.request);

            break;
        }

        if (str8_starts_with(line, CLIENT_CMD_FILE) != 0) {
            u8   type = COMMAND_FILE_SIZE;
            str8 name = line;

            name = str8_trim_prefix(name, CLIENT_CMD_FILE);
            name = str8_trim_spaces(name);

            buf8_write_mem8_tail(&client.request, &type, 1);
            buf8_write_str8_tail(&client.request, name);

            printf(INFO " Requesting size of file " BLU("'%.*s'") "\n",
                pax_cast(int, name.length), name.memory);

            client_tcp_write(client.socket, &client.request);

            if (client_tcp_read(client.socket, &client.response) == 0)
                break;

            u32 size = 0;

            buf8_read_mem8_head(&client.response,
                pax_cast(u8*, &size), pax_size_of(u32));

            printf(INFO " Requested file is " YLW("%uB") " long\n", size);

            if (size == 0) continue;

            type = COMMAND_FILE_CONTENT;

            buf8_clear(&client.request);

            buf8_write_mem8_tail(&client.request, &type, 1);
            buf8_write_str8_tail(&client.request, name);

            printf(INFO " Requesting content of file " BLU("'%.*s'") "\n",
                pax_cast(int, name.length), name.memory);

            client_tcp_write(client.socket, &client.request);

            printf(TRACE " size = %u\n", size);

            while (size > 0) {
                if (client_tcp_read(client.socket, &client.response) == 0)
                    break;

                size -= client.response.size;

                str8 string = buf8_read_str8_head(&client.response,
                    &arena, client.response.size);

                printf(TRACE " [%.*s]\n",
                    pax_cast(int, string.length), string.memory);

                printf(TRACE " size = %u, length = %llu\n", size, string.length);

                // TODO: Write to file
            }
        }

        arena_rewind(&arena, offset);
    } while (loop != 0);

    client_tcp_stop(client.socket);

    system_network_stop();
}

str8
stdin_read_str8(Arena* arena, uptr length)
{
    str8 result = str8_reserve(arena, length);

    fgets(pax_cast(char*, result.memory),
        pax_cast(int, result.length), stdin);

    return result;
}
