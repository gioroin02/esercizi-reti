#ifndef PAX_MEMORY_ORDER_HPP
#define PAX_MEMORY_ORDER_HPP

#include "imports.hpp"

namespace pax {

//
// Procs
//

/* Memory order */

b32
mem_is_lower_first();

b32
mem_is_upper_first();

/* Memory network order */

void*
mem_host_from_net(void* memory, isiz length);

void*
mem_copy_host_from_net(void* memory, void* value, isiz length);

void*
mem_net_from_host(void* memory, isiz length);

void*
mem_copy_net_from_host(void* memory, void* value, isiz length);

/* 64 bits host */

f64
f64_host_from_net(u64 value);

i64
i64_host_from_net(u64 value);

u64
u64_host_from_net(u64 value);

/* 64 bits network */

u64
f64_net_from_host(f64 value);

u64
i64_net_from_host(i64 value);

u64
u64_net_from_host(u64 value);

/* 32 bits host */

f32
f32_host_from_net(u32 value);

i32
i32_host_from_net(u32 value);

u32
u32_host_from_net(u32 value);

/* 32 bits network */

u32
f32_net_from_host(f32 value);

u32
i32_net_from_host(i32 value);

u32
u32_net_from_host(u32 value);

/* 16 bits host */

i16
i16_host_from_net(u16 value);

u16
u16_host_from_net(u16 value);

/* 16 bits network */

u16
i16_net_from_host(i16 value);

u16
u16_net_from_host(u16 value);

} // namespace pax

#endif // PAX_MEMORY_ORDER_HPP
