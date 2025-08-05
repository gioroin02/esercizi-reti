#ifndef PAX_FORMAT_BUF32_HPP
#define PAX_FORMAT_BUF32_HPP

#include "options.hpp"

namespace pax {

//
// Procs
//

/* buf32 writing unsigned */

b32
buf32_write_usiz_tail(buf32* self, Format_Options options, usiz value);

b32
buf32_write_u64_tail(buf32* self, Format_Options options, u64 value);

b32
buf32_write_u32_tail(buf32* self, Format_Options options, u32 value);

b32
buf32_write_u16_tail(buf32* self, Format_Options options, u16 value);

b32
buf32_write_u8_tail(buf32* self, Format_Options options, u8 value);

/* buf32 reading unsigned */

b32
buf32_read_usiz_head(buf32* self, Format_Options options, usiz* value);

b32
buf32_read_u64_head(buf32* self, Format_Options options, u64* value);

b32
buf32_read_u32_head(buf32* self, Format_Options options, u32* value);

b32
buf32_read_u16_head(buf32* self, Format_Options options, u16* value);

b32
buf32_read_u8_head(buf32* self, Format_Options options, u8* value);

/* buf32 writing integer */

b32
buf32_write_isiz_tail(buf32* self, Format_Options options, isiz value);

b32
buf32_write_i64_tail(buf32* self, Format_Options options, i64 value);

b32
buf32_write_i32_tail(buf32* self, Format_Options options, i32 value);

b32
buf32_write_i16_tail(buf32* self, Format_Options options, i16 value);

b32
buf32_write_i8_tail(buf32* self, Format_Options options, i8 value);

/* buf32 reading integer */

b32
buf32_read_isiz_head(buf32* self, Format_Options options, isiz* value);

b32
buf32_read_i64_head(buf32* self, Format_Options options, i64* value);

b32
buf32_read_i32_head(buf32* self, Format_Options options, i32* value);

b32
buf32_read_i16_head(buf32* self, Format_Options options, i16* value);

b32
buf32_read_i8_head(buf32* self, Format_Options options, i8* value);

} // namespace pax

#endif // PAX_FORMAT_BUF32_HPP
