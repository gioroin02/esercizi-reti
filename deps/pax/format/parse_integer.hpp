#ifndef PAX_FORMAT_PARSE_INTEGER_HPP
#define PAX_FORMAT_PARSE_INTEGER_HPP

#include "format_spec.hpp"

namespace pax {

//
// Procs
//

/* str8 */

b32
str8_parse_i64(str8 self, Format_Spec spec, i64* value);

b32
str8_parse_i32(str8 self, Format_Spec spec, i32* value);

b32
str8_parse_i16(str8 self, Format_Spec spec, i16* value);

b32
str8_parse_i8(str8 self, Format_Spec spec, i8* value);

/* str16 */

b32
str16_parse_i64(str16 self, Format_Spec spec, i64* value);

b32
str16_parse_i32(str16 self, Format_Spec spec, i32* value);

b32
str16_parse_i16(str16 self, Format_Spec spec, i16* value);

b32
str16_parse_i8(str16 self, Format_Spec spec, i8* value);

/* str32 */

b32
str32_parse_i64(str32 self, Format_Spec spec, i64* value);

b32
str32_parse_i32(str32 self, Format_Spec spec, i32* value);

b32
str32_parse_i16(str32 self, Format_Spec spec, i16* value);

b32
str32_parse_i8(str32 self, Format_Spec spec, i8* value);

/* Buffer */

b32
buffer_parse_i64(Buffer* self, Format_Spec spec, i64* value);

b32
buffer_parse_i32(Buffer* self, Format_Spec spec, i32* value);

b32
buffer_parse_i16(Buffer* self, Format_Spec spec, i16* value);

b32
buffer_parse_i8(Buffer* self, Format_Spec spec, i8* value);

} // namespace pax

#endif // PAX_FORMAT_PARSE_INTEGER_HPP
