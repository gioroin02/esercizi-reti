#ifndef PAX_STRUCTURE_ARRAY_CPP
#define PAX_STRUCTURE_ARRAY_CPP

#include "array.hpp"

namespace pax {

Array
array_make(u8* memory, isiz stride, isiz length)
{
    Array result = {};

    if (memory != 0 && stride > 0 && length > 0) {
        result.stride = stride;
        result.memory = memory;
        result.length = length;
    }

    return result;
}

Array
array_reserve_mem(Arena* arena, isiz stride, isiz length)
{
    Array result = {};
    u8*   memory = arena_reserve(arena, stride, length).memory;

    result.arena = arena;

    if (memory != 0 && stride > 0 && length > 0) {
        result.memory = memory;
        result.stride = stride;
        result.length = length;
    }

    return result;
}

void
array_release(Array* self)
{
    if (self->arena != 0 && self->memory != 0)
        arena_release(self->arena, self->memory);

    self->arena  = 0;
    self->memory = 0;
    self->stride = 0;
    self->length = 0;
    self->size   = 0;
}

Array
array_copy(Arena* arena, Array* value)
{
    return array_copy_len(arena, value, value->size);
}

Array
array_copy_len(Arena* arena, Array* value, isiz length)
{
    Array result = array_reserve_mem(arena, value->stride, length);

    if (result.length <= 0) return result;

    result.size = pax_limit(value->size, 0, length);

    mem8_copy(result.memory, value->memory,
        result.size * result.stride);

    return result;
}

b32
array_grow(Array* self, isiz length)
{
    Array copy = {};

    if (self->length >= length) return 1;

    copy = array_copy_len(self->arena, self, length);

    if (copy.length > 0) {
        array_release(self);

        self->arena  = copy.arena;
        self->memory = copy.memory;
        self->stride = copy.stride;
        self->length = copy.length;
        self->size   = copy.size;

        return 1;
    }

    return 0;
}

b32
array_swap(Array* self, isiz index, usiz other)
{
    if (index < 0 || index >= self->size) return 0;
    if (other < 0 || other >= self->size) return 0;

    if (index == other) return 1;

    for (isiz i = 0; i < self->stride; i += 1) {
        u8* left  = self->memory + (index + i);
        u8* right = self->memory + (other + i);

        *left  = *right ^ *left;
        *right = *left ^ *right;
        *left  = *right ^ *left;
    }

    return 1;
}

b32
array_swap_head(Array* self, isiz index)
{
    return array_swap(self, index, 0);
}

b32
array_swap_tail(Array* self, isiz index)
{
    return array_swap(self, index, self->size - 1);
}

void
array_clear(Array* self)
{
    self->size = 0;
}

b32
array_insert_mem(Array* self, isiz index, void* memory, isiz stride)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (index < 0 || index > self->size) return 0;

    if (self->stride != stride || memory == 0) return 0;

    isiz length = self->size - index;

    mem8_move_forw(self->memory + (index * stride),
        length * stride, stride);

    mem8_copy(self->memory + (index * stride), memory, stride);

    self->size += 1;

    return 1;
}

b32
array_insert_head_mem(Array* self, void* memory, isiz stride)
{
    return array_insert_mem(self, 0, memory, stride);
}

b32
array_insert_tail_mem(Array* self, void* memory, isiz stride)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (self->stride != stride || memory == 0) return 0;

    isiz index = self->size;

    mem8_copy(self->memory + (index * stride), memory, stride);

    self->size += 1;

    return 1;
}

b32
array_remove_mem(Array* self, isiz index, void* memory, isiz stride)
{
    if (index < 0 || index >= self->size) return 0;

    if (self->stride != stride) return 0;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    isiz length = self->size - index;

    mem8_move_back(self->memory + (index * stride),
        length * stride, stride);

    self->size -= 1;

    return 1;
}

b32
array_remove_head_mem(Array* self, void* memory, isiz stride)
{
    return array_remove_mem(self, 0, memory, stride);
}

b32
array_remove_tail_mem(Array* self, void* memory, isiz stride)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    if (self->stride != stride) return 0;

    self->size -= 1;

    isiz index = self->size;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    return 1;
}

b32
array_drop(Array* self, isiz index)
{
    if (index < 0 || index >= self->size) return 0;

    isiz length = self->size - index;
    isiz stride = self->stride;

    mem8_move_back(self->memory + (index * stride),
        length * stride, stride);

    self->size -= 1;

    return 1;
}

b32
array_drop_head(Array* self)
{
    return array_drop(self, 0);
}

b32
array_drop_tail(Array* self)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    self->size -= 1;

    return 1;
}

b32
array_get_mem(Array* self, isiz index, void* memory, isiz stride)
{
    if (index < 0 || index >= self->size) return 0;

    if (self->stride != stride) return 0;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    return 1;
}

b32
array_get_head_mem(Array* self, void* memory, isiz stride)
{
    return array_get_mem(self, 0, memory, stride);
}

b32
array_get_tail_mem(Array* self, void* memory, isiz stride)
{
    return array_get_mem(self, self->size - 1, memory, stride);
}

b32
array_assign_mem(Array* self, isiz index, void* memory, isiz stride)
{
    if (index < 0 || index >= self->size) return 0;

    if (self->stride != stride || memory == 0) return 0;

    mem8_copy(self->memory + (index * stride), memory, stride);

    return 1;
}

b32
array_assign_head_mem(Array* self, void* memory, isiz stride)
{
    return array_assign_mem(self, 0, memory, stride);
}

b32
array_assign_tail_mem(Array* self, void* memory, isiz stride)
{
    return array_assign_mem(self, self->size - 1, memory, stride);
}

} // namespace pax

#endif // PAX_STRUCTURE_ARRAY_CPP
