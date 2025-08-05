#include "../exports.hpp"

#include <stdio.h>

static const str8 CLIENT_ARG_ADDR = pax_str8("--addr=");
static const str8 CLIENT_ARG_PORT = pax_str8("--port=");

struct Server
{
    Address addr = address_localhost(ADDRESS_TYPE_IP4);
    u16     port = 8000;
};

struct Client
{
    Socket_TCP socket = 0;

    buf8 request  = {};
    buf8 response = {};
};

str8
stdin_read_str8(Arena* arena, usiz length);

int
main(int argc, char** argv)
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    Server server = {};

    if (argc != 1) {
        Format_Options opts = format_options_simple(10);

        for (usiz i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, CLIENT_ARG_ADDR) != 0) {
                arg = str8_trim_prefix(arg, CLIENT_ARG_ADDR);
                arg = str8_trim_spaces(arg);

                address_from_str8(arg, ADDRESS_TYPE_IP4, &server.addr);
            }

            if (str8_starts_with(arg, CLIENT_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, CLIENT_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server.port);
            }
        }
    }

    Client client = {};

    client.socket = client_tcp_start(&arena, ADDRESS_TYPE_IP4);

    if (client.socket == 0) return 1;

    if (client_tcp_connect(client.socket, server.port, server.addr) == 0)
        return 1;

    client.request  = buf8_reserve(&arena, MEMORY_KIB);
    client.response = buf8_reserve(&arena, MEMORY_KIB);

    usiz offset = arena_offset(&arena);
    u32  number = 0;

    do {
        printf("-> ");

        str8 input = stdin_read_str8(&arena, 32);
        str8 line  = str8_split_on(input, pax_str8("\n"), &input);

        Format_Options opts = format_options(10,
            FORMAT_FLAG_LEADING_ZERO | FORMAT_FLAG_LEADING_PLUS);

        if (u32_from_str8(line, opts, &number) == 0)
            number = 0;

        number = u32_net_from_host(number);

        buf8_write_mem8_tail(&client.request,
            pax_as_u8p(&number), pax_size_of(u32));

        client_tcp_write(client.socket, &client.request);

        if (client_tcp_read(client.socket, &client.response) != 0) {
            u32 result = 0;

            buf8_read_mem8_head(&client.response,
                pax_as_u8p(&result), pax_size_of(u32));

            result = u32_host_from_net(result);

            printf(INFO " result = " YLW("%u")  "\n", result);
        }

        arena_rewind(&arena, offset);
    } while (number != 0);

    client_tcp_stop(client.socket);

    system_network_stop();
}

str8
stdin_read_str8(Arena* arena, usiz length)
{
    str8 result = str8_reserve(arena, length);

    fgets(pax_as(char*, result.memory),
        pax_as(int, result.length), stdin);

    return result;
}
