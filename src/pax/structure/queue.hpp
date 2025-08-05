#ifndef PAX_STRUCTURE_QUEUE_HPP
#define PAX_STRUCTURE_QUEUE_HPP

#include "imports.hpp"

//
// Defines
//

#define pax_queue_reserve(arena, type, length) \
    queue_reserve_mem(arena, pax_size_of(type), length)

#define pax_queue_insert_head(self, type, value) \
    queue_insert_head_mem(self, value, pax_size_of(type))

#define pax_queue_insert_tail(self, type, value) \
    queue_insert_tail_mem(self, value, pax_size_of(type))

#define pax_queue_remove_head(self, type, value) \
    queue_remove_head_mem(self, value, pax_size_of(type))

#define pax_queue_remove_tail(self, type, value) \
    queue_remove_tail_mem(self, value, pax_size_of(type))

#define pax_queue_get(self, index, type, value) \
    queue_get_mem(self, index, value, pax_size_of(type))

#define pax_queue_get_head(self, type, value) \
    queue_get_head_mem(self, value, pax_size_of(type))

#define pax_queue_get_tail(self, type, value) \
    queue_get_tail_mem(self, value, pax_size_of(type))

namespace pax {

//
// Types
//

struct Queue
{
    Arena* arena = 0;

    u8*  memory = 0;
    isiz stride = 0;
    isiz length = 0;
    isiz size   = 0;
    usiz head   = 0;
    usiz tail   = 0;
};

//
// Procs
//

/* Queue */

Queue
queue_make(u8* memory, isiz stride, isiz length);

Queue
queue_reserve_mem(Arena* arena, isiz stride, isiz length);

void
queue_release(Queue* self);

Queue
queue_copy(Arena* arena, Queue* value);

Queue
queue_copy_len(Arena* arena, Queue* value, isiz length);

b32
queue_grow(Queue* self, isiz length);

void
queue_clear(Queue* self);

b32
queue_insert_head_mem(Queue* self, void* memory, isiz stride);

b32
queue_insert_tail_mem(Queue* self, void* memory, isiz stride);

b32
queue_remove_head_mem(Queue* self, void* memory, isiz stride);

b32
queue_remove_tail_mem(Queue* self, void* memory, isiz stride);

b32
queue_drop_head(Queue* self);

b32
queue_drop_tail(Queue* self);

b32
queue_get_mem(Queue* self, isiz index, void* memory, isiz stride);

b32
queue_get_head_mem(Queue* self, void* memory, isiz stride);

b32
queue_get_tail_mem(Queue* self, void* memory, isiz stride);

#ifdef __cplusplus

template <class V>
Queue
queue_reserve(Arena* arena, isiz length)
{
    return queue_reserve_mem(arena, pax_size_of(V), length);
}

template <class V>
b32
queue_insert_head(Queue* self, V value)
{
    return queue_insert_head_mem(self, &value, pax_size_of(V));
}

template <class V>
b32
queue_insert_tail(Queue* self, V value)
{
    return queue_insert_tail_mem(self, &value, pax_size_of(V));
}

template <class V>
b32
queue_remove_head(Queue* self, V* value)
{
    return queue_remove_head_mem(self, value, pax_size_of(V));
}

template <class V>
V
queue_remove_head_or(Queue* self, V other)
{
    V result = {};

    if (queue_remove_head_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
queue_remove_tail(Queue* self, V* value)
{
    return queue_remove_tail_mem(self, value, pax_size_of(V));
}

template <class V>
V
queue_remove_tail_or(Queue* self, V other)
{
    V result = {};

    if (queue_remove_tail_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
queue_get(Queue* self, isiz index, V* value)
{
    return queue_get_mem(self, index, value, pax_size_of(V));
}

template <class V>
V
queue_get_or(Queue* self, isiz index, V other)
{
    V result = {};

    if (queue_get_mem(self, index, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
queue_get_head(Queue* self, V* value)
{
    return queue_get_head_mem(self, value, pax_size_of(V));
}

template <class V>
V
queue_get_head_or(Queue* self, V other)
{
    V result = {};

    if (queue_get_head_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
queue_get_tail(Queue* self, V* value)
{
    return queue_get_tail_mem(self, value, pax_size_of(V));
}

template <class V>
V
queue_get_tail_or(Queue* self, V other)
{
    V result = {};

    if (queue_get_tail_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

#endif // __cplusplus

} // namespace pax

#endif // PAX_STRUCTURE_QUEUE_HPP
