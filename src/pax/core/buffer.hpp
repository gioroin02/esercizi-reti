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
};

//
// Procs
//

/* Buffer */

Buffer
buffer_make(const u8* memory, uptr length);

Buffer
buffer_make_full(const u8* memory, uptr length);

Buffer
buffer_reserve(Arena* arena, uptr length);

void
buffer_clear(Buffer* self);

void
buffer_slide(Buffer* self, uptr offset);

/* Buffer writing */

b32
buffer_write(Buffer* self, Buffer value);

b32
buffer_write_mem8(Buffer* self, u8* memory, uptr length);

/* Buffer reading */

b32
buffer_read(Buffer* self, uptr index, Buffer* value);

b32
buffer_read_mem8(Buffer* self, uptr index, u8* memory, uptr length);

} // namespace pax

#endif // PAX_CORE_BUFFER_HPP
