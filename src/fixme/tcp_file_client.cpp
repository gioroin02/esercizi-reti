#include "message.hpp"

#include <stdio.h>

static const str8 EXIT_CMD = pax_str8("exit");
static const str8 FILE_CMD = pax_str8("file ");

int
main()
{
    Arena arena = system_reserve(4);

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    if (system_network_start() == 0) return 1;

    Address server_addr = {};

    if (str8_parse_address(SERVER_ADDR, ADDRESS_KIND_IP4, &server_addr) == 0)
        return 1;

    Socket_TCP client = client_start(&arena, ADDRESS_KIND_IP4);

    if (client == 0) return 1;

    if (client_connect(client, SERVER_PORT, server_addr) == 0)
        return 1;

    b32 loop = 1;

    while (loop != 0) {
        uptr offset = arena_offset(&arena);

        printf("-> ");

        str8 input = str8_read_from_stdin(&arena, MEMORY_KIB);
        str8 line  = {};

        line = str8_split_on(input, pax_str8("\n"), &input);

        if (str8_is_equal(line, EXIT_CMD) != 0) {
            buffer_encode_msg_exit(&request);

            client_write(client, request);
            arena_rewind(&arena, offset);

            loop = 0;

            continue;
        }

        if (str8_starts_with(line, FILE_CMD) != 0) {
            line = str8_trim_prefix(line, FILE_CMD);
            line = str8_trim_spaces(line);

            buffer_encode_msg_file_name(&request, line);

            client_write(client, request);
            client_read(client, &response);

            u8 type = buffer_decode_msg_type(&response);

            if (type == MESSAGE_FILE_SIZE) {
                u64 size = buffer_decode_msg_file_size(&response);

                printf(INFO " Dimensione file remoto = {" YLW("%llu") "}\n", size);

                Str_Builder builder = str_builder_make(&arena);

                str_builder_str8(&builder, pax_str8("./"));
                str_builder_str8(&builder, str8_slice_since_last(line, pax_str8("/")));

                str8 name = str8_from_str_builder(&builder);

                char* memory = pax_cast(char*, name.memory);
                int   length = pax_cast(int, name.length);

                printf(INFO " Scrittura in " BLU("'%.*s'") "\n", length, memory);

                FILE* file = fopen(memory, "wb");

                for (u64 temp = 0; temp < size; temp += response.size) {
                    client_read(client, &response);

                    if (response.size == 0) break;

                    if (file != 0) {
                        memory = pax_cast(char*, response.memory);
                        length = pax_cast(int, response.size);

                        fwrite(memory, 1, length, file);
                    }
                }

                fclose(file);
            }

            arena_rewind(&arena, offset);

            continue;
        }
    }

    client_stop(client);

    system_network_stop();
}
