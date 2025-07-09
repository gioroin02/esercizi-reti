#include "tcp/exports.hpp"
#include "pax/storage/exports.hpp"

#include <stdio.h>

enum Command_Type
{
    COMMAND_EXIT,
    COMMAND_FILE_CONTENT,
    COMMAND_FILE_SIZE,
};

static const str8 SERVER_DATA_PATH = pax_str8("./data/file_server");

static const str8 SERVER_ARG_PORT = pax_str8("--port=");

void
file_server_on_content(Socket_TCP session, Arena* arena, str8 name, Buffer* response);

void
file_server_on_size(Socket_TCP session, Arena* arena, str8 name, Buffer* response);

int
main(int argc, const char* argv[])
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    u16 server_port = 8000;

    if (argc != 1) {
        Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server_port);
            }
        }
    }

    Socket_TCP server = server_tcp_start(&arena,
        server_port, address_any(ADDRESS_KIND_IP4));

    if (server == 0) return 1;

    Socket_TCP session = session_tcp_open(&arena, server);

    if (session == 0) return 1;

    Buffer request  = buffer_reserve(&arena, MEMORY_KIB);
    Buffer response = buffer_reserve(&arena, MEMORY_KIB);

    server_tcp_stop(server);

    b32 loop = 1;

    do {
        if (session_tcp_read(session, &request) == 0)
            break;

        u8 type = 0;

        buffer_read_mem8(&request, 0, &type, 1);

        switch (type) {
            case COMMAND_FILE_CONTENT: {
                str8 name = str8_make(request.memory + 1,
                    request.size - 1);

                file_server_on_content(session, &arena, name, &response);
            } break;

            case COMMAND_FILE_SIZE: {
                str8 name = str8_make(request.memory + 1,
                    request.size - 1);

                file_server_on_size(session, &arena, name, &response);
            } break;

            default: { loop = 0; } break;
        }
    } while (loop != 0);

    session_tcp_close(session);

    system_network_stop();
}

void
file_server_on_content(Socket_TCP session, Arena* arena, str8 name, Buffer* response)
{
    printf(INFO " Requested content of file " BLU("'%.*s'") "\n",
        pax_cast(int, name.length), name.memory);

    File_Props props = {};

    file_props(&props, arena, SERVER_DATA_PATH, name);

    uptr size = file_size(&props);
    File file = file_open(arena, SERVER_DATA_PATH, name, FILE_PERM_READ);

    while (file != 0 && size != 0) {
        buffer_clear(response);

        if (file_read(file, response) == 0)
            break;

        session_tcp_write(session, *response);
    }

    file_close(file);
}

void
file_server_on_size(Socket_TCP session, Arena* arena, str8 name, Buffer* response)
{
    printf(INFO " Requested size of file " BLU("'%.*s'") "\n",
        pax_cast(int, name.length), name.memory);

    File_Props     props = {};
    Format_Options opts  = format_options(10, FORMAT_FLAG_NONE);

    file_props(&props, arena, SERVER_DATA_PATH, name);

    buffer_clear(response);
    buffer_write_uptr(response, opts, file_size(&props));

    session_tcp_write(session, *response);
}
