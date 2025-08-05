#ifndef PAX_FORMAT_STR16_CPP
#define PAX_FORMAT_STR16_CPP

#include "str16.hpp"

namespace pax {

str16
str16_from_usiz(Arena* arena, Format_Options options, usiz value)
{
    isiz index = 0;
    usiz flags = options.flags;
    usiz radix = options.radix;
    usiz other = value;

    for (usiz temp = other; temp != 0; temp /= radix) index += 1;

    if (value == 0) index += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_u64(Arena* arena, Format_Options options, u64 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u64  radix = options.radix;
    u64  other = value;

    for (u64 temp = other; temp != 0; temp /= radix) index += 1;

    if (value == 0) index += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_u32(Arena* arena, Format_Options options, u32 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u32  radix = options.radix;
    u32  other = value;

    for (u32 temp = other; temp != 0; temp /= radix) index += 1;

    if (value == 0) index += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_u16(Arena* arena, Format_Options options, u16 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u16  radix = options.radix;
    u16  other = value;

    for (u16 temp = other; temp != 0; temp /= radix) index += 1;

    if (value == 0) index += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_u8(Arena* arena, Format_Options options, u8 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u8   radix = options.radix;
    u8   other = value;

    for (u8 temp = other; temp != 0; temp /= radix) index += 1;

    if (value == 0) index += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

b32
usiz_from_str16(str16 self, Format_Options options, usiz* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    usiz radix = options.radix;
    usiz other = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        usiz digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (other > (USIZ_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
    }

    if (value != 0) *value = other;

    return 1;
}

b32
u64_from_str16(str16 self, Format_Options options, u64* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u64  radix = options.radix;
    u64  other = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (other > (U64_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
    }

    if (value != 0) *value = other;

    return 1;
}

b32
u32_from_str16(str16 self, Format_Options options, u32* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u32  radix = options.radix;
    u32  other = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (other > (U32_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
    }

    if (value != 0) *value = other;

    return 1;
}

b32
u16_from_str16(str16 self, Format_Options options, u16* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u16  radix = options.radix;
    u16  other = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (other > (U16_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
    }

    if (value != 0) *value = other;

    return 1;
}

b32
u8_from_str16(str16 self, Format_Options options, u8* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u8   radix = options.radix;
    u8   other = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        if (other > (U8_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
    }

    if (value != 0) *value = other;

    return 1;
}

str16
str16_from_isiz(Arena* arena, Format_Options options, isiz value)
{
    isiz index = 0;
    usiz flags = options.flags;
    usiz radix = options.radix;
    usiz other = abs_isiz(value);
    b32  sign  = sign_isiz(value);

    for (usiz temp = other; temp != 0; temp /= radix) index += 1;

    if (sign != 0 || value == 0) index += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) result.memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_i64(Arena* arena, Format_Options options, i64 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u64  radix = options.radix;
    u64  other = abs_i64(value);
    b32  sign  = sign_i64(value);

    for (u64 temp = other; temp != 0; temp /= radix) index += 1;

    if (sign != 0 || value == 0) index += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) result.memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_i32(Arena* arena, Format_Options options, i32 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u32  radix = options.radix;
    u32  other = abs_i32(value);
    b32  sign  = sign_i32(value);

    for (u32 temp = other; temp != 0; temp /= radix) index += 1;

    if (sign != 0 || value == 0) index += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) result.memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_i16(Arena* arena, Format_Options options, i16 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u16  radix = options.radix;
    u16  other = abs_i16(value);
    b32  sign  = sign_i16(value);

    for (u16 temp = other; temp != 0; temp /= radix) index += 1;

    if (sign != 0 || value == 0) index += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) result.memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

str16
str16_from_i8(Arena* arena, Format_Options options, i8 value)
{
    isiz index = 0;
    usiz flags = options.flags;
    u8   radix = options.radix;
    u8   other = abs_i8(value);
    b32  sign  = sign_i8(value);

    for (u8 temp = other; temp != 0; temp /= radix) index += 1;

    if (sign != 0 || value == 0) index += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    isiz  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index -= 1;
        other /= radix;

        if (ascii != ASCII_NULL)
            result.memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) result.memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[index] = ASCII_PLUS;

    if (index == 0) return result;

    arena_rewind(arena, offset);

    return {};
}

b32
isiz_from_str16(str16 self, Format_Options options, isiz* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    isiz radix = options.radix;
    isiz other = 0;
    b32  sign  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        isiz digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (other > (ISIZ_MAX - digit) / radix)
                    return 0;

                other = other * radix + digit;
            } break;

            case 1: {
                if (other < (ISIZ_MIN + digit) / radix)
                    return 0;

                other = other * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (value != 0) *value = other;

    return 1;
}

b32
i64_from_str16(str16 self, Format_Options options, i64* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    i64  radix = options.radix;
    i64  other = 0;
    b32  sign  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i64 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (other > (I64_MAX - digit) / radix)
                    return 0;

                other = other * radix + digit;
            } break;

            case 1: {
                if (other < (I64_MIN + digit) / radix)
                    return 0;

                other = other * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (value != 0) *value = other;

    return 1;
}

b32
i32_from_str16(str16 self, Format_Options options, i32* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    i32  radix = options.radix;
    i32  other = 0;
    b32  sign  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            sign  = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i32 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (other > (I32_MAX - digit) / radix)
                    return 0;

                other = other * radix + digit;
            } break;

            case 1: {
                if (other < (I32_MIN + digit) / radix)
                    return 0;

                other = other * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (value != 0) *value = other;

    return 1;
}

b32
i16_from_str16(str16 self, Format_Options options, i16* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    i16  radix = options.radix;
    i16  other = 0;
    b32  sign  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            sign  = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i16 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (other > (I16_MAX - digit) / radix)
                    return 0;

                other = other * radix + digit;
            } break;

            case 1: {
                if (other < (I16_MIN + digit) / radix)
                    return 0;

                other = other * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (value != 0) *value = other;

    return 1;
}

b32
i8_from_str16(str16 self, Format_Options options, i8* value)
{
    isiz index = 0;
    usiz flags = options.flags;
    i8   radix = options.radix;
    i8   other = 0;
    b32  sign  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            sign  = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self.memory[index];

        if (self.length > index + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i8 digit = ascii_index_from_digit(self.memory[index], radix);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (other > (I8_MAX - digit) / radix)
                    return 0;

                other = other * radix + digit;
            } break;

            case 1: {
                if (other < (I8_MIN + digit) / radix)
                    return 0;

                other = other * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (value != 0) *value = other;

    return 1;
}

} // namespace pax

#endif // PAX_FORMAT_STR16_CPP
