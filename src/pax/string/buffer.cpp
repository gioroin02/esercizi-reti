#ifndef PAX_STRING_BUFFER_CPP
#define PAX_STRING_BUFFER_CPP

#include "buffer.hpp"

namespace pax {

b32
buffer_write_str8_head(Buffer* self, str8 value)
{
    u8*  memory = value.memory;
    uptr length = value.length;
    uptr prev   = self->head + self->length - length;

    if (self->size < 0 || self->size + length > self->length)
        return 0;

    self->size += length;
    self->head  = prev % self->length;

    for (uptr i = 0; i < length; i += 1)
        self->memory[(self->head + i) % self->length] = memory[i];

    return 1;
}

b32
buffer_write_str8_tail(Buffer* self, str8 value)
{
    u8*  memory = value.memory;
    uptr length = value.length;
    uptr next   = self->tail + length;

    if (self->size < 0 || self->size + length > self->length)
        return 0;

    for (uptr i = 0; i < length; i += 1)
        self->memory[(self->tail + i) % self->length] = memory[i];

    self->size += length;
    self->tail  = next % self->length;

    return 1;
}

str8
buffer_read_str8_head(Buffer* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr next = self->head + size;

    str8 result = str8_reserve(arena, size);

    if (result.length == 0) return result;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return result;
}

str8
buffer_read_str8_tail(Buffer* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr prev = self->tail + self->length - size;

    str8 result = str8_reserve(arena, size);

    if (result.length == 0) return result;

    self->size -= size;
    self->tail  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->tail + i) % self->length];

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUFFER_CPP
