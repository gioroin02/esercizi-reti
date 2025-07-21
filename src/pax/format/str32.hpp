#ifndef PAX_FORMAT_STR32_HPP
#define PAX_FORMAT_STR32_HPP

#include "options.hpp"

namespace pax {

/* str32 printing unsigned */

str32
str32_from_uptr(Arena* arena, Format_Options opts, uptr value);

str32
str32_from_u64(Arena* arena, Format_Options opts, u64 value);

str32
str32_from_u32(Arena* arena, Format_Options opts, u32 value);

str32
str32_from_u16(Arena* arena, Format_Options opts, u16 value);

str32
str32_from_u8(Arena* arena, Format_Options opts, u8 value);

/* str32 parsing unsigned */

b32
uptr_from_str32(str32 self, Format_Options opts, uptr* value);

b32
u64_from_str32(str32 self, Format_Options opts, u64* value);

b32
u32_from_str32(str32 self, Format_Options opts, u32* value);

b32
u16_from_str32(str32 self, Format_Options opts, u16* value);

b32
u8_from_str32(str32 self, Format_Options opts, u8* value);

/* str32 printing integer */

str32
str32_from_iptr(Arena* arena, Format_Options opts, iptr value);

str32
str32_from_i64(Arena* arena, Format_Options opts, i64 value);

str32
str32_from_i32(Arena* arena, Format_Options opts, i32 value);

str32
str32_from_i16(Arena* arena, Format_Options opts, i16 value);

str32
str32_from_i8(Arena* arena, Format_Options opts, i8 value);

/* str32 parsing integer */

b32
iptr_from_str32(str32 self, Format_Options opts, iptr* value);

b32
i64_from_str32(str32 self, Format_Options opts, i64* value);

b32
i32_from_str32(str32 self, Format_Options opts, i32* value);

b32
i16_from_str32(str32 self, Format_Options opts, i16* value);

b32
i8_from_str32(str32 self, Format_Options opts, i8* value);

} // namespace pax

#endif // PAX_FORMAT_STR32_HPP
