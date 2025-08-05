#ifndef PAX_STRING_UTF32_HPP
#define PAX_STRING_UTF32_HPP

#include "unicode.hpp"

namespace pax {

//
// Values
//

static const isiz UTF32_MAX_UNITS = 1;
static const isiz UTF32_MIN_UNITS = 1;

//
// Types
//

struct UTF32
{
    union
    {
        struct
        {
            u32 a;
        };

        u32 memory[UTF32_MAX_UNITS] = {};
    };

    isiz size = 0;
};

//
// Procs
//

/* UTF32 writing */

b32
utf32_encode(UTF32* self, u32 value);

isiz
mem32_write_utf32_forw(u32* memory, isiz length, isiz index, u32 value);

isiz
mem32_write_utf32_back(u32* memory, isiz length, isiz index, u32 value);

/* UTF32 reading */

b32
utf32_decode(UTF32* self, u32* value);

isiz
mem32_read_utf32_forw(u32* memory, isiz length, isiz index, u32* value);

isiz
mem32_read_utf32_back(u32* memory, isiz length, isiz index, u32* value);

/* Utils */

isiz
utf32_units_to_write(u32 value);

isiz
utf32_units_to_read(u32 value);

} // namespace pax

#endif // PAX_STRING_UTF32_HPP
