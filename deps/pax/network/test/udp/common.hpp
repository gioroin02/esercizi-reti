#ifndef COMMON_HPP
#define COMMON_HPP

#include "../../exports.hpp"

using namespace pax;

//
// Defines
//

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GRN(str) "\x1b[32m" str "\x1b[0m"
#define YLW(str) "\x1b[33m" str "\x1b[0m"
#define BLU(str) "\x1b[34m" str "\x1b[0m"
#define PRP(str) "\x1b[35m" str "\x1b[0m"

#define SUCC GRN("SUCCESSO")
#define FAIL RED("FALLIMENTO")

#define FATAL "[" PRP("FATAL") "]"
#define ERROR "[" RED("ERROR") "]"
#define WARN  "[" YLW("WARN")  "]"
#define INFO  "[" BLU("INFO")  "]"
#define DEBUG "[" GRN("DEBUG") "]"

//
// Values
//

static const str8 CLIENT_ADDR = pax_str8("127.0.0.1");
static const u16  CLIENT_PORT = 20 * 1000;

static const str8 SERVER_ADDR = pax_str8("127.0.0.1");
static const u16  SERVER_PORT = 35 * 1000;

//
// Procs
//

Socket_UDP
client_start(Arena* arena, Address_Kind kind);

void
client_stop(Socket_UDP self);

b32
client_write(Socket_UDP self, Buffer buffer, u16 port, Address address);

void
client_read(Socket_UDP self, Buffer* buffer, u16* port, Address* address);

Socket_UDP
server_start(Arena* arena, u16 port, Address address);

void
server_stop(Socket_UDP self);

b32
server_write(Socket_UDP self, Buffer buffer, u16 port, Address address);

void
server_read(Socket_UDP self, Buffer* buffer, u16* port, Address* address);

str8
str8_read_from_stdin(Arena* arena, uptr length);

#endif // COMMON_HPP
