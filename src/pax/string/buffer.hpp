#ifndef PAX_STRING_BUFFER_HPP
#define PAX_STRING_BUFFER_HPP

#include "str8.hpp"

namespace pax {

b32
buffer_write_str8_head(Buffer* self, str8 value);

b32
buffer_write_str8_tail(Buffer* self, str8 value);

str8
buffer_read_str8_head(Buffer* self, Arena* arena, uptr length);

str8
buffer_read_str8_tail(Buffer* self, Arena* arena, uptr length);

} // namespace pax

#endif // PAX_STRING_BUFFER_HPP
