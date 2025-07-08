#include "tcp/exports.hpp"

#include <stdio.h>

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

    u16     server_port = 8000;
    Address server_addr = {};

    address_from_str8(pax_str8("localhost"), ADDRESS_KIND_IP4, &server_addr);

    if (argc == 3) {
        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        str8 arg1 = str8_count_max(pax_cast(const u8*, argv[1]), 128);
        str8 arg2 = str8_count_max(pax_cast(const u8*, argv[2]), 128);

        u16_from_str8(arg1, opts, &server_port);

        address_from_str8(arg2, ADDRESS_KIND_IP4, &server_addr);
    }

    Socket_TCP client = client_start(&arena, ADDRESS_KIND_IP4);

    if (client == 0) return 1;

    if (client_connect(client, server_port, server_addr) == 0)
        return 1;

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    u32 number = 0;

    do {
        printf("-> ");

        str8 input  = stdin_read_str8(&arena, 32);
        str8 line   = str8_split_on(input, pax_str8("\n"), &input);

        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        if (u32_from_str8(line, opts, &number) == 0)
            number = 0;

        number = u32_net_from_host(number);

        buffer_clear(&request);

        buffer_write_mem8(&request, pax_cast(u8*, &number),
            pax_size_of(u32));

        client_write(client, request);
    } while (number != 0);

    client_read(client, &response);

    buffer_read_mem8(&response, 0, pax_cast(u8*, &number),
        pax_size_of(u32));

    number = u32_host_from_net(number);

    printf(INFO " result = %lu\n", number);

    client_stop(client);

    system_network_stop();
}
