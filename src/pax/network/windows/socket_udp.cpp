#ifndef PAX_NETWORK_WINDOWS_SOCKET_UDP_CPP
#define PAX_NETWORK_WINDOWS_SOCKET_UDP_CPP

#include "socket_udp.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <winsock2.h>
#include <ws2tcpip.h>

namespace pax {

#ifndef PAX_NETWORK_SOCK_ADDRESS
#define PAX_NETWORK_SOCK_ADDRESS

using Sock_Address = struct sockaddr;
using Sock_Storage = struct sockaddr_storage;
using Sock4        = struct sockaddr_in;
using Sock6        = struct sockaddr_in6;

static const isiz SOCK4_SIZE        = pax_size_of(Sock4);
static const isiz SOCK6_SIZE        = pax_size_of(Sock6);
static const isiz SOCK_STORAGE_SIZE = pax_size_of(Sock_Storage);

#define pax_as_sock_address(self) pax_as(Sock_Address*, self)

#define pax_as_sock4(self)   pax_as(Sock4*, self)
#define pax_sock4_port(self) pax_as_u16p(&pax_as_sock4(self)->sin_port)
#define pax_sock4_addr(self) pax_as_u8p(&pax_as_sock4(self)->sin_addr.s_addr)

#define pax_as_sock6(self)   pax_as(Sock6*, self)
#define pax_sock6_port(self) pax_as_u16p(&pax_as_sock6(self)->sin6_port)
#define pax_sock6_addr(self) pax_as_u16p(&pax_as_sock6(self)->sin6_addr.s6_addr)

#endif // PAX_NETWORK_SOCK_ADDRESS

struct Windows_Socket_UDP
{
    SOCKET       handle  = INVALID_SOCKET;
    Sock_Storage address = {};
};

Windows_Socket_UDP*
windows_socket_udp_create(Arena* arena, Address_Type type)
{
    isiz offset = arena_offset(arena);
    isiz family = 0;

    switch (type) {
        case ADDRESS_TYPE_IP4: { family = AF_INET;  } break;
        case ADDRESS_TYPE_IP6: { family = AF_INET6; } break;

        default: return 0;
    }

    Windows_Socket_UDP* result = pax_arena_reserve_one(arena, Windows_Socket_UDP);

    if (result != 0) {
        result->handle  = socket(family, SOCK_DGRAM, 0);
        result->address = {};

        if (result->handle != INVALID_SOCKET)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
windows_socket_udp_destroy(Windows_Socket_UDP* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_SOCKET)
        closesocket(self->handle);

    self->handle  = INVALID_SOCKET;
    self->address = {};
}

Address
windows_socket_udp_get_address(Windows_Socket_UDP* self)
{
    Address result = {};

    switch (self->address.ss_family) {
        case AF_INET: {
            mem8_copy(result.ip4.memory, pax_sock4_addr(&self->address),
                ADDRESS_IP4_GROUPS);

            result.type = ADDRESS_TYPE_IP4;
        } break;

        case AF_INET6: {
            mem16_copy(result.ip6.memory, pax_sock6_addr(&self->address),
                ADDRESS_IP6_GROUPS);

            result.type = ADDRESS_TYPE_IP6;
        } break;

        default: break;
    }

    return result;
}

u16
windows_socket_udp_get_port(Windows_Socket_UDP* self)
{
    u16 port = 0;

    switch (self->address.ss_family) {
        case AF_INET: {
            port = *pax_sock4_port(&self->address);
        } break;

        case AF_INET6: {
            port = *pax_sock6_port(&self->address);
        } break;

        default: break;
    }

    return u16_host_from_net(port);
}

b32
windows_socket_udp_bind(Windows_Socket_UDP* self, u16 port, Address address)
{
    isiz         payload = 0;
    Sock_Storage storage = {};

    switch (address.type) {
        case ADDRESS_TYPE_IP4: {
            payload = SOCK4_SIZE;
            port    = u16_net_from_host(port);

            mem16_copy(pax_sock4_port(&storage), &port, 1);

            mem8_copy(pax_sock4_addr(&storage), address.ip4.memory,
                ADDRESS_IP4_GROUPS);

            storage.ss_family = AF_INET;
        } break;

        case ADDRESS_TYPE_IP6: {
            payload = SOCK6_SIZE;
            port    = u16_net_from_host(port);

            mem16_copy(pax_sock6_port(&storage), &port, 1);

            mem16_copy(pax_sock6_addr(&storage), address.ip6.memory,
                ADDRESS_IP6_GROUPS);

            storage.ss_family = AF_INET6;
        } break;

        default: return 0;
    }

    if (bind(self->handle, pax_as_sock_address(&storage), payload) == SOCKET_ERROR)
        return 0;

    self->address = storage;

    return 1;
}

b32
windows_socket_udp_listen(Windows_Socket_UDP* self)
{
    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

b32
windows_socket_udp_connect(Windows_Socket_UDP* self, u16 port, Address address)
{
    isiz         payload = 0;
    Sock_Storage storage = {};

    switch (address.type) {
        case ADDRESS_TYPE_IP4: {
            payload = SOCK4_SIZE;
            port    = u16_net_from_host(port);

            mem16_copy(pax_sock4_port(&storage), &port, 1);

            mem8_copy(pax_sock4_addr(&storage), address.ip4.memory,
                ADDRESS_IP4_GROUPS);

            storage.ss_family = AF_INET;
        } break;

        case ADDRESS_TYPE_IP6: {
            payload = SOCK6_SIZE;
            port    = u16_net_from_host(port);

            mem16_copy(pax_sock6_port(&storage), &port, 1);

            mem16_copy(pax_sock6_addr(&storage), address.ip6.memory,
                ADDRESS_IP6_GROUPS);

            storage.ss_family = AF_INET6;
        } break;

        default: return 0;
    }

    if (connect(self->handle, pax_as_sock_address(&storage), payload) == SOCKET_ERROR)
        return 0;

    return 1;
}

Windows_Socket_UDP*
windows_socket_udp_accept(Windows_Socket_UDP* self, Arena* arena)
{
    isiz offset = arena_offset(arena);

    Windows_Socket_UDP* result = pax_arena_reserve_one(arena, Windows_Socket_UDP);

    if (result != 0) {
        isiz         payload = SOCK_STORAGE_SIZE;
        Sock_Storage storage = {};

        result->handle  = accept(self->handle,
            pax_as_sock_address(&storage), pax_as(int*, &payload));

        result->address = storage;

        if (result->handle != INVALID_SOCKET)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

b32
windows_socket_udp_write(Windows_Socket_UDP* self, buf8* buffer)
{
    buf8_normalize(buffer);

    u8*  memory = buffer->memory;
    isiz length = buffer->size;

    b32 state = windows_socket_udp_write_mem8(self,
        memory, length);

    if (state == 0) return 0;

    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;

    return 1;
}

b32
windows_socket_udp_write_to(Windows_Socket_UDP* self, buf8* buffer, u16 port, Address address)
{
    buf8_normalize(buffer);

    u8*  memory = buffer->memory;
    isiz length = buffer->size;

    b32 state = windows_socket_udp_write_mem8_to(self,
        memory, length, port, address);

    if (state == 0) return 0;

    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;

    return 1;
}

b32
windows_socket_udp_write_mem8(Windows_Socket_UDP* self, u8* memory, isiz length)
{
    isiz temp = 0;

    for (isiz i = 0; i < length; i += temp) {
        isiz tail = length - i;

        temp = send(self->handle,
            pax_as(char*, memory + i), tail, 0);

        if (temp <= 0 || temp > tail) return 0;
    }

    return 1;
}

b32
windows_socket_udp_write_mem8_to(Windows_Socket_UDP* self, u8* memory, isiz length, u16 port, Address address)
{
    isiz         payload = 0;
    Sock_Storage storage = {};

    switch (address.type) {
        case ADDRESS_TYPE_IP4: {
            payload = SOCK4_SIZE;
            port    = u16_net_from_host(port);

            mem16_copy(pax_sock4_port(&storage), &port, 1);

            mem8_copy(pax_sock4_addr(&storage), address.ip4.memory,
                ADDRESS_IP4_GROUPS);

            storage.ss_family = AF_INET;
        } break;

        case ADDRESS_TYPE_IP6: {
            payload = SOCK6_SIZE;
            port    = u16_net_from_host(port);

            mem16_copy(pax_sock6_port(&storage), &port, 1);

            mem16_copy(pax_sock6_addr(&storage), address.ip6.memory,
                ADDRESS_IP6_GROUPS);

            storage.ss_family = AF_INET6;
        } break;

        default: return 0;
    }

    isiz temp = 0;

    for (isiz i = 0; i < length; i += temp) {
        isiz tail = length - i;

        temp = sendto(self->handle, pax_as(char*, memory + i), tail,
            0, pax_as_sock_address(&storage), payload);

        if (temp <= 0 || temp > length) return 0;
    }

    return 1;
}

b32
windows_socket_udp_read(Windows_Socket_UDP* self, buf8* buffer)
{
    buf8_normalize(buffer);

    u8*  memory = buffer->memory + buffer->size;
    isiz length = buffer->length - buffer->size;
    isiz size   = 0;

    if (length <= 0) return 0;

    b32 state = windows_socket_udp_read_mem8(self,
        memory, length, &size);

    if (state == 0 || size <= 0 || size > length)
        return 0;

    buffer->size += size;
    buffer->tail += size;

    return 1;
}

b32
windows_socket_udp_read_from(Windows_Socket_UDP* self, buf8* buffer, u16* port, Address* address)
{
    buf8_normalize(buffer);

    u8*  memory = buffer->memory + buffer->size;
    isiz length = buffer->length - buffer->size;
    isiz size   = 0;

    if (length <= 0) return 0;

    b32 state = windows_socket_udp_read_mem8_from(self,
        memory, length, &size, port, address);

    if (state == 0 || size <= 0 || size > length)
        return 0;

    buffer->size += size;
    buffer->tail += size;

    return 1;
}

b32
windows_socket_udp_read_mem8(Windows_Socket_UDP* self, u8* memory, isiz length, isiz* size)
{
    isiz result = recv(self->handle,
        pax_as(char*, memory), length, 0);

    if (result <= 0 || result > length) return 0;

    if (size != 0) *size = result;

    return 1;
}

b32
windows_socket_udp_read_mem8_from(Windows_Socket_UDP* self, u8* memory, isiz length, isiz* size, u16* port, Address* address)
{
    isiz         payload = SOCK_STORAGE_SIZE;
    Sock_Storage storage = {};

    isiz result = recvfrom(self->handle, pax_as(char*, memory), length,
        0, pax_as_sock_address(&storage), pax_as(int*, &payload));

    if (result <= 0 || result > length) return 0;

    if (size != 0) *size = result;

    switch (storage.ss_family) {
        case AF_INET: {
            if (port != 0)
                mem_copy_host_from_net(port, pax_sock4_port(&storage), U16_SIZE);

            if (address != 0) {
                address->type = ADDRESS_TYPE_IP4;

                mem8_copy(address->ip4.memory, pax_sock4_addr(&storage),
                    ADDRESS_IP4_GROUPS);
            }
        } break;

        case AF_INET6: {
            if (port != 0)
                mem_copy_host_from_net(port, pax_sock6_port(&storage), U16_SIZE);

            if (address != 0) {
                address->type = ADDRESS_TYPE_IP6;

                mem16_copy(address->ip6.memory, pax_sock6_addr(&storage),
                    ADDRESS_IP6_GROUPS);
            }
        } break;

        default: return 0;
    }

    return 1;
}

} // namespace pax

#endif // PAX_NETWORK_WINDOWS_SOCKET_UDP_CPP
