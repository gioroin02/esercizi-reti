#ifndef PAX_STRING_BUF16_HPP
#define PAX_STRING_BUF16_HPP

#include "convert.hpp"

namespace pax {

//
// Procs
//

/* buf16 writing */

isiz
buf16_write_utf16_head(buf16* self, u32 value);

isiz
buf16_write_str8_head(buf16* self, str8 value);

isiz
buf16_write_str16_head(buf16* self, str16 value);

isiz
buf16_write_str32_head(buf16* self, str32 value);

isiz
buf16_write_utf16_tail(buf16* self, u32 value);

isiz
buf16_write_str8_tail(buf16* self, str8 value);

isiz
buf16_write_str16_tail(buf16* self, str16 value);

isiz
buf16_write_str32_tail(buf16* self, str32 value);

/* buf16 reading */

isiz
buf16_read_utf16_head(buf16* self, u32* value);

isiz
buf16_read_utf16_tail(buf16* self, u32* value);

str16
buf16_read_str16_head(buf16* self, Arena* arena, isiz length);

str16
buf16_read_str16_tail(buf16* self, Arena* arena, isiz length);

} // namespace pax

#endif // PAX_STRING_BUF16_HPP
