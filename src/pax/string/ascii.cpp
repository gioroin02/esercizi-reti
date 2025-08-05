#ifndef PAX_STRING_ASCII_CPP
#define PAX_STRING_ASCII_CPP

#include "ascii.hpp"

namespace pax {

b32
ascii_is_space(u32 value)
{
    switch (value) {
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
            return 1;

        default: break;
    }

    return 0;
}

b32
ascii_is_digit(u32 value, usiz radix)
{
    switch (value) {
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
            return radix >= 2 && radix <= 16 && value - 48 < radix;

        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
            return radix >= 11 && radix <= 16 && value - 55 < radix;

        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102:
            return radix >= 11 && radix <= 16 && value - 87 < radix;

        default: break;
    }

    return 0;
}

b32
ascii_is_letter(u32 value)
{
    if (value >= 65 && value <= 90)  return 1;
    if (value >= 97 && value <= 122) return 1;

    return 0;
}

b32
ascii_is_lower(u32 value)
{
    if (value >= 97 && value <= 122)
        return 1;

    return 0;
}

b32
ascii_is_upper(u32 value)
{
    if (value >= 65 && value <= 90)
        return 1;

    return 0;
}

usiz
ascii_index_from_digit(u32 value, usiz radix)
{
    switch (value) {
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57: {
            usiz result = value - 48;

            if (radix >= 2 && radix <= 16 && result < radix)
                return result;
        } break;

        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70: {
            usiz result = value - 55;

            if (radix >= 11 && radix <= 16 && result < radix)
                return result;
        } break;

        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102: {
            usiz result = value - 87;

            if (radix >= 11 && radix <= 16 && result < radix)
                return result;
        } break;

        default: break;
    }

    return radix;
}

usiz
ascii_index_from_letter(u32 value)
{
    if (value >= 65 && value <= 90)  return value - 65;
    if (value >= 97 && value <= 122) return value - 97;

    return 26;
}

usiz
ascii_index_from_lower(u32 value)
{
    if (value >= 97 && value <= 122)
        return value - 97;

    return 26;
}

usiz
ascii_index_from_upper(u32 value)
{
    if (value >= 65 && value <= 90)
        return value - 65;

    return 26;
}

u32
ascii_digit_from_index(usiz value, usiz radix, b32 upper)
{
    u32 digit = value % radix;

    if (digit >= 0 && digit <= 9)
        return digit + ASCII_ZERO;

    if (digit >= 10 && digit <= 15) {
        digit -= 10;

        if (upper != 0)
            return digit + ASCII_UPPER_A;

        return digit + ASCII_LOWER_A;
    }

    return ASCII_NULL;
}

u32
ascii_letter_from_index(usiz value, b32 upper)
{
    if (value >= 0 && value <= 25) {
        if (upper != 0)
            return value + ASCII_UPPER_A;

        return value + ASCII_LOWER_A;
    }

    return ASCII_NULL;
}

u32
ascii_lower_from_index(usiz value)
{
    if (value >= 0 && value <= 25)
        return value + ASCII_LOWER_A;

    return ASCII_NULL;
}

u32
ascii_upper_from_index(usiz value)
{
    if (value >= 0 && value <= 25)
        return value + ASCII_UPPER_A;

    return ASCII_NULL;
}

} // namespace pax

#endif // PAX_STRING_ASCII_CPP
