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
buffer_write(Buffer* self, Buffer value)
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
buffer_write_mem8(Buffer* self, u8* memory, uptr length)
{
    uptr start = self->size;
    uptr size  = length;

    if (start < 0 || start + size > self->length)
        return 0;

    mem8_copy(self->memory + start, memory, size);

    self->size += size;

    return 1;
}

b32
buffer_read(Buffer* self, uptr index, Buffer* value)
{
    uptr start = value->size;
    uptr size  = value->length - value->size;

    if (index < 0 || index > self->size)
        return 0;

    size = pax_limit(size, 0, self->size - index);

    mem8_copy(value->memory + start,
        self->memory + index, size);

    value->size += size;

    return 1;
}

b32
buffer_read_mem8(Buffer* self, uptr index, u8* memory, uptr length)
{
    if (index < 0 || index > self->size)
        return 0;

    uptr size = pax_limit(size, 0, self->size - index);

    mem8_copy(memory, self->memory + index, size);
    mem8_zero(memory + size, length - size);

    return 1;
}

} // namespace pax

#endif // PAX_CORE_BUFFER_CPP
