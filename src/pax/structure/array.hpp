#ifndef PAX_STRUCTURE_ARRAY_HPP
#define PAX_STRUCTURE_ARRAY_HPP

#include "imports.hpp"

//
// Defines
//

#define pax_array_reserve(arena, type, length) \
    array_reserve_mem(arena, pax_size_of(type), length)

#define pax_array_insert(self, index, type, value) \
    array_insert_mem(self, index, value, pax_size_of(type))

#define pax_array_insert_head(self, type, value) \
    array_insert_head_mem(self, value, pax_size_of(type))

#define pax_array_insert_tail(self, type, value) \
    array_insert_tail_mem(self, value, pax_size_of(type))

#define pax_array_remove(self, index, type, value) \
    array_remove_mem(self, index, value, pax_size_of(type))

#define pax_array_remove_head(self, type, value) \
    array_remove_head_mem(self, value, pax_size_of(type))

#define pax_array_remove_tail(self, type, value) \
    array_remove_tail_mem(self, value, pax_size_of(type))

#define pax_array_get(self, index, type, value) \
    array_get_mem(self, index, value, pax_size_of(type))

#define pax_array_get_head(self, type, value) \
    array_get_head_mem(self, value, pax_size_of(type))

#define pax_array_get_tail(self, type, value) \
    array_get_tail_mem(self, value, pax_size_of(type))

#define pax_array_assign(self, index, type, value) \
    array_assign_mem(self, index, value, pax_size_of(type))

#define pax_array_assign_head(self) \
    array_assign_head_mem(self, value, pax_size_of(type))

#define pax_array_assign_tail(self) \
    array_assign_tail_mem(self, value, pax_size_of(type))

namespace pax {

//
// Types
//

struct Array
{
    Arena* arena = 0;

    u8*  memory = 0;
    isiz stride = 0;
    isiz length = 0;
    isiz size   = 0;
};

//
// Procs
//

Array
array_make(u8* memory, isiz stride, isiz length);

Array
array_reserve_mem(Arena* arena, isiz stride, isiz length);

void
array_release(Array* self);

Array
array_copy(Arena* arena, Array* value);

Array
array_copy_len(Arena* arena, Array* value, isiz length);

b32
array_grow(Array* self, isiz length);

b32
array_swap(Array* self, isiz index, usiz other);

b32
array_swap_head(Array* self, isiz index);

b32
array_swap_tail(Array* self, isiz index);

void
array_clear(Array* self);

b32
array_insert_mem(Array* self, isiz index, void* memory, isiz stride);

b32
array_insert_head_mem(Array* self, void* memory, isiz stride);

b32
array_insert_tail_mem(Array* self, void* memory, isiz stride);

b32
array_remove_mem(Array* self, isiz index, void* memory, isiz stride);

b32
array_remove_head_mem(Array* self, void* memory, isiz stride);

b32
array_remove_tail_mem(Array* self, void* memory, isiz stride);

b32
array_drop(Array* self, isiz index);

b32
array_drop_head(Array* self);

b32
array_drop_tail(Array* self);

b32
array_get_mem(Array* self, isiz index, void* memory, isiz stride);

b32
array_get_head_mem(Array* self, void* memory, isiz stride);

b32
array_get_tail_mem(Array* self, void* memory, isiz stride);

b32
array_assign_mem(Array* self, isiz index, void* memory, isiz stride);

b32
array_assign_head_mem(Array* self, void* memory, isiz stride);

b32
array_assign_tail_mem(Array* self, void* memory, isiz stride);

#ifdef __cplusplus

template <class V>
Array
array_reserve(Arena* arena, isiz length)
{
    return array_reserve_mem(arena, pax_size_of(V), length);
}

template <class V>
b32
array_insert(Array* self, isiz index, V value)
{
    return array_insert_mem(self, index, &value, pax_size_of(V));
}

template <class V>
b32
array_insert_head(Array* self, V value)
{
    return array_insert_head_mem(self, &value, pax_size_of(V));
}

template <class V>
b32
array_insert_tail(Array* self, V value)
{
    return array_insert_tail_mem(self, &value, pax_size_of(V));
}

template <class V>
b32
array_remove(Array* self, isiz index, V* value)
{
    return array_remove_mem(self, index, value, pax_size_of(V));
}

template <class V>
V
array_remove_or(Array* self, isiz index, V other)
{
    V result = {};

    if (array_remove_mem(self, index, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
array_remove_head(Array* self, V* value)
{
    return array_remove_head_mem(self, value, pax_size_of(V));
}

template <class V>
V
array_remove_head_or(Array* self, V other)
{
    V result = {};

    if (array_remove_head_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}


template <class V>
b32
array_remove_tail(Array* self, V* value)
{
    return array_remove_tail_mem(self, value, pax_size_of(V));
}

template <class V>
V
array_remove_tail_or(Array* self, V other)
{
    V result = {};

    if (array_remove_tail_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
array_get(Array* self, isiz index, V* value)
{
    return array_get_mem(self, index, value, pax_size_of(V));
}

template <class V>
V
array_get_or(Array* self, isiz index, V other)
{
    V result = {};

    if (array_get_mem(self, index, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
array_get_head(Array* self, V* value)
{
    return array_get_head_mem(self, value, pax_size_of(V));
}

template <class V>
V
array_get_head_or(Array* self, V other)
{
    V result = {};

    if (array_get_head_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
array_get_tail(Array* self, V* value)
{
    return array_get_tail_mem(self, value, pax_size_of(V));
}

template <class V>
V
array_get_tail_or(Array* self, V other)
{
    V result = {};

    if (array_get_tail_mem(self, &result, pax_size_of(V)) == 0)
        return other;

    return result;
}

template <class V>
b32
array_assign(Array* self, isiz index, V value)
{
    return array_assign_mem(self, index, &value, pax_size_of(V));
}

template <class V>
b32
array_assign_head(Array* self, V value)
{
    return array_assign_head_mem(self, &value, pax_size_of(V));
}

template <class V>
b32
array_assign_tail(Array* self, V value)
{
    return array_assign_tail_mem(self, &value, pax_size_of(V));
}

#endif // __cplusplus

} // namespace pax

#endif // PAX_STRUCTURE_ARRAY_HPP
