#ifndef PAX_BASE_BUF16_HPP
#define PAX_BASE_BUF16_HPP

#include "memory.hpp"

namespace pax {

//
// Types
//

struct buf16
{
    u16* memory = 0;
    isiz length = 0;
    isiz size   = 0;
    isiz head   = 0;
    isiz tail   = 0;
};

//
// Procs
//

/* buf16 */

buf16
buf16_make(u16* memory, isiz length);

buf16
buf16_full(u16* memory, isiz length);

buf16
buf16_reserve(Arena* arena, isiz length);

buf16
buf16_copy(Arena* arena, buf16 value);

buf16
buf16_copy_len(Arena* arena, buf16 value, isiz length);

buf16
buf16_copy_mem(Arena* arena, u16* memory, isiz length);

void
buf16_clear(buf16* self);

void
buf16_normalize(buf16* self);

b32
buf16_get_head(buf16* self, isiz index, u16* value);

u16
buf16_get_head_or(buf16* self, isiz index, u16 value);

b32
buf16_get_tail(buf16* self, isiz index, u16* value);

u16
buf16_get_tail_or(buf16* self, isiz index, u16 value);

isiz
buf16_drop_head(buf16* self, isiz offset);

isiz
buf16_drop_tail(buf16* self, isiz offset);

/* buf16 writing */

isiz
buf16_write_head(buf16* self, buf16* value);

isiz
buf16_write_mem16_head(buf16* self, u16* memory, isiz length);

isiz
buf16_write_tail(buf16* self, buf16* value);

isiz
buf16_write_mem16_tail(buf16* self, u16* memory, isiz length);

/* buf16 reading */

isiz
buf16_read_head(buf16* self, buf16* value);

isiz
buf16_read_mem16_head(buf16* self, u16* memory, isiz length);

isiz
buf16_read_tail(buf16* self, buf16* value);

isiz
buf16_read_mem16_tail(buf16* self, u16* memory, isiz length);

/* buf16 peeking */

isiz
buf16_peek_head(buf16* self, buf16* value);

isiz
buf16_peek_mem16_head(buf16* self, u16* memory, isiz length);

isiz
buf16_peek_tail(buf16* self, buf16* value);

isiz
buf16_peek_mem16_tail(buf16* self, u16* memory, isiz length);

} // namespace pax

#endif // PAX_BASE_BUF8_HPP
