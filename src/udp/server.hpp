#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include "imports.hpp"

Socket_UDP
server_udp_start(Arena* arena, u16 port, Address address);

void
server_udp_stop(Socket_UDP self);

b32
server_udp_write(Socket_UDP self, Buffer buffer, u16 port, Address address);

b32
server_udp_read(Socket_UDP self, Buffer* buffer, u16* port, Address* address);

#endif // UDP_SERVER_HPP
