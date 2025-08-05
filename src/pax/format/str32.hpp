#ifndef PAX_FORMAT_STR32_HPP
#define PAX_FORMAT_STR32_HPP

#include "options.hpp"

namespace pax {

/* str32 writing unsigned */

str32
str32_from_usiz(Arena* arena, Format_Options options, usiz value);

str32
str32_from_u64(Arena* arena, Format_Options options, u64 value);

str32
str32_from_u32(Arena* arena, Format_Options options, u32 value);

str32
str32_from_u16(Arena* arena, Format_Options options, u16 value);

str32
str32_from_u8(Arena* arena, Format_Options options, u8 value);

/* str32 reading unsigned */

b32
usiz_from_str32(str32 self, Format_Options options, usiz* value);

b32
u64_from_str32(str32 self, Format_Options options, u64* value);

b32
u32_from_str32(str32 self, Format_Options options, u32* value);

b32
u16_from_str32(str32 self, Format_Options options, u16* value);

b32
u8_from_str32(str32 self, Format_Options options, u8* value);

/* str32 writing integer */

str32
str32_from_isiz(Arena* arena, Format_Options options, isiz value);

str32
str32_from_i64(Arena* arena, Format_Options options, i64 value);

str32
str32_from_i32(Arena* arena, Format_Options options, i32 value);

str32
str32_from_i16(Arena* arena, Format_Options options, i16 value);

str32
str32_from_i8(Arena* arena, Format_Options options, i8 value);

/* str32 reading integer */

b32
isiz_from_str32(str32 self, Format_Options options, isiz* value);

b32
i64_from_str32(str32 self, Format_Options options, i64* value);

b32
i32_from_str32(str32 self, Format_Options options, i32* value);

b32
i16_from_str32(str32 self, Format_Options options, i16* value);

b32
i8_from_str32(str32 self, Format_Options options, i8* value);

} // namespace pax

#endif // PAX_FORMAT_STR32_HPP
