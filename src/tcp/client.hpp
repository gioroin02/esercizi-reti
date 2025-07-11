#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "imports.hpp"

Socket_TCP
client_tcp_start(Arena* arena, Address_Kind kind);

void
client_tcp_stop(Socket_TCP self);

b32
client_tcp_connect(Socket_TCP self, u16 port, Address address);

b32
client_tcp_write(Socket_TCP self, Buffer* buffer);

b32
client_tcp_read(Socket_TCP self, Buffer* buffer);

#endif // TCP_CLIENT_HPP
