#ifndef PAX_FORMAT_PARSE_UNSIGNED_HPP
#define PAX_FORMAT_PARSE_UNSIGNED_HPP

#include "format_spec.hpp"

namespace pax {

//
// Procs
//

/* str8 */

b32
str8_parse_u64(str8 self, Format_Spec spec, u64* value);

b32
str8_parse_u32(str8 self, Format_Spec spec, u32* value);

b32
str8_parse_u16(str8 self, Format_Spec spec, u16* value);

b32
str8_parse_u8(str8 self, Format_Spec spec, u8* value);

/* str16 */

b32
str16_parse_u64(str16 self, Format_Spec spec, u64* value);

b32
str16_parse_u32(str16 self, Format_Spec spec, u32* value);

b32
str16_parse_u16(str16 self, Format_Spec spec, u16* value);

b32
str16_parse_u8(str16 self, Format_Spec spec, u8* value);

/* str32 */

b32
str32_parse_u64(str32 self, Format_Spec spec, u64* value);

b32
str32_parse_u32(str32 self, Format_Spec spec, u32* value);

b32
str32_parse_u16(str32 self, Format_Spec spec, u16* value);

b32
str32_parse_u8(str32 self, Format_Spec spec, u8* value);

/* Buffer */

b32
buffer_parse_u64(Buffer* self, Format_Spec spec, u64* value);

b32
buffer_parse_u32(Buffer* self, Format_Spec spec, u32* value);

b32
buffer_parse_u16(Buffer* self, Format_Spec spec, u16* value);

b32
buffer_parse_u8(Buffer* self, Format_Spec spec, u8* value);

} // namespace pax

#endif // PAX_FORMAT_PARSE_UNSIGNED_HPP
