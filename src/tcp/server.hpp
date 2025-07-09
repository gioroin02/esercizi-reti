#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "imports.hpp"

Socket_TCP
server_tcp_start(Arena* arena, u16 port, Address address);

void
server_tcp_stop(Socket_TCP self);

Socket_TCP
session_tcp_open(Arena* arena, Socket_TCP server);

void
session_tcp_close(Socket_TCP self);

b32
session_tcp_write(Socket_TCP self, Buffer buffer);

b32
session_tcp_read(Socket_TCP self, Buffer* buffer);

#endif // TCP_SERVER_HPP
