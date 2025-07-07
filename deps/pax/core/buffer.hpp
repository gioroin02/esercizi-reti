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

/* Encoding */

b32
buffer_encode_buffer(Buffer* self, Buffer value);

b32
buffer_encode_uptr(Buffer* self, uptr value);

b32
buffer_encode_u64(Buffer* self, u64 value);

b32
buffer_encode_u32(Buffer* self, u32 value);

b32
buffer_encode_u16(Buffer* self, u16 value);

b32
buffer_encode_u8(Buffer* self, u8 value);

/* Decoding */

b32
buffer_decode_uptr(Buffer* self, uptr* value);

b32
buffer_decode_u64(Buffer* self, u64* value);

b32
buffer_decode_u32(Buffer* self, u32* value);

b32
buffer_decode_u16(Buffer* self, u16* value);

b32
buffer_decode_u8(Buffer* self, u8* value);

} // namespace pax

#endif // PAX_CORE_BUFFER_HPP
