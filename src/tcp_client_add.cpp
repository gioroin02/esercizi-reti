#include "tcp/exports.hpp"

#include <stdio.h>

static const str8 CLIENT_ARG_ADDR = pax_str8("--addr=");
static const str8 CLIENT_ARG_PORT = pax_str8("--port=");

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

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    uptr offset = arena_offset(&arena);
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

        buffer_write_mem8_tail(&request, pax_cast(u8*, &number),
            pax_size_of(u32));

        client_tcp_write(client, &request);

        arena_rewind(&arena, offset);
    } while (number != 0);

    if (client_tcp_read(client, &response) != 0) {
        u32 result = 0;

        buffer_read_mem8_head(&response, pax_cast(u8*, &result),
            pax_size_of(u32));

        result = u32_host_from_net(result);

        printf(INFO " result = " YLW("%u")  "\n", result);
    }

    client_tcp_stop(client);

    system_network_stop();
}
