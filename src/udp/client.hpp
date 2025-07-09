#ifndef UDP_CLIENT_HPP
#define UDP_CLIENT_HPP

#include "imports.hpp"

Socket_UDP
client_udp_start(Arena* arena, Address_Kind kind);

void
client_udp_stop(Socket_UDP self);

b32
client_udp_write(Socket_UDP self, Buffer buffer, u16 port, Address address);

b32
client_udp_read(Socket_UDP self, Buffer* buffer, u16* port, Address* address);

#endif // UDP_CLIENT_HPP
