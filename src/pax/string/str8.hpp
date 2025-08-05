#ifndef PAX_STRING_STR8_HPP
#define PAX_STRING_STR8_HPP

#include "ascii.hpp"
#include "utf8.hpp"

//
// Defines
//

#define pax_str8(expr) \
    str8_make(pax_as_u8p(expr), pax_array_length(expr) - 1)

#define pax_str8_cnt(expr) \
    str8_count(pax_as_u8p(expr))

#define pax_str8_max(expr, limit) \
    str8_count_max(pax_as_u8p(expr), limit)

#define pax_to_str8(expr) pax_str8(pax_string(expr))

namespace pax {

//
// Types
//

struct str8
{
    u8*  memory = 0;
    isiz length = 0;
};

//
// Procs
//

/* str8 */

str8
str8_make(u8* memory, isiz length);

str8
str8_reserve(Arena* arena, isiz length);

str8
str8_copy(Arena* arena, str8 value);

str8
str8_copy_mem(Arena* arena, u8* memory, isiz length);

str8
str8_from_unicode(Arena* arena, u32 value);

b32
str8_get(str8 self, isiz index, u8* value);

u8
str8_get_or(str8 self, isiz index, u8 value);

/* str8 counting */

str8
str8_count(u8* memory);

str8
str8_count_max(u8* memory, isiz limit);

/* str8 comparison */

b32
str8_is_equal(str8 self, str8 value);

b32
str8_starts_with(str8 self, str8 value);

b32
str8_ends_with(str8 self, str8 value);

/* str8 slicing */

str8
str8_slice(str8 self, isiz start, isiz stop);

str8
str8_slice_len(str8 self, isiz index, isiz length);

str8
str8_slice_until_first(str8 self, str8 value);

str8
str8_slice_until_last(str8 self, str8 value);

str8
str8_slice_since_first(str8 self, str8 value);

str8
str8_slice_since_last(str8 self, str8 value);

/* str8 chaining */

str8
str8_chain(Arena* arena, str8 value, str8 other);

/* str8 splitting */

str8
str8_split_on(str8 self, str8 pivot, str8* value);

/* str8 trimming */

str8
str8_trim_prefix(str8 self, str8 prefix);

str8
str8_trim_suffix(str8 self, str8 suffix);

str8
str8_trim_spaces(str8 self);

str8
str8_trim_spaces_start(str8 self);

str8
str8_trim_spaces_end(str8 self);

/* str8 searching */

b32
str8_find_first(str8 self, str8 value, isiz* index);

b32
str8_find_first_since(str8 self, str8 value, isiz since, isiz* index);

b32
str8_find_last(str8 self, str8 value, isiz* index);

b32
str8_find_last_until(str8 self, str8 value, isiz until, isiz* index);

isiz
str8_contains(str8 self, str8 value);

/* str8 iterating */

b32
str8_next(str8 self, isiz index, isiz* units, u32* value);

b32
str8_prev(str8 self, isiz index, isiz* units, u32* value);

/* str8 writing */

isiz
str8_write_utf8_forw(str8 self, isiz index, u32 value);

isiz
str8_write_utf8_back(str8 self, isiz index, u32 value);

/* str32 reading */

isiz
str8_read_utf8_forw(str8 self, isiz index, u32* value);

isiz
str8_read_utf8_back(str8 self, isiz index, u32* value);

} // namespace pax

#endif // PAX_STRING_STR8_HPP
