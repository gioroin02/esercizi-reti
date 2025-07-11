#ifndef PAX_CORE_BUFFER_HPP
#define PAX_CORE_BUFFER_HPP

#include "memory.hpp"

//
// Defines
//

#define pax_buffer(expr) \
    buffer_make(pax_cast(u8*, expr), pax_array_length(expr))

#define pax_buffer_full(expr) \
    buffer_make_full(pax_cast(u8*, expr), pax_array_length(expr))

namespace pax {

//
// Types
//

struct Buffer
{
    u8*  memory = 0;
    uptr length = 0;
    uptr size   = 0;
    uptr head   = 0;
    uptr tail   = 0;
};

//
// Procs
//

/* Buffer */

Buffer
buffer_make(u8* memory, uptr length);

Buffer
buffer_make_full(u8* memory, uptr length);

Buffer
buffer_reserve(Arena* arena, uptr length);

Buffer
buffer_copy_normalized(Arena* arena, Buffer value);

void
buffer_clear(Buffer* self);

void
buffer_normalize(Buffer* self);

uptr
buffer_drop_head(Buffer* self, uptr offset);

uptr
buffer_drop_tail(Buffer* self, uptr offset);

/* Buffer writing */

b32
buffer_write_mem8_head(Buffer* self, u8* memory, uptr length);

b32
buffer_write_mem8_tail(Buffer* self, u8* memory, uptr length);

/* Buffer reading */

uptr
buffer_read_mem8_head(Buffer* self, u8* memory, uptr length);

uptr
buffer_read_mem8_tail(Buffer* self, u8* memory, uptr length);

} // namespace pax

#endif // PAX_CORE_BUFFER_HPP
