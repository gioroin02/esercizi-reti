#ifndef PAX_FORMAT_BUF8_HPP
#define PAX_FORMAT_BUF8_HPP

#include "options.hpp"

namespace pax {

//
// Procs
//

/* buf8 writing unsigned */

b32
buf8_write_uptr_tail(buf8* self, Format_Options opts, uptr value);

b32
buf8_write_u64_tail(buf8* self, Format_Options opts, u64 value);

b32
buf8_write_u32_tail(buf8* self, Format_Options opts, u32 value);

b32
buf8_write_u16_tail(buf8* self, Format_Options opts, u16 value);

b32
buf8_write_u8_tail(buf8* self, Format_Options opts, u8 value);

/* buf8 reading unsigned */

b32
buf8_read_uptr_head(buf8* self, Format_Options opts, uptr* value);

b32
buf8_read_u64_head(buf8* self, Format_Options opts, u64* value);

b32
buf8_read_u32_head(buf8* self, Format_Options opts, u32* value);

b32
buf8_read_u16_head(buf8* self, Format_Options opts, u16* value);

b32
buf8_read_u8_head(buf8* self, Format_Options opts, u8* value);

/* buf8 writing integer */

b32
buf8_write_iptr_tail(buf8* self, Format_Options opts, iptr value);

b32
buf8_write_i64_tail(buf8* self, Format_Options opts, i64 value);

b32
buf8_write_i32_tail(buf8* self, Format_Options opts, i32 value);

b32
buf8_write_i16_tail(buf8* self, Format_Options opts, i16 value);

b32
buf8_write_i8_tail(buf8* self, Format_Options opts, i8 value);

/* buf8 reading integer */

b32
buf8_read_iptr_head(buf8* self, Format_Options opts, iptr* value);

b32
buf8_read_i64_head(buf8* self, Format_Options opts, i64* value);

b32
buf8_read_i32_head(buf8* self, Format_Options opts, i32* value);

b32
buf8_read_i16_head(buf8* self, Format_Options opts, i16* value);

b32
buf8_read_i8_head(buf8* self, Format_Options opts, i8* value);

} // namespace pax

#endif // PAX_FORMAT_BUF8_HPP
