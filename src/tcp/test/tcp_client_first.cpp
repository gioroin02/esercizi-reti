#include "../exports.hpp"

#include <stdio.h>

static const str8 CLIENT_MSG = pax_str8("Ciao, sono il client!");

static const str8 CLIENT_ARG_ADDR = pax_str8("--addr=");
static const str8 CLIENT_ARG_PORT = pax_str8("--port=");

struct Server
{
    Address addr = address_localhost(ADDRESS_TYPE_IP4);
    u16     port = 8000;
};

struct Client
{
    Socket_UDP socket = 0;

    buf8 request  = {};
    buf8 response = {};
};

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

    buf8_write_str8_tail(&client.request, CLIENT_MSG);

    client_tcp_write(client.socket, &client.request);

    if (client_tcp_read(client.socket, &client.response) != 0) {
        str8 string = buf8_read_str8_head(&client.response,
            &arena, client.response.size);

        printf(INFO " " BLU("'%.*s'") "\n",
            pax_as(int, string.length), string.memory);
    }

    client_tcp_stop(client.socket);

    system_network_stop();
}
