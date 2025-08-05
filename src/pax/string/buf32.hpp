#ifndef PAX_STRING_BUF32_HPP
#define PAX_STRING_BUF32_HPP

#include "convert.hpp"

namespace pax {

//
// Procs
//

/* buf32 writing */

isiz
buf32_write_utf32_head(buf32* self, u32 value);

isiz
buf32_write_str8_head(buf32* self, str8 value);

isiz
buf32_write_str16_head(buf32* self, str16 value);

isiz
buf32_write_str32_head(buf32* self, str32 value);

isiz
buf32_write_utf32_tail(buf32* self, u32 value);

isiz
buf32_write_str8_tail(buf32* self, str8 value);

isiz
buf32_write_str16_tail(buf32* self, str16 value);

isiz
buf32_write_str32_tail(buf32* self, str32 value);

/* buf32 reading */

isiz
buf32_read_utf32_head(buf32* self, u32* value);

isiz
buf32_read_utf32_tail(buf32* self, u32* value);

str32
buf32_read_str32_head(buf32* self, Arena* arena, isiz length);

str32
buf32_read_str32_tail(buf32* self, Arena* arena, isiz length);

} // namespace pax

#endif // PAX_STRING_BUF32_HPP
