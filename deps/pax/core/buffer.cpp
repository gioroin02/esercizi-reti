#ifndef PAX_CORE_BUFFER_CPP
#define PAX_CORE_BUFFER_CPP

#include "buffer.hpp"

namespace pax {

Buffer
buffer_make(const u8* memory, uptr length)
{
    Buffer result = {};

    result.size = 0;

    if (memory != 0 && length != 0) {
        result.memory = pax_cast(u8*, memory);
        result.length = length;
    }

    return result;
}

Buffer
buffer_make_full(const u8* memory, uptr length)
{
    Buffer result = {};

    if (memory != 0 && length != 0) {
        result.memory = pax_cast(u8*, memory);
        result.length = length;
        result.size   = length;
    }

    return result;
}

Buffer
buffer_reserve(Arena* arena, uptr length)
{
    return buffer_make(arena_reserve_arr<u8>(arena, length), length);
}

void
buffer_clear(Buffer* self)
{
    self->size = 0;
}

void
buffer_slide(Buffer* self, uptr offset)
{
    offset = pax_limit(offset, 0, self->size);

    self->size = self->size - offset;

    for (uptr i = 0; i < self->size; i += 1)
        self->memory[i] = self->memory[i + offset];
}

b32
buffer_encode_buffer(Buffer* self, Buffer value)
{
    uptr start = self->size;
    uptr size  = value.size;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(self->memory + start, value.memory, size);

    self->size += size;

    return 1;
}

b32
buffer_encode_uptr(Buffer* self, uptr value)
{
    uptr start = self->size;
    uptr size  = UPTR_SIZE;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(self->memory + start, &value, size);

    self->size += size;

    return 1;
}

b32
buffer_encode_u64(Buffer* self, u64 value)
{
    uptr start = self->size;
    uptr size  = U64_SIZE;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(self->memory + start, &value, size);

    self->size += size;

    return 1;
}

b32
buffer_encode_u32(Buffer* self, u32 value)
{
    uptr start = self->size;
    uptr size  = U32_SIZE;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(self->memory + start, &value, size);

    self->size += size;

    return 1;
}

b32
buffer_encode_u16(Buffer* self, u16 value)
{
    uptr start = self->size;
    uptr size  = U16_SIZE;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(self->memory + start, &value, size);

    self->size += size;

    return 1;
}

b32
buffer_encode_u8(Buffer* self, u8 value)
{
    uptr start = self->size;
    uptr size  = U8_SIZE;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(self->memory + start, &value, size);

    self->size += size;

    return 1;
}

b32
buffer_decode_uptr(Buffer* self, uptr* value)
{
    uptr size  = UPTR_SIZE;
    uptr start = self->size - size;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(value, self->memory + start, size);

    self->size -= size;

    return 1;
}

b32
buffer_decode_u64(Buffer* self, u64* value)
{
    uptr size  = U64_SIZE;
    uptr start = self->size - size;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(value, self->memory + start, size);

    self->size -= size;

    return 1;
}

b32
buffer_decode_u32(Buffer* self, u32* value)
{
    uptr size  = U32_SIZE;
    uptr start = self->size - size;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(value, self->memory + start, size);

    self->size -= size;

    return 1;
}

b32
buffer_decode_u16(Buffer* self, u16* value)
{
    uptr size  = U16_SIZE;
    uptr start = self->size - size;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(value, self->memory + start, size);

    self->size -= size;

    return 1;
}

b32
buffer_decode_u8(Buffer* self, u8* value)
{
    uptr size  = U8_SIZE;
    uptr start = self->size - size;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(value, self->memory + start, size);

    self->size -= size;

    return 1;
}

} // namespace pax

#endif // PAX_CORE_BUFFER_CPP
