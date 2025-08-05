#ifndef PAX_STRING_CONVERT_HPP
#define PAX_STRING_CONVERT_HPP

#include "str8.hpp"
#include "str16.hpp"
#include "str32.hpp"

namespace pax {

//
// Procs
//

/* UTF8 units */

isiz
utf8_units_from_mem16(u16* memory, isiz length);

isiz
utf8_units_from_str16(str16 value);

isiz
utf8_units_from_mem32(u32* memory, isiz length);

isiz
utf8_units_from_str32(str32 value);

/* UTF16 units */

isiz
utf16_units_from_mem8(u8* memory, isiz length);

isiz
utf16_units_from_str8(str8 value);

isiz
utf16_units_from_mem32(u32* memory, isiz length);

isiz
utf16_units_from_str32(str32 value);

/* UTF32 units */

isiz
utf32_units_from_mem8(u8* memory, isiz length);

isiz
utf32_units_from_str8(str8 value);

isiz
utf32_units_from_mem16(u16* memory, isiz length);

isiz
utf32_units_from_str16(str16 value);

/* str8 */

str8
str8_from_str16(Arena* arena, str16 value);

str8
str8_from_str32(Arena* arena, str32 value);

/* str16 */

str16
str16_from_str8(Arena* arena, str8 value);

str16
str16_from_str32(Arena* arena, str32 value);

/* str32 */

str32
str32_from_str8(Arena* arena, str8 value);

str32
str32_from_str16(Arena* arena, str16 value);

} // namespace pax

#endif // PAX_STRING_CONVERT_HPP
