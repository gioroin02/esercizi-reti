#ifndef PAX_BASE_BUF8_HPP
#define PAX_BASE_BUF8_HPP

#include "memory.hpp"

namespace pax {

//
// Types
//

struct buf8
{
    u8*  memory = 0;
    isiz length = 0;
    isiz size   = 0;
    isiz head   = 0;
    isiz tail   = 0;
};

//
// Procs
//

/* buf8 */

buf8
buf8_make(u8* memory, isiz length);

buf8
buf8_full(u8* memory, isiz length);

buf8
buf8_reserve(Arena* arena, isiz length);

buf8
buf8_copy(Arena* arena, buf8 value);

buf8
buf8_copy_len(Arena* arena, buf8 value, isiz length);

buf8
buf8_copy_mem(Arena* arena, u8* memory, isiz length);

void
buf8_clear(buf8* self);

void
buf8_normalize(buf8* self);

b32
buf8_get_head(buf8* self, isiz index, u8* value);

u8
buf8_get_head_or(buf8* self, isiz index, u8 value);

b32
buf8_get_tail(buf8* self, isiz index, u8* value);

u8
buf8_get_tail_or(buf8* self, isiz index, u8 value);

isiz
buf8_drop_head(buf8* self, isiz offset);

isiz
buf8_drop_tail(buf8* self, isiz offset);

/* buf8 writing */

isiz
buf8_write_head(buf8* self, buf8* value);

isiz
buf8_write_mem8_head(buf8* self, u8* memory, isiz length);

isiz
buf8_write_tail(buf8* self, buf8* value);

isiz
buf8_write_mem8_tail(buf8* self, u8* memory, isiz length);

/* buf8 reading */

isiz
buf8_read_head(buf8* self, buf8* value);

isiz
buf8_read_mem8_head(buf8* self, u8* memory, isiz length);

isiz
buf8_read_tail(buf8* self, buf8* value);

isiz
buf8_read_mem8_tail(buf8* self, u8* memory, isiz length);

/* buf8 peeking */

isiz
buf8_peek_head(buf8* self, buf8* value);

isiz
buf8_peek_mem8_head(buf8* self, u8* memory, isiz length);

isiz
buf8_peek_tail(buf8* self, buf8* value);

isiz
buf8_peek_mem8_tail(buf8* self, u8* memory, isiz length);

} // namespace pax

#endif // PAX_BASE_BUF8_HPP
