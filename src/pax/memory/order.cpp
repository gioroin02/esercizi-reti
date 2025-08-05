#ifndef PAX_MEMORY_ORDER_CPP
#define PAX_MEMORY_ORDER_CPP

#include "order.hpp"

namespace pax {

b32
mem_is_lower_first()
{
    u16 value = 0x0001;

    if (pax_as_u8p(&value)[0] != 0)
        return 1;

    return 0;
}

b32
mem_is_upper_first()
{
    u16 value = 0x0001;

    if (pax_as_u8p(&value)[0] != 0)
        return 0;

    return 1;
}

void*
mem_host_from_net(void* memory, isiz length)
{
    if (mem_is_lower_first())
        return mem8_flip(memory, length);

    return memory;
}

void*
mem_copy_host_from_net(void* memory, void* value, isiz length)
{
    if (mem_is_lower_first())
        return mem8_copy_flipped(memory, value, length);

    return mem8_copy(memory, value, length);
}

void*
mem_net_from_host(void* memory, isiz length)
{
    if (mem_is_lower_first())
        return mem8_flip(memory, length);

    return memory;
}

void*
mem_copy_net_from_host(void* memory, void* value, isiz length)
{
    if (mem_is_lower_first())
        return mem8_copy_flipped(memory, value, length);

    return mem8_copy(memory, value, length);
}

f64
f64_host_from_net(u64 value)
{
    return *pax_as_f64p(mem_host_from_net(&value, U64_SIZE));
}

i64
i64_host_from_net(u64 value)
{
    return *pax_as_i64p(mem_host_from_net(&value, U64_SIZE));
}

u64
u64_host_from_net(u64 value)
{
    return *pax_as_u64p(mem_host_from_net(&value, U64_SIZE));
}

u64
f64_net_from_host(f64 value)
{
    return *pax_as_u64p(mem_net_from_host(&value, U64_SIZE));
}

u64
i64_net_from_host(i64 value)
{
    return *pax_as_u64p(mem_net_from_host(&value, U64_SIZE));
}

u64
u64_net_from_host(u64 value)
{
    return *pax_as_u64p(mem_net_from_host(&value, U64_SIZE));
}

f32
f32_host_from_net(u32 value)
{
    return *pax_as_f32p(mem_host_from_net(&value, U32_SIZE));
}

i32
i32_host_from_net(u32 value)
{
    return *pax_as_i32p(mem_host_from_net(&value, U32_SIZE));
}

u32
u32_host_from_net(u32 value)
{
    return *pax_as_u32p(mem_host_from_net(&value, U32_SIZE));
}

u32
f32_net_from_host(f32 value)
{
    return *pax_as_u32p(mem_net_from_host(&value, U32_SIZE));
}

u32
i32_net_from_host(i32 value)
{
    return *pax_as_u32p(mem_net_from_host(&value, U32_SIZE));
}

u32
u32_net_from_host(u32 value)
{
    return *pax_as_u32p(mem_net_from_host(&value, U32_SIZE));
}

i16
i16_host_from_net(u16 value)
{
    return *pax_as_i16p(mem_host_from_net(&value, U16_SIZE));
}

u16
u16_host_from_net(u16 value)
{
    return *pax_as_u16p(mem_host_from_net(&value, U16_SIZE));
}

u16
i16_net_from_host(i16 value)
{
    return *pax_as_u16p(mem_net_from_host(&value, U16_SIZE));
}

u16
u16_net_from_host(u16 value)
{
    return *pax_as_u16p(mem_net_from_host(&value, U16_SIZE));
}

} // namespace pax

#endif // PAX_MEMORY_ORDER_CPP
