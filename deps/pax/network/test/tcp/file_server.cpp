#include "message.hpp"

#include <stdio.h>

int
main()
{
    Arena arena = system_reserve(4);

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    if (system_network_start() == 0) return 1;

    Address    server_addr = address_any(ADDRESS_KIND_IP4);
    Socket_TCP server      = server_start(&arena, SERVER_PORT, server_addr);

    if (server == 0) return 1;

    Socket_TCP session = session_open(server, &arena);

    if (session == 0) return 1;

    server_stop(server);

    b32 loop = 1;

    while (loop) {
        session_read(session, &request);

        u8 type = buffer_decode_msg_type(&request);

        if (type == MESSAGE_EXIT) {
            loop = 0;

            continue;
        }

        if (type == MESSAGE_FILE_NAME) {
            uptr offset = arena_offset(&arena);
            str8 name   = buffer_decode_msg_file_name(&request, &arena);

            char* memory = pax_cast(char*, name.memory);
            int   length = pax_cast(int, name.length);

            printf(INFO " File richiesto = " PRP("'%.*s'") "\n", length, memory);

            FILE* file = fopen(memory, "rb");
            uptr  size = 0;

            if (file != 0) {
                fseek(file, 0, SEEK_END);

                size = ftell(file);

                fseek(file, 0, SEEK_SET);
            }

            buffer_encode_msg_file_size(&response, pax_cast(u64, size));

            session_write(session, response);

            for (uptr temp = 0; temp < size; temp += response.size) {
                response.size = fread(response.memory, 1,
                    response.length, file);

                if (response.size == 0) break;

                session_write(session, response);
            }

            fclose(file);

            arena_rewind(&arena, offset);

            continue;
        }
    }

    session_close(session);

    system_network_stop();
}
