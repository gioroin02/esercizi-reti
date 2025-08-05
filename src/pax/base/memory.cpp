#ifndef PAX_BASE_MEMORY_CPP
#define PAX_BASE_MEMORY_CPP

#include "memory.hpp"

namespace pax {

void*
mem8_zero(void* memory, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u8p(memory)[i] = 0;

    return memory;
}

void*
mem8_copy(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u8p(memory)[i] = pax_as_u8p(value)[i];

    return memory;
}

void*
mem8_copy_flipped(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u8p(memory)[i] = pax_as_u8p(value)[length - i - 1];

    return memory;
}

void*
mem8_move_back(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = 0; i < length; i += 1)
        pax_as_u8p(memory)[i] = pax_as_u8p(memory)[i + offset];

    return memory;
}

void*
mem8_move_forw(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = length; i > 0; i -= 1)
        pax_as_u8p(memory)[i + offset - 1] = pax_as_u8p(memory)[i - 1];

    return memory;
}

void*
mem8_flip(void* memory, isiz length)
{
    if (length <= 0) return memory;

    isiz i = 0;
    isiz j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = pax_as_u8p(memory)[i];
        u8 right = pax_as_u8p(memory)[j];

        pax_as_u8p(memory)[i] = right;
        pax_as_u8p(memory)[j] = left;
    }

    return memory;
}

b32
mem8_is_equal(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1) {
        if (pax_as_u8p(memory)[i] != pax_as_u8p(value)[i])
            return 0;
    }

    return 1;
}

void*
mem16_zero(void* memory, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u16p(memory)[i] = 0;

    return memory;
}

void*
mem16_copy(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u16p(memory)[i] = pax_as_u16p(value)[i];

    return memory;
}

void*
mem16_copy_flipped(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u16p(memory)[i] = pax_as_u16p(value)[length - i - 1];

    return memory;
}

void*
mem16_move_back(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = 0; i < length; i += 1)
        pax_as_u16p(memory)[i] = pax_as_u16p(memory)[i + offset];

    return memory;
}

void*
mem16_move_forw(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = length; i > 0; i -= 1)
        pax_as_u16p(memory)[i + offset - 1] = pax_as_u16p(memory)[i - 1];

    return memory;
}

void*
mem16_flip(void* memory, isiz length)
{
    if (length <= 0) return memory;

    isiz i = 0;
    isiz j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = pax_as_u16p(memory)[i];
        u8 right = pax_as_u16p(memory)[j];

        pax_as_u16p(memory)[i] = right;
        pax_as_u16p(memory)[j] = left;
    }

    return memory;
}

b32
mem16_is_equal(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1) {
        if (pax_as_u16p(memory)[i] != pax_as_u16p(value)[i])
            return 0;
    }

    return 1;
}

void*
mem32_zero(void* memory, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u32p(memory)[i] = 0;

    return memory;
}

void*
mem32_copy(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u32p(memory)[i] = pax_as_u32p(value)[i];

    return memory;
}

void*
mem32_copy_flipped(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u32p(memory)[i] = pax_as_u32p(value)[length - i - 1];

    return memory;
}

void*
mem32_move_back(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = 0; i < length; i += 1)
        pax_as_u32p(memory)[i] = pax_as_u32p(memory)[i + offset];

    return memory;
}

void*
mem32_move_forw(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = length; i > 0; i -= 1)
        pax_as_u32p(memory)[i + offset - 1] = pax_as_u32p(memory)[i - 1];

    return memory;
}

void*
mem32_flip(void* memory, isiz length)
{
    if (length <= 0) return memory;

    isiz i = 0;
    isiz j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = pax_as_u32p(memory)[i];
        u8 right = pax_as_u32p(memory)[j];

        pax_as_u32p(memory)[i] = right;
        pax_as_u32p(memory)[j] = left;
    }

    return memory;
}

b32
mem32_is_equal(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1) {
        if (pax_as_u32p(memory)[i] != pax_as_u32p(value)[i])
            return 0;
    }

    return 1;
}

void*
mem64_zero(void* memory, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u64p(memory)[i] = 0;

    return memory;
}

void*
mem64_copy(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u64p(memory)[i] = pax_as_u64p(value)[i];

    return memory;
}

void*
mem64_copy_flipped(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1)
        pax_as_u64p(memory)[i] = pax_as_u64p(value)[length - i - 1];

    return memory;
}

void*
mem64_move_back(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = 0; i < length; i += 1)
        pax_as_u64p(memory)[i] = pax_as_u64p(memory)[i + offset];

    return memory;
}

void*
mem64_move_forw(void* memory, isiz length, isiz offset)
{
    if (offset <= 0) return memory;

    for (isiz i = length; i > 0; i -= 1)
        pax_as_u64p(memory)[i + offset - 1] = pax_as_u64p(memory)[i - 1];

    return memory;
}

void*
mem64_flip(void* memory, isiz length)
{
    if (length <= 0) return memory;

    isiz i = 0;
    isiz j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = pax_as_u64p(memory)[i];
        u8 right = pax_as_u64p(memory)[j];

        pax_as_u64p(memory)[i] = right;
        pax_as_u64p(memory)[j] = left;
    }

    return memory;
}

b32
mem64_is_equal(void* memory, void* value, isiz length)
{
    for (isiz i = 0; i < length; i += 1) {
        if (pax_as_u64p(memory)[i] != pax_as_u64p(value)[i])
            return 0;
    }

    return 1;
}

Arena
arena_make(u8* memory, isiz length)
{
    Arena result = {};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

Arena
arena_reserve(Arena* self, isiz stride, isiz amount)
{
    Arena result = {};

    if (stride <= 0 || amount <= 0) return result;

    isiz size  = stride * amount;
    isiz start = arena_align_forward(self, 16);
    isiz stop  = start + size;

    if (start < self->offset || stop > self->length)
        return result;

    mem8_zero(self->memory + start, size);

    self->offset = stop;

    return arena_make(self->memory + start, size);
}

Arena
arena_reserve_one(Arena* self, isiz size)
{
    return arena_reserve(self, size, 1);
}

b32
arena_release(Arena* self, void* value)
{
    return 0;
}

void
arena_clear(Arena* self)
{
    self->offset = 0;
}

isiz
arena_offset(Arena* self)
{
    return self->offset;
}

b32
arena_rewind(Arena* self, isiz offset)
{
    if (offset < 0 || offset >= self->length)
        return 0;

    self->offset = offset;

    return 1;
}

isiz
arena_align_forward(Arena* self, isiz align)
{
    if (align <= 0) return self->offset;

    isiz error = self->offset % align;
    isiz extra = 0;

    if (error != 0)
        extra = align - error;

    return self->offset + extra;
}

} // namespace pax

#endif // PAX_BASE_MEMORY_CPP
