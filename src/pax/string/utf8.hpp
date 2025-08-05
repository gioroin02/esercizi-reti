#ifndef PAX_STRING_UTF8_HPP
#define PAX_STRING_UTF8_HPP

#include "unicode.hpp"

namespace pax {

//
// Values
//

static const isiz UTF8_MAX_UNITS = 4;
static const isiz UTF8_MIN_UNITS = 1;

//
// Types
//

struct UTF8
{
    union
    {
        struct
        {
            u8 a, b, c, d;
        };

        u8 memory[UTF8_MAX_UNITS] = {};
    };

    isiz size = 0;
};

//
// Procs
//

/* UTF8 writing */

b32
utf8_encode(UTF8* self, u32 value);

isiz
mem8_write_utf8_forw(u8* memory, isiz length, isiz index, u32 value);

isiz
mem8_write_utf8_back(u8* memory, isiz length, isiz index, u32 value);

/* UTf8 reading */

b32
utf8_decode(UTF8* self, u32* value);

isiz
mem8_read_utf8_forw(u8* memory, isiz length, isiz index, u32* value);

isiz
mem8_read_utf8_back(u8* memory, isiz length, isiz index, u32* value);

/* Utils */

isiz
utf8_units_to_write(u32 value);

isiz
utf8_units_to_read(u8 value);

b32
utf8_is_trailing(u8 value);

b32
utf8_is_overlong(u32 value, isiz units);

} // namespace pax

#endif // PAX_STRING_UTF8_HPP
