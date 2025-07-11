#ifndef PAX_CORE_BUFFER_CPP
#define PAX_CORE_BUFFER_CPP

#include "buffer.hpp"

namespace pax {

Buffer
buffer_make(u8* memory, uptr length)
{
    Buffer result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

Buffer
buffer_make_full(u8* memory, uptr length)
{
    Buffer result = {};

    if (memory != 0 && length != 0) {
        result.memory = memory;
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

Buffer
buffer_copy_normalized(Arena* arena, Buffer value)
{
    Buffer result = buffer_reserve(arena, value.size);

    for (uptr i = 0; i < value.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    result.size = value.size;
    result.tail = value.size;

    return result;
}

void
buffer_clear(Buffer* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
buffer_normalize(Buffer* self)
{
    u8*  memory = self->memory;
    uptr length = self->tail;
    uptr shift  = self->head;

    if (self->head > self->tail) {
        memory = self->memory + self->length - self->head;
        shift  = self->head - self->tail;

        mem8_reverse(self->memory + self->head,
            self->length - self->head);

        mem8_reverse(self->memory, self->tail);
        mem8_reverse(self->memory, self->length);
    }

    if (shift != 0)
        mem8_move_back(memory, length, shift);

    self->head = 0;
    self->tail = self->size;
}

uptr
buffer_drop_head(Buffer* self, uptr offset)
{
    uptr size = pax_limit(offset, 0, self->size);
    uptr next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

uptr
buffer_drop_tail(Buffer* self, uptr offset)
{
    uptr size = pax_limit(offset, 0, self->size);
    uptr prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    return size;
}

b32
buffer_write_mem8_head(Buffer* self, u8* memory, uptr length)
{
    uptr prev = self->head + self->length - length;

    if (self->size < 0 || self->size + length > self->length)
        return 0;

    self->size += length;
    self->head  = prev % self->length;

    for (uptr i = 0; i < length; i += 1)
        self->memory[(self->head + i) % self->length] = memory[i];

    return 1;
}

b32
buffer_write_mem8_tail(Buffer* self, u8* memory, uptr length)
{
    uptr next = self->tail + length;

    if (self->size < 0 || self->size + length > self->length)
        return 0;

    for (uptr i = 0; i < length; i += 1)
        self->memory[(self->tail + i) % self->length] = memory[i];

    self->size += length;
    self->tail  = next % self->length;

    return 1;
}

uptr
buffer_read_mem8_head(Buffer* self, u8* memory, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr next = self->head + size;

    for (uptr i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

uptr
buffer_read_mem8_tail(Buffer* self, u8* memory, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->tail + i) % self->length];

    return size;
}

} // namespace pax

#endif // PAX_CORE_BUFFER_CPP
