#ifndef PAX_NETWORK_SOCKET_TCP_CPP
#define PAX_NETWORK_SOCKET_TCP_CPP

#include "socket_tcp.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/socket_tcp.cpp"

    #define __Socket_TCP__ Windows_Socket_TCP

    #define __socket_tcp_create__      windows_socket_tcp_create
    #define __socket_tcp_destroy__     windows_socket_tcp_destroy
    #define __socket_tcp_get_address__ windows_socket_tcp_get_address
    #define __socket_tcp_get_port__    windows_socket_tcp_get_port
    #define __socket_tcp_bind__        windows_socket_tcp_bind
    #define __socket_tcp_listen__      windows_socket_tcp_listen
    #define __socket_tcp_connect__     windows_socket_tcp_connect
    #define __socket_tcp_accept__      windows_socket_tcp_accept
    #define __socket_tcp_write__       windows_socket_tcp_write
    #define __socket_tcp_read__        windows_socket_tcp_read

#else

    #error "Platform not supported or unknown"

#endif

#define PAX_SOCKET_TCP(self) pax_cast(__Socket_TCP__*, self)

namespace pax {

Socket_TCP
socket_tcp_create(Arena* arena, Address_Kind kind)
{
    return __socket_tcp_create__(arena, kind);
}

void
socket_tcp_destroy(Socket_TCP self)
{
    __socket_tcp_destroy__(PAX_SOCKET_TCP(self));
}

Address
socket_tcp_get_address(Socket_TCP self)
{
    return __socket_tcp_get_address__(PAX_SOCKET_TCP(self));
}

u16
socket_tcp_get_port(Socket_TCP self)
{
    return __socket_tcp_get_port__(PAX_SOCKET_TCP(self));
}

b32
socket_tcp_bind(Socket_TCP self, u16 port, Address address)
{
    return __socket_tcp_bind__(PAX_SOCKET_TCP(self), port, address);
}

b32
socket_tcp_listen(Socket_TCP self)
{
    return __socket_tcp_listen__(PAX_SOCKET_TCP(self));
}

b32
socket_tcp_connect(Socket_TCP self, u16 port, Address address)
{
    return __socket_tcp_connect__(PAX_SOCKET_TCP(self), port, address);
}

Socket_TCP
socket_tcp_accept(Socket_TCP self, Arena* arena)
{
    return __socket_tcp_accept__(PAX_SOCKET_TCP(self), arena);
}

b32
socket_tcp_write(Socket_TCP self, Buffer buffer)
{
    return __socket_tcp_write__(PAX_SOCKET_TCP(self), buffer);
}

b32
socket_tcp_read(Socket_TCP self, Buffer* buffer)
{
    return __socket_tcp_read__(PAX_SOCKET_TCP(self), buffer);
}

} // namespace pax

#endif // PAX_NETWORK_SOCKET_TCP_CPP
