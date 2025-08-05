#ifndef PAX_BASE_BUF32_HPP
#define PAX_BASE_BUF32_HPP

#include "memory.hpp"

namespace pax {

//
// Types
//

struct buf32
{
    u32* memory = 0;
    isiz length = 0;
    isiz size   = 0;
    isiz head   = 0;
    isiz tail   = 0;
};

//
// Procs
//

/* buf32 */

buf32
buf32_make(u32* memory, isiz length);

buf32
buf32_full(u32* memory, isiz length);

buf32
buf32_reserve(Arena* arena, isiz length);

buf32
buf32_copy(Arena* arena, buf32 value);

buf32
buf32_copy_len(Arena* arena, buf32 value, isiz length);

buf32
buf32_copy_mem(Arena* arena, u32* memory, isiz length);

void
buf32_clear(buf32* self);

void
buf32_normalize(buf32* self);

b32
buf32_get_head(buf32* self, isiz index, u32* value);

u32
buf32_get_head_or(buf32* self, isiz index, u32 value);

b32
buf32_get_tail(buf32* self, isiz index, u32* value);

u32
buf32_get_tail_or(buf32* self, isiz index, u32 value);

isiz
buf32_drop_head(buf32* self, isiz offset);

isiz
buf32_drop_tail(buf32* self, isiz offset);

/* buf32 writing */

isiz
buf32_write_head(buf32* self, buf32* value);

isiz
buf32_write_mem32_head(buf32* self, u32* memory, isiz length);

isiz
buf32_write_tail(buf32* self, buf32* value);

isiz
buf32_write_mem32_tail(buf32* self, u32* memory, isiz length);

/* buf32 reading */

isiz
buf32_read_head(buf32* self, buf32* value);

isiz
buf32_read_mem32_head(buf32* self, u32* memory, isiz length);

isiz
buf32_read_tail(buf32* self, buf32* value);

isiz
buf32_read_mem32_tail(buf32* self, u32* memory, isiz length);

/* buf32 peeking */

isiz
buf32_peek_head(buf32* self, buf32* value);

isiz
buf32_peek_mem32_head(buf32* self, u32* memory, isiz length);

isiz
buf32_peek_tail(buf32* self, buf32* value);

isiz
buf32_peek_mem32_tail(buf32* self, u32* memory, isiz length);

} // namespace pax

#endif // PAX_BASE_BUF8_HPP
