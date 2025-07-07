#ifndef PAX_CORE_MEMORY_CPP
#define PAX_CORE_MEMORY_CPP

#include "memory.hpp"

namespace pax {

addr
mem8_zero(const addr memory, uptr length)
{
    u8* mem = pax_cast(u8*, memory);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = 0;

    return mem;
}

addr
mem8_copy(const addr memory, const addr value, uptr length)
{
    u8* mem = pax_cast(u8*, memory);
    u8* val = pax_cast(u8*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[i];

    return mem;
}

addr
mem8_copy_rev(const addr memory, const addr value, uptr length)
{
    u8* mem = pax_cast(u8*, memory);
    u8* val = pax_cast(u8*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[length - i - 1];

    return mem;
}

addr
mem8_move_back(const addr memory, uptr length, uptr offset)
{
    u8* mem = pax_cast(u8*, memory);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = mem[i + offset];

    return memory;
}

addr
mem8_move_forw(const addr memory, uptr length, uptr offset)
{
    u8* mem = pax_cast(u8*, memory);

    for (uptr i = length; i > 0; i -= 1)
        mem[i + offset - 1] = mem[i - 1];

    return memory;
}

addr
mem8_reverse(const addr memory, uptr length)
{
    u8* mem = pax_cast(u8*, memory);

    uptr i = 0;
    uptr j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = mem[i];
        u8 right = mem[j];

        mem[i] = right;
        mem[j] = left;
    }

    return mem;
}

b32
mem8_is_equal(const addr memory, const addr value, uptr length)
{
    u8* mem = pax_cast(u8*, memory);
    u8* val = pax_cast(u8*, value);

    for (uptr i = 0; i < length; i += 1) {
        if (mem[i] != val[i]) return 0;
    }

    return 1;
}

addr
mem16_zero(const addr memory, uptr length)
{
    u16* mem = pax_cast(u16*, memory);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = 0;

    return mem;
}

addr
mem16_copy(const addr memory, const addr value, uptr length)
{
    u16* mem = pax_cast(u16*, memory);
    u16* val = pax_cast(u16*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[i];

    return mem;
}

addr
mem16_copy_rev(const addr memory, const addr value, uptr length)
{
    u16* mem = pax_cast(u16*, memory);
    u16* val = pax_cast(u16*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[length - i - 1];

    return mem;
}

addr
mem16_reverse(const addr memory, uptr length)
{
    u16* mem = pax_cast(u16*, memory);

    uptr i = 0;
    uptr j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = mem[i];
        u8 right = mem[j];

        mem[i] = right;
        mem[j] = left;
    }

    return mem;
}

b32
mem16_is_equal(const addr memory, const addr value, uptr length)
{
    u16* mem = pax_cast(u16*, memory);
    u16* val = pax_cast(u16*, value);

    for (uptr i = 0; i < length; i += 1) {
        if (mem[i] != val[i]) return 0;
    }

    return 1;
}

addr
mem32_zero(const addr memory, uptr length)
{
    u32* mem = pax_cast(u32*, memory);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = 0;

    return mem;
}

addr
mem32_copy(const addr memory, const addr value, uptr length)
{
    u32* mem = pax_cast(u32*, memory);
    u32* val = pax_cast(u32*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[i];

    return mem;
}

addr
mem32_copy_rev(const addr memory, const addr value, uptr length)
{
    u32* mem = pax_cast(u32*, memory);
    u32* val = pax_cast(u32*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[length - i - 1];

    return mem;
}

addr
mem32_reverse(const addr memory, uptr length)
{
    u32* mem = pax_cast(u32*, memory);

    uptr i = 0;
    uptr j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = mem[i];
        u8 right = mem[j];

        mem[i] = right;
        mem[j] = left;
    }

    return mem;
}

b32
mem32_is_equal(const addr memory, const addr value, uptr length)
{
    u32* mem = pax_cast(u32*, memory);
    u32* val = pax_cast(u32*, value);

    for (uptr i = 0; i < length; i += 1) {
        if (mem[i] != val[i]) return 0;
    }

    return 1;
}

addr
mem64_zero(const addr memory, uptr length)
{
    u64* mem = pax_cast(u64*, memory);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = 0;

    return mem;
}

addr
mem64_copy(const addr memory, const addr value, uptr length)
{
    u64* mem = pax_cast(u64*, memory);
    u64* val = pax_cast(u64*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[i];

    return mem;
}

addr
mem64_copy_rev(const addr memory, const addr value, uptr length)
{
    u64* mem = pax_cast(u64*, memory);
    u64* val = pax_cast(u64*, value);

    for (uptr i = 0; i < length; i += 1)
        mem[i] = val[length - i - 1];

    return mem;
}

addr
mem64_reverse(const addr memory, uptr length)
{
    u64* mem = pax_cast(u64*, memory);

    uptr i = 0;
    uptr j = length - 1;

    for (; i < j; i += 1, j -= 1) {
        u8 left  = mem[i];
        u8 right = mem[j];

        mem[i] = right;
        mem[j] = left;
    }

    return mem;
}

b32
mem64_is_equal(const addr memory, const addr value, uptr length)
{
    u64* mem = pax_cast(u64*, memory);
    u64* val = pax_cast(u64*, value);

    for (uptr i = 0; i < length; i += 1) {
        if (mem[i] != val[i]) return 0;
    }

    return 1;
}

uptr
align_forward(uptr value, uptr align)
{
    uptr error = value % align;
    uptr extra = 0;

    if (error != 0)
        extra = align - error;

    return value + extra;
}

Arena
arena_make(const addr memory, uptr length)
{
    Arena result = {};

    if (memory != 0 && length != 0) {
        result.memory = pax_cast(u8*, memory);
        result.length = length;
        result.offset = 0;
    }

    return result;
}

Arena
arena_reserve(Arena* self, uptr size)
{
    Arena result = {};

    if (size <= 0) return result;

    uptr start = align_forward(self->offset, 16);
    uptr stop  = start + size;

    if (start < self->offset || stop > self->length)
        return result;

    mem8_zero(self->memory + start, size);

    self->offset = stop;

    return arena_make(self->memory + start, size);
}

b32
arena_release(Arena* self, addr value)
{
    return 0;
}

void
arena_clear(Arena* self)
{
    self->offset = 0;
}

uptr
arena_offset(Arena* self)
{
    return self->offset;
}

b32
arena_rewind(Arena* self, uptr offset)
{
    if (offset < 0 || offset >= self->length)
        return 0;

    self->offset = offset;

    return 1;
}

} // namespace pax

#endif // PAX_CORE_MEMORY_CPP
