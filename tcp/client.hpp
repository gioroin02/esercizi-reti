#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "imports.hpp"

Socket_TCP
client_start(Arena* arena, Address_Kind kind);

void
client_stop(Socket_TCP self);

b32
client_connect(Socket_TCP self, u16 port, Address address);

b32
client_write(Socket_TCP self, Buffer buffer);

b32
client_read(Socket_TCP self, Buffer* buffer);

#endif // TCP_CLIENT_HPP
