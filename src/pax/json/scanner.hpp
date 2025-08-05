#ifndef PAX_JSON_SCANNER_HPP
#define PAX_JSON_SCANNER_HPP

#include "token.hpp"

namespace pax {

//
// Types
//

struct JSON_Scanner
{
    buf8* buffer = 0;
    isiz  line   = 0;
    isiz  column = 0;
};

//
// Procs
//

/* JSON_Scanner */

JSON_Scanner
json_scanner_make(buf8* buffer, isiz line, isiz column);

buf8*
json_scanner_set_buffer(JSON_Scanner* self, buf8* buffer);

JSON_Token
json_scanner_token(JSON_Scanner* self, Arena* arena);

str8
json_scanner_symbol(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type);

str8
json_scanner_string(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type);

str8
json_scanner_number(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type);

JSON_Token
json_scanner_absolute(JSON_Scanner* self, Arena* arena, str8 string);

JSON_Token
json_scanner_relative(JSON_Scanner* self, Arena* arena, str8 string);

JSON_Token
json_scanner_floating(JSON_Scanner* self, Arena* arena, str8 string);

str8
json_scanner_word(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type);

/* JSON_Scanner helpers */

u32
json_scanner_peek(JSON_Scanner* self, isiz offset);

u32
json_scanner_step(JSON_Scanner* self, isiz offset);

u32
json_scanner_expect(JSON_Scanner* self, u32 value);

u32
json_scanner_skip_spaces(JSON_Scanner* self);

} // namespace pax

#endif // PAX_JSON_SCANNER_HPP
