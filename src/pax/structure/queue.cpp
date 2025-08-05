#ifndef PAX_STRUCTURE_QUEUE_CPP
#define PAX_STRUCTURE_QUEUE_CPP

#include "queue.hpp"

namespace pax {

Queue
queue_make(u8* memory, isiz stride, isiz length)
{
    Queue result = {};

    if (memory != 0 && stride > 0 && length > 0) {
        result.memory = memory;
        result.stride = stride;
        result.length = length;
    }

    return result;
}

Queue
queue_reserve_mem(Arena* arena, isiz stride, isiz length)
{
    Queue result = {};
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
queue_release(Queue* self)
{
    if (self->arena != 0 && self->memory != 0)
        arena_release(self->arena, self->memory);

    self->arena  = 0;
    self->memory = 0;
    self->stride = 0;
    self->length = 0;
    self->size   = 0;
    self->head   = 0;
    self->tail   = 0;
}

Queue
queue_copy(Arena* arena, Queue* value)
{
    return queue_copy_len(arena, value, value->size);
}

Queue
queue_copy_len(Arena* arena, Queue* value, isiz length)
{
    Queue result = queue_reserve_mem(arena, value->stride, length);

    if (result.length <= 0) return result;

    result.size = pax_limit(value->size, 0, length);
    result.tail = result.size;

    for (isiz i = 0; i < result.size; i += 1) {
        isiz j = (value->head + i) % value->length;

        mem8_copy(result.memory + (i * result.stride),
            value->memory + (j * result.stride), result.stride);
    }

    return result;
}

b32
queue_grow(Queue* self, isiz length)
{
    Queue copy = {};

    if (self->length >= length) return 1;

    copy = queue_copy_len(self->arena, self, length);

    if (copy.length > 0) {
        queue_release(self);

        self->arena  = copy.arena;
        self->memory = copy.memory;
        self->stride = copy.stride;
        self->length = copy.length;
        self->size   = copy.size;
        self->head   = copy.head;
        self->tail   = copy.tail;

        return 1;
    }

    return 0;
}

void
queue_clear(Queue* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

b32
queue_insert_head_mem(Queue* self, void* memory, isiz stride)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (self->stride != stride || memory == 0) return 0;

    isiz prev = self->head + self->length - 1;

    self->size += 1;
    self->head  = prev % self->length;

    isiz index = self->head;

    mem8_copy(self->memory + (index * stride), memory, stride);

    return 1;
}

b32
queue_insert_tail_mem(Queue* self, void* memory, isiz stride)
{
    if (self->size < 0 || self->size >= self->length)
        return 0;

    if (self->stride != stride || memory == 0) return 0;

    isiz index = self->tail;

    mem8_copy(self->memory + (index * stride), memory, stride);

    isiz next = self->tail + 1;

    self->size += 1;
    self->tail  = next % self->length;

    return 1;
}

b32
queue_remove_head_mem(Queue* self, void* memory, isiz stride)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    if (self->stride != stride) return 0;

    isiz index = self->head;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    isiz next = self->head + 1;

    self->size -= 1;
    self->head  = next % self->length;

    return 1;
}

b32
queue_remove_tail_mem(Queue* self, void* memory, isiz stride)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    if (self->stride != stride) return 0;

    isiz prev = self->tail + self->length - 1;

    self->size -= 1;
    self->tail  = prev % self->length;

    isiz index = self->tail;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    return 1;
}

b32
queue_drop_head(Queue* self)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    isiz next = self->head + 1;

    self->size -= 1;
    self->head  = next % self->length;

    return 1;
}

b32
queue_drop_tail(Queue* self)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    isiz prev = self->tail + self->length - 1;

    self->size -= 1;
    self->tail  = prev % self->length;

    return 1;
}

b32
queue_get_mem(Queue* self, isiz index, void* memory, isiz stride)
{
    if (index < 0 || index >= self->size) return 0;

    if (self->stride != stride) return 0;

    index = (self->head + index) % self->length;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    return 1;
}

b32
queue_get_head_mem(Queue* self, void* memory, isiz stride)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    if (self->stride != stride) return 0;

    isiz index = self->head;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    return 1;
}

b32
queue_get_tail_mem(Queue* self, void* memory, isiz stride)
{
    if (self->size <= 0 || self->size > self->length)
        return 0;

    if (self->stride != stride) return 0;

    isiz index = (self->tail + self->length - 1) % self->length;

    if (memory != 0)
        mem8_copy(memory, self->memory + (index * stride), stride);

    return 1;
}

} // namespace pax

#endif // PAX_STRUCTURE_QUEUE_CPP
