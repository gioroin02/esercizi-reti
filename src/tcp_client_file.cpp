#include "tcp/exports.hpp"

#include <stdio.h>

enum Command_Type
{
    COMMAND_EXIT,
    COMMAND_FILE_CONTENT,
    COMMAND_FILE_SIZE,
};

static const str8 CLIENT_ARG_ADDR = pax_str8("--addr=");
static const str8 CLIENT_ARG_PORT = pax_str8("--port=");

static const str8 CLIENT_CMD_EXIT = pax_str8("exit");
static const str8 CLIENT_CMD_FILE = pax_str8("file ");

str8
stdin_read_str8(Arena* arena, uptr length)
{
    str8 result = str8_reserve(arena, length);

    fgets(pax_cast(char*, result.memory),
        pax_cast(int, result.length), stdin);

    return result;
}

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    Address server_addr = {};
    u16     server_port = 8000;

    address_from_str8(pax_str8("localhost"), ADDRESS_KIND_IP4, &server_addr);

    if (argc != 1) {
        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, CLIENT_ARG_ADDR) != 0) {
                arg = str8_trim_prefix(arg, CLIENT_ARG_ADDR);
                arg = str8_trim_spaces(arg);

                address_from_str8(arg, ADDRESS_KIND_IP4, &server_addr);
            }

            if (str8_starts_with(arg, CLIENT_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, CLIENT_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server_port);
            }
        }
    }

    Socket_TCP client = client_tcp_start(&arena, ADDRESS_KIND_IP4);

    if (client == 0) return 1;

    if (client_tcp_connect(client, server_port, server_addr) == 0)
        return 1;

    buf8 request  = buf8_reserve(&arena, MEMORY_KIB);
    buf8 response = buf8_reserve(&arena, MEMORY_KIB);

    uptr offset = arena_offset(&arena);
    b32  loop   = 1;

    do {
        printf("-> ");

        str8 input = stdin_read_str8(&arena, 64);
        str8 line  = str8_split_on(input, pax_str8("\n"), &input);

        if (str8_starts_with(line, CLIENT_CMD_EXIT) != 0) {
            u8 type = COMMAND_EXIT;

            buf8_write_mem8_tail(&request, &type, 1);

            client_tcp_write(client, &request);

            break;
        }

        if (str8_starts_with(line, CLIENT_CMD_FILE) != 0) {
            str8 name = line;

            u8   type = COMMAND_FILE_SIZE;
            uptr size = 0;

            name = str8_trim_prefix(name, CLIENT_CMD_FILE);
            name = str8_trim_spaces(name);

            buf8_write_mem8_tail(&request, &type, 1);
            buf8_write_str8_tail(&request, name);

            printf(INFO " Requesting size of file " BLU("'%.*s'") "\n",
                pax_cast(int, name.length), name.memory);

            client_tcp_write(client, &request);

            if (client_tcp_read(client, &response) == 0)
                break;

            u32 number = 0;

            buf8_read_mem8_head(&response,
                pax_cast(u8*, &number), pax_size_of(u32));

            printf(INFO " Requested file is " YLW("%u") " bytes long\n", number);

            if (number != 0) {
                type = COMMAND_FILE_CONTENT;

                buf8_write_mem8_tail(&request, &type, 1);
                buf8_write_str8_tail(&request, name);

                printf(INFO " Requesting content of file " BLU("'%.*s'") "\n",
                    pax_cast(int, name.length), name.memory);

                client_tcp_write(client, &request);

                for (uptr i = 0; i < number;) {
                    if (client_tcp_read(client, &response) == 0)
                        break;

                    i += response.size;

                    // TODO: Write to file

                    buf8_normalize(&response);

                    printf(TRACE " %.*s", pax_cast(int, response.size),
                        response.memory);

                    buf8_clear(&response);
                }
            }
        }

        if (response.size != 0)
            printf(ERROR " Unhandled data\n");

        arena_rewind(&arena, offset);
    } while (loop != 0);

    client_tcp_stop(client);

    system_network_stop();
}
