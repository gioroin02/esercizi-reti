#ifndef PAX_STRING_UTF16_HPP
#define PAX_STRING_UTF16_HPP

#include "unicode.hpp"

namespace pax {

//
// Values
//

static const isiz UTF16_MAX_UNITS = 2;
static const isiz UTF16_MIN_UNITS = 1;

//
// Types
//

struct UTF16
{
    union
    {
        struct
        {
            u16 a, b;
        };

        u16 memory[UTF16_MAX_UNITS] = {};
    };

    isiz size = 0;
};

//
// Procs
//

/* UTF16 writing */

b32
utf16_encode(UTF16* self, u32 value);

isiz
mem16_write_utf16_forw(u16* memory, isiz length, isiz index, u32 value);

isiz
mem16_write_utf16_back(u16* memory, isiz length, isiz index, u32 value);

/* UTF16 reading */

b32
utf16_decode(UTF16* self, u32* value);

isiz
mem16_read_utf16_forw(u16* memory, isiz length, isiz index, u32* value);

isiz
mem16_read_utf16_back(u16* memory, isiz length, isiz index, u32* value);

/* Utils */

isiz
utf16_units_to_write(u32 value);

isiz
utf16_units_to_read(u16 value);

} // namespace pax

#endif // PAX_STRING_UTF16_HPP
