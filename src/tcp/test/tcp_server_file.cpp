#include "../exports.hpp"

#include "../../pax/storage/exports.hpp"

#include <stdio.h>

static const str8 SERVER_PATH = pax_str8("./data/http_server");

static const str8 SERVER_ARG_PORT = pax_str8("--port=");
static const str8 SERVER_ARG_PATH = pax_str8("--path=");

enum Command_Type
{
    COMMAND_EXIT,
    COMMAND_FILE_CONTENT,
    COMMAND_FILE_SIZE,
};

struct Server
{
    Socket_TCP socket = 0;

    u16  port = 8000;
    str8 path = SERVER_PATH;
};

struct Session
{
    Socket_TCP socket = 0;

    buf8 request  = {};
    buf8 response = {};
};

void
file_server_on_content(Arena* arena, Server* server, Session* session);

void
file_server_on_size(Arena* arena, Server* server, Session* session);

int
main(int argc, char** argv)
{
    Arena arena = system_reserve(16);

    if (system_network_start() == 0) return 1;

    Server server = {};

    if (argc != 1) {
        Format_Options opts = format_options_base(10);

        for (uptr i = 1; i < argc; i += 1) {
            str8 arg = pax_str8_max(argv[i], 128);

            if (str8_starts_with(arg, SERVER_ARG_PORT) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PORT);
                arg = str8_trim_spaces(arg);

                u16_from_str8(arg, opts, &server.port);
            }

            if (str8_starts_with(arg, SERVER_ARG_PATH) != 0) {
                arg = str8_trim_prefix(arg, SERVER_ARG_PATH);
                arg = str8_trim_spaces(arg);

                server.path = str8_copy(&arena, arg);
            }
        }
    }

    server.socket = server_tcp_start(&arena, server.port, address_any(ADDRESS_KIND_IP4));

    if (server.socket == 0) return 1;

    Session session = {};

    session.socket = session_tcp_open(&arena, server.socket);

    server_tcp_stop(server.socket);

    if (session.socket == 0) return 1;

    session.request  = buf8_reserve(&arena, MEMORY_KIB);
    session.response = buf8_reserve(&arena, MEMORY_KIB);

    uptr offset = arena_offset(&arena);
    b32  loop   = 1;

    do {
        if (session_tcp_read(session.socket, &session.request) == 0)
            break;

        u8 type = 0;

        buf8_read_mem8_head(&session.request, &type, 1);

        switch (type) {
            case COMMAND_FILE_CONTENT: {
                file_server_on_content(&arena, &server, &session);
            } break;

            case COMMAND_FILE_SIZE: {
                file_server_on_size(&arena, &server, &session);
            } break;

            default: { loop = 0; } break;
        }

        arena_rewind(&arena, offset);
    } while (loop != 0);

    session_tcp_close(session.socket);

    system_network_stop();
}

void
file_server_on_content(Arena* arena, Server* server, Session* session)
{
    str8 name = buf8_read_str8_head(&session->request, arena,
        session->request.size);

    printf(INFO " Requested content of file " BLU("'%.*s'") "\n",
        pax_cast(int, name.length), name.memory);

    File_Props properties = {};

    file_props(&properties, arena, server->path, name);

    uptr size = file_size(&properties);
    File file = file_open(arena, server->path, name, FILE_PERM_READ);

    buf8_clear(&session->response);

    while (file != 0 && size > 0) {
        if (file_read(file, &session->response) == 0)
            break;

        size -= session->response.size;

        session_tcp_write(session->socket, &session->response);
    }

    file_close(file);
}

void
file_server_on_size(Arena* arena, Server* server, Session* session)
{
    str8 name = buf8_read_str8_head(&session->request, arena,
        session->request.size);

    printf(INFO " Requested size of file " BLU("'%.*s'") "\n",
        pax_cast(int, name.length), name.memory);

    File_Props properties = {};

    file_props(&properties, arena, server->path, name);

    u32 size = file_size(&properties);

    buf8_clear(&session->response);

    buf8_write_mem8_tail(&session->response, pax_cast(u8*, &size),
        pax_size_of(u32));

    session_tcp_write(session->socket, &session->response);
}
