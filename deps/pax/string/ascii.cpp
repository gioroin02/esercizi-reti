#ifndef PAX_STRING_ASCII_CPP
#define PAX_STRING_ASCII_CPP

#include "ascii.hpp"

namespace pax {

b32
ascii_is_space(u32 value)
{
    if (value >= 9 && value <= 13)
        return 1;

    if (value == 32) return 1;

    return 0;
}

b32
ascii_is_digit(u32 value, uptr base)
{
    if (value >= 48 && value - 48 < base) return 1;
    if (value >= 97 && value - 87 < base) return 1;
    if (value >= 65 && value - 55 < base) return 1;

    return 0;
}

b32
ascii_is_letter(u32 value)
{
    if (value >= 97 && value <= 122) return 1;
    if (value >= 65 && value <= 90)  return 1;

    return 0;
}

b32
ascii_is_letter_lower(u32 value)
{
    if (value >= 97 && value <= 122)
        return 1;

    return 0;
}

b32
ascii_is_letter_upper(u32 value)
{
    if (value >= 65 && value <= 90)
        return 1;

    return 0;
}

uptr
ascii_digit_index(u32 value, uptr base)
{
    if (value >= 48 && value - 48 < base) return value - 48;
    if (value >= 97 && value - 87 < base) return value - 87;
    if (value >= 65 && value - 55 < base) return value - 55;

    return base;
}

uptr
ascii_letter_index(u32 value)
{
    if (value >= 97 && value <= 122) return value - 97;
    if (value >= 65 && value <= 90)  return value - 65;

    return 26;
}

} // namespace pax

#endif // PAX_STRING_ASCII_CPP
