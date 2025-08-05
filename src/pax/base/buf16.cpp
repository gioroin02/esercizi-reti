#ifndef PAX_BASE_BUF16_CPP
#define PAX_BASE_BUF16_CPP

#include "buf16.hpp"

namespace pax {

buf16
buf16_make(u16* memory, isiz length)
{
    buf16 result = {};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

buf16
buf16_full(u16* memory, isiz length)
{
    buf16 result = {};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
        result.size   = length;
        result.tail   = length;
    }

    return result;
}

buf16
buf16_reserve(Arena* arena, isiz length)
{
    return buf16_make(pax_arena_reserve(arena, u16, length), length);
}

buf16
buf16_copy(Arena* arena, buf16 value)
{
    return buf16_copy_len(arena, value, value.length);
}

buf16
buf16_copy_len(Arena* arena, buf16 value, isiz length)
{
    buf16 result = buf16_reserve(arena, length);

    if (result.length <= 0 || value.length <= 0) return result;

    result.size = pax_limit(value.size, 0, length);
    result.tail = result.size;

    for (isiz i = 0; i < result.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    return result;
}

buf16
buf16_copy_mem(Arena* arena, u16* memory, isiz length)
{
    buf16 result = buf16_reserve(arena, length);

    if (result.length <= 0) return result;

    mem16_copy(result.memory, memory, result.length);

    result.size = result.length;
    result.tail = result.length;

    return result;
}

void
buf16_clear(buf16* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
buf16_normalize(buf16* self)
{
    u16* memory = self->memory;
    isiz length = self->tail;
    isiz shift  = self->head;

    if (self->head > self->tail) {
        memory = self->memory + self->length - self->head;
        shift  = self->head - self->tail;

        mem16_flip(self->memory + self->head,
            self->length - self->head);

        mem16_flip(self->memory, self->tail);
        mem16_flip(self->memory, self->length);
    }

    if (shift > 0 && self->head > 0)
        mem16_move_back(memory, length, shift);

    self->head = 0;
    self->tail = self->size;
}

b32
buf16_get_head(buf16* self, isiz index, u16* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->head + index) % self->length;

    return self->memory[index];
}

u16
buf16_get_head_or(buf16* self, isiz index, u16 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->head + index) % self->length;

    return self->memory[index];
}

b32
buf16_get_tail(buf16* self, isiz index, u16* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->tail + self->length - index) % self->length;

    return self->memory[index];
}

u16
buf16_get_tail_or(buf16* self, isiz index, u16 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->tail + self->length - index) % self->length;

    return self->memory[index];
}

isiz
buf16_drop_head(buf16* self, isiz offset)
{
    offset = pax_min(offset, self->size);

    if (offset > 0) {
        isiz next = self->head + offset;

        self->size -= offset;
        self->head  = next % self->length;
    }

    return offset;
}

isiz
buf16_drop_tail(buf16* self, isiz offset)
{
    offset = pax_min(offset, self->size);

    if (offset > 0) {
        isiz prev = self->tail + self->length - offset;

        self->size -= offset;
        self->tail  = prev % self->length;
    }

    return offset;
}

isiz
buf16_write_head(buf16* self, buf16* value)
{
    isiz size = self->length - self->size;

    size = pax_min(size, value->size);

    if (size <= 0 || size > self->length) return 0;

    isiz prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0; i < size; i += 1) {
        isiz j = (self->head + i) % self->length;
        isiz k = (value->head + i) % value->length;

        self->memory[j] = value->memory[k];
    }

    isiz next = value->head + size;

    value->size -= size;
    value->head  = next % value->length;

    return size;
}

isiz
buf16_write_mem16_head(buf16* self, u16* memory, isiz length)
{
    length = pax_min(length, self->length - self->size);

    if (length <= 0 || length > self->length) return 0;

    isiz prev = self->head + self->length - length;

    self->size += length;
    self->head  = prev % self->length;

    for (isiz i = 0; i < length; i += 1)
        self->memory[(self->head + i) % self->length] = memory[i];

    return length;
}

isiz
buf16_write_tail(buf16* self, buf16* value)
{
    isiz size = self->length - self->size;

    size = pax_min(size, value->size);

    if (size <= 0 || size > self->length) return 0;

    isiz next = self->tail + size;

    for (isiz i = 0; i < size; i += 1) {
        isiz j = (self->tail + i) % self->length;
        isiz k = (value->head + i) % value->length;

        self->memory[j] = value->memory[k];
    }

    self->size += size;
    self->tail  = next % self->length;

    next = value->head + size;

    value->size -= size;
    value->head  = next % value->length;

    return size;
}

isiz
buf16_write_mem16_tail(buf16* self, u16* memory, isiz length)
{
    length = pax_min(length, self->length - self->size);

    if (length <= 0 || length > self->length) return 0;

    isiz next = self->tail + length;

    for (isiz i = 0; i < length; i += 1)
        self->memory[(self->tail + i) % self->length] = memory[i];

    self->size += length;
    self->tail  = next % self->length;

    return length;
}

isiz
buf16_read_head(buf16* self, buf16* value)
{
    isiz size = self->size;

    size = pax_min(size, value->length - value->size);

    if (size <= 0 || size > self->size) return 0;

    isiz next = self->head + size;

    for (isiz i = 0; i < size; i += 1) {
        isiz j = (value->tail + i) % value->length;
        isiz k = (self->head + i) % self->length;

        value->memory[j] = self->memory[k];
    }

    self->size -= size;
    self->head  = next % self->length;

    next = value->tail + size;

    value->size += size;
    value->tail  = next % value->length;

    return size;
}

isiz
buf16_read_mem16_head(buf16* self, u16* memory, isiz length)
{
    length = pax_min(length, self->size);

    if (length <= 0 || length > self->size) return 0;

    isiz next = self->head + length;

    for (isiz i = 0; i < length; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= length;
    self->head  = next % self->length;

    return length;
}

isiz
buf16_read_tail(buf16* self, buf16* value)
{
    isiz size = self->size;

    size = pax_min(size, value->length - value->size);

    if (size <= 0 || size > self->size) return 0;

    isiz prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (isiz i = 0; i < size; i += 1) {
        isiz j = (value->tail + i) % value->length;
        isiz k = (self->tail + i) % self->length;

        value->memory[j] = self->memory[k];
    }

    isiz next = value->tail + size;

    value->size += size;
    value->tail  = next % value->length;

    return size;
}

isiz
buf16_read_mem16_tail(buf16* self, u16* memory, isiz length)
{
    length = pax_min(length, self->size);

    if (length <= 0 || length > self->size) return 0;

    isiz prev = self->tail + self->length - length;

    self->size -= length;
    self->tail  = prev % self->length;

    for (isiz i = 0; i < length; i += 1)
        memory[i] = self->memory[(self->tail + i) % self->length];

    return length;
}

isiz
buf16_peek_head(buf16* self, buf16* value)
{
    isiz size = self->size;

    size = pax_min(size, value->length - value->size);

    if (size <= 0 || size > self->size) return 0;

    for (isiz i = 0; i < size; i += 1) {
        isiz j = (value->tail + i) % value->length;
        isiz k = (self->head + i) % self->length;

        value->memory[j] = self->memory[k];
    }

    isiz next = value->tail + size;

    value->size += size;
    value->tail  = next % value->length;

    return size;
}

isiz
buf16_peek_mem16_head(buf16* self, u16* memory, isiz length)
{
    length = pax_min(length, self->size);

    if (length <= 0 || length > self->size) return 0;

    for (isiz i = 0; i < length; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    return length;
}

isiz
buf16_peek_tail(buf16* self, buf16* value)
{
    isiz size = self->size;

    size = pax_min(size, value->length - value->size);

    if (size <= 0 || size > self->size) return 0;

    isiz prev = self->tail + self->length - size;

    for (isiz i = 0; i < size; i += 1) {
        isiz j = (value->tail + i) % value->length;
        isiz k = (prev + i) % self->length;

        value->memory[j] = self->memory[k];
    }

    isiz next = value->tail + size;

    value->size += size;
    value->tail  = next % value->length;

    return size;
}

isiz
buf16_peek_mem16_tail(buf16* self, u16* memory, isiz length)
{
    length = pax_min(length, self->size);

    if (length <= 0 || length > self->size) return 0;

    isiz prev = self->tail + self->length - length;

    for (isiz i = 0; i < length; i += 1)
        memory[i] = self->memory[(prev + i) % self->length];

    return length;
}

} // namespace pax

#endif // PAX_BASE_BUF16_CPP
