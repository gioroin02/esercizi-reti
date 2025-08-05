#ifndef PAX_STRING_STR32_CPP
#define PAX_STRING_STR32_CPP

#include "str32.hpp"

namespace pax {

str32
str32_make(u32* memory, isiz length)
{
    str32 result = {};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

str32
str32_reserve(Arena* arena, isiz length)
{
    return str32_make(pax_arena_reserve(arena, u32, length + 1), length);
}

str32
str32_copy(Arena* arena, str32 value)
{
    return str32_copy_mem(arena, value.memory, value.length);
}

str32
str32_copy_mem(Arena* arena, u32* memory, isiz length)
{
    str32 result = str32_reserve(arena, length);

    if (result.length <= 0) return result;

    mem32_copy(result.memory, memory, result.length);

    return result;
}

str32
str32_from_unicode(Arena* arena, u32 value)
{
    isiz  units  = utf32_units_to_write(value);
    str32 result = str32_reserve(arena, units);

    if (result.length <= 0) return result;

    str32_write_utf32_forw(result, 0, value);

    return result;
}

b32
str32_get(str32 self, isiz index, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (value != 0) *value = self.memory[index];

    return 1;
}

u32
str32_get_or(str32 self, isiz index, u32 value)
{
    if (index < 0 || index >= self.length)
        return value;

    return self.memory[index];
}

str32
str32_count(u32* memory)
{
    isiz index = 0;

    while (memory[index] != 0)
        index += 1;

    return str32_make(memory, index);
}

str32
str32_count_max(u32* memory, isiz limit)
{
    isiz index = 0;

    while (memory[index] != 0) {
        index += 1;

        if (index > limit)
            return {};
    }

    return str32_make(memory, index);
}

b32
str32_is_equal(str32 self, str32 value)
{
    if (self.length == value.length)
        return mem32_is_equal(self.memory, value.memory, self.length);

    return 0;
}

b32
str32_starts_with(str32 self, str32 value)
{
    isiz start  = 0;
    isiz length = value.length;

    str32 slice = str32_slice_len(self, start, length);

    if (self.length >= value.length)
        return str32_is_equal(slice, value);

    return 0;
}

b32
str32_ends_with(str32 self, str32 value)
{
    isiz start  = self.length - value.length;
    isiz length = value.length;

    str32 slice = str32_slice_len(self, start, length);

    if (self.length >= value.length)
        return str32_is_equal(slice, value);

    return 0;
}

str32
str32_slice(str32 self, isiz start, isiz stop)
{
    str32 result = {};

    start = pax_limit(start, 0, self.length);
    stop  = pax_limit(stop, 0, self.length);

    isiz length = stop - start;

    if (start <= stop)
        result = str32_make(self.memory + start, length);

    return result;
}

str32
str32_slice_len(str32 self, isiz index, isiz length)
{
    return str32_slice(self, index, index + length);
}

str32
str32_slice_until_first(str32 self, str32 value)
{
    isiz start = 0;
    isiz stop  = self.length;

    str32_find_first(self, value, &stop);

    return str32_slice(self, start, stop);
}

str32
str32_slice_until_last(str32 self, str32 value)
{
    isiz start = 0;
    isiz stop  = self.length;

    str32_find_last(self, value, &stop);

    return str32_slice(self, start, stop);
}

str32
str32_slice_since_first(str32 self, str32 value)
{
    isiz start = self.length;
    isiz stop  = self.length;

    str32_find_first(self, value, &start);

    return str32_slice(self, start + value.length, stop);
}

str32
str32_slice_since_last(str32 self, str32 value)
{
    isiz start = self.length;
    isiz stop  = self.length;

    str32_find_last(self, value, &start);

    return str32_slice(self, start + value.length, stop);
}

str32
str32_chain(Arena* arena, str32 value, str32 other)
{
    str32 result = str32_reserve(arena, value.length + other.length);

    if (result.length <= 0) return result;

    mem32_copy(result.memory, value.memory, value.length);

    mem32_copy(result.memory + value.length, other.memory,
        other.length);

    return result;
}

str32
str32_split_on(str32 self, str32 pivot, str32* value)
{
    isiz start = 0;
    isiz stop  = self.length;
    isiz index = self.length;

    str32_find_first(self, pivot, &index);

    if (value != 0)
        *value = str32_slice(self, index + pivot.length, stop);

    return str32_slice(self, start, index);
}

str32
str32_trim_prefix(str32 self, str32 prefix)
{
    if (str32_starts_with(self, prefix) == 0)
        return self;

    return str32_slice(self, prefix.length, self.length);
}

str32
str32_trim_suffix(str32 self, str32 suffix)
{
    if (str32_ends_with(self, suffix) == 0)
        return self;

    isiz length = self.length - suffix.length;

    return str32_slice(self, 0, length);
}

str32
str32_trim_spaces(str32 self)
{
    return str32_trim_spaces_start(str32_trim_spaces_end(self));
}

str32
str32_trim_spaces_start(str32 self)
{
    isiz units = 0;
    isiz start = 0;
    isiz stop  = self.length;

    for (; start < stop; start += units) {
        u32 unicode = 0;

        units = str32_read_utf32_forw(self, start, &unicode);

        if (units <= 0) return self;

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str32_slice(self, start, stop);
}

str32
str32_trim_spaces_end(str32 self)
{
    isiz units = 0;
    isiz start = 0;
    isiz stop  = self.length;

    for (; start < stop; stop -= units) {
        u32 unicode = 0;

        units = str32_read_utf32_back(self, stop - 1, &unicode);

        if (units <= 0) return self;

        if (ascii_is_space(unicode) == 0)
            break;
    }

    return str32_slice(self, start, stop);
}

b32
str32_find_first(str32 self, str32 value, isiz* index)
{
    return str32_find_first_since(self, value, 0, index);
}

b32
str32_find_first_since(str32 self, str32 value, isiz since, isiz* index)
{
    since = pax_limit(since, 0, self.length);

    for (isiz i = since; i < self.length; i += 1) {
        str32 slice = str32_slice_len(self, i, value.length);

        if (str32_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

b32
str32_find_last(str32 self, str32 value, isiz* index)
{
    return str32_find_last_until(self, value, self.length, index);
}

b32
str32_find_last_until(str32 self, str32 value, isiz until, isiz* index)
{
    until = pax_limit(until, 0, self.length);

    for (isiz i = until; i > 0; i -= 1) {
        str32 slice = str32_slice_len(self, i - value.length, value.length);

        if (str32_is_equal(slice, value) == 0)
            continue;

        if (index != 0) *index = i - value.length;

        return 1;
    }

    return 0;
}

usiz
str32_contains(str32 self, str32 value)
{
    isiz result = 0;

    if (value.length > self.length) return result;

    for (isiz i = 0; i < self.length; i += 1) {
        str32 slice = str32_slice_len(self, i, value.length);

        if (str32_is_equal(slice, value) != 0)
            result += 1;
    }

    return result;
}

b32
str32_next(str32 self, isiz index, isiz* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    isiz step = str32_read_utf32_forw(self, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

b32
str32_prev(str32 self, isiz index, isiz* units, u32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    isiz step = str32_read_utf32_back(self, index, value);

    if (units != 0) *units = step;

    return 1;
}

isiz
str32_write_utf32_forw(str32 self, isiz index, u32 value)
{
    return mem32_write_utf32_forw(self.memory, self.length, index, value);
}

isiz
str32_write_utf32_back(str32 self, isiz index, u32 value)
{
    return mem32_write_utf32_back(self.memory, self.length, index, value);
}

isiz
str32_read_utf32_forw(str32 self, isiz index, u32* value)
{
    return mem32_read_utf32_forw(self.memory, self.length, index, value);
}

isiz
str32_read_utf32_back(str32 self, isiz index, u32* value)
{
    return mem32_read_utf32_back(self.memory, self.length, index, value);
}

} // namespace pax

#endif // PAX_STRING_STR32_CPP
