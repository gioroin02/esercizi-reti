#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "imports.hpp"

Socket_TCP
server_start(Arena* arena, u16 port, Address address);

void
server_stop(Socket_TCP self);

Socket_TCP
session_open(Socket_TCP self, Arena* arena);

void
session_close(Socket_TCP self);

b32
session_write(Socket_TCP self, Buffer buffer);

void
session_read(Socket_TCP self, Buffer* buffer);

#endif // TCP_SERVER_HPP
