#ifndef PAX_STRING_BUF8_HPP
#define PAX_STRING_BUF8_HPP

#include "convert.hpp"

namespace pax {

//
// Procs
//

/* buf8 writing */

isiz
buf8_write_utf8_head(buf8* self, u32 value);

isiz
buf8_write_str8_head(buf8* self, str8 value);

isiz
buf8_write_str16_head(buf8* self, str16 value);

isiz
buf8_write_str32_head(buf8* self, str32 value);

isiz
buf8_write_utf8_tail(buf8* self, u32 value);

isiz
buf8_write_str8_tail(buf8* self, str8 value);

isiz
buf8_write_str16_tail(buf8* self, str16 value);

isiz
buf8_write_str32_tail(buf8* self, str32 value);

/* buf8 reading */

isiz
buf8_read_utf8_head(buf8* self, u32* value);

isiz
buf8_read_utf8_tail(buf8* self, u32* value);

str8
buf8_read_str8_head(buf8* self, Arena* arena, isiz length);

str8
buf8_read_str8_tail(buf8* self, Arena* arena, isiz length);

} // namespace pax

#endif // PAX_STRING_BUF8_HPP
