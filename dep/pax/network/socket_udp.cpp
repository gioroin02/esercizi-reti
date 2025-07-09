#ifndef PAX_NETWORK_SOCKET_UDP_CPP
#define PAX_NETWORK_SOCKET_UDP_CPP

#include "socket_udp.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/socket_udp.cpp"

    #define __Socket_UDP__ Windows_Socket_UDP

    #define __socket_udp_create__      windows_socket_udp_create
    #define __socket_udp_destroy__     windows_socket_udp_destroy
    #define __socket_udp_bind__        windows_socket_udp_bind
    #define __socket_udp_listen__      windows_socket_udp_listen
    #define __socket_udp_connect__     windows_socket_udp_connect
    #define __socket_udp_accept__      windows_socket_udp_accept
    #define __socket_udp_write__       windows_socket_udp_write
    #define __socket_udp_write_to__    windows_socket_udp_write_to
    #define __socket_udp_read__        windows_socket_udp_read
    #define __socket_udp_read_from__   windows_socket_udp_read_from

#else

    #error "Platform not supported or unknown"

#endif

#define PAX_SOCKET_UDP(self) pax_cast(__Socket_UDP__*, self)

namespace pax {

Socket_UDP
socket_udp_create(Arena* arena, Address_Kind kind)
{
    return __socket_udp_create__(arena, kind);
}

void
socket_udp_destroy(Socket_UDP self)
{
    __socket_udp_destroy__(PAX_SOCKET_UDP(self));
}

b32
socket_udp_bind(Socket_UDP self, u16 port, Address address)
{
    return __socket_udp_bind__(PAX_SOCKET_UDP(self), port, address);
}

b32
socket_udp_listen(Socket_UDP self)
{
    return __socket_udp_listen__(PAX_SOCKET_UDP(self));
}

b32
socket_udp_connect(Socket_UDP self, u16 port, Address address)
{
    return __socket_udp_connect__(PAX_SOCKET_UDP(self), port, address);
}

Socket_UDP
socket_udp_accept(Socket_UDP self, Arena* arena)
{
    return __socket_udp_accept__(PAX_SOCKET_UDP(self), arena);
}

b32
socket_udp_write(Socket_UDP self, Buffer buffer)
{
    return __socket_udp_write__(PAX_SOCKET_UDP(self), buffer);
}

b32
socket_udp_write_to(Socket_UDP self, Buffer buffer, u16 port, Address address)
{
    return __socket_udp_write_to__(PAX_SOCKET_UDP(self), buffer, port, address);
}

b32
socket_udp_read(Socket_UDP self, Buffer* buffer)
{
    return __socket_udp_read__(PAX_SOCKET_UDP(self), buffer);
}

b32
socket_udp_read_from(Socket_UDP self, Buffer* buffer, u16* port, Address *address)
{
    return __socket_udp_read_from__(PAX_SOCKET_UDP(self), buffer, port, address);
}

} // namespace pax

#endif // PAX_NETWORK_SOCKET_UDP_CPP
