#ifndef PAX_FORMAT_STR8_CPP
#define PAX_FORMAT_STR8_CPP

#include "str8.hpp"

namespace pax {

str8
str8_from_uptr(Arena* arena, Format_Options opts, uptr value)
{
    uptr size = 0;
    uptr base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (uptr temp = value; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u64(Arena* arena, Format_Options opts, u64 value)
{
    uptr size = 0;
    u64  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u64 temp = value; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u32(Arena* arena, Format_Options opts, u32 value)
{
    uptr size = 0;
    u32  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u32 temp = value; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u16(Arena* arena, Format_Options opts, u16 value)
{
    uptr size = 0;
    u16  base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u16 temp = value; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_u8(Arena* arena, Format_Options opts, u8 value)
{
    uptr size = 0;
    u8   base = opts.base;

    if (value == 0) size = 1;

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u8 temp = value; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(value, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        value /= base;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

b32
uptr_from_str8(str8 self, Format_Options opts, uptr* value)
{
    uptr index = 0;
    uptr base  = opts.base;
    uptr temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        uptr digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (UPTR_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u64_from_str8(str8 self, Format_Options opts, u64* value)
{
    uptr index = 0;
    u64  base  = opts.base;
    u64  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U64_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u32_from_str8(str8 self, Format_Options opts, u32* value)
{
    uptr index = 0;
    u32  base  = opts.base;
    u32  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U32_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u16_from_str8(str8 self, Format_Options opts, u16* value)
{
    uptr index = 0;
    u16  base  = opts.base;
    u16  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U16_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
u8_from_str8(str8 self, Format_Options opts, u8* value)
{
    uptr index = 0;
    u8   base  = opts.base;
    u8   temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            if (temp > (U8_MAX - digit) / base)
                return 0;

            temp = temp * base + digit;
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

str8
str8_from_iptr(Arena* arena, Format_Options opts, iptr value)
{
    uptr size  = 0;
    uptr base  = opts.base;
    uptr other = pax_cast(uptr, value);
    b32  negat = 0;

    if (value < 0) {
        other = pax_cast(uptr, ~value) + 1;
        negat = 1;
    }

    if (negat != 0 || value == 0) size = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (uptr temp = other; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        other /= base;
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i64(Arena* arena, Format_Options opts, i64 value)
{
    uptr size  = 0;
    u64  base  = opts.base;
    u64  other = pax_cast(u64, value);
    b32  negat = 0;

    if (value < 0) {
        other = pax_cast(u64, ~value) + 1;
        negat = 1;
    }

    if (negat != 0 || value == 0) size = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u64 temp = other; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        other /= base;
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i32(Arena* arena, Format_Options opts, i32 value)
{
    uptr size  = 0;
    u32  base  = opts.base;
    u32  other = pax_cast(u32, value);
    b32  negat = 0;

    if (value < 0) {
        other = pax_cast(u32, ~value) + 1;
        negat = 1;
    }

    if (negat != 0 || value == 0) size = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u32 temp = other; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        other /= base;
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i16(Arena* arena, Format_Options opts, i16 value)
{
    uptr size  = 0;
    u16  base  = opts.base;
    u16  other = pax_cast(u16, value);
    b32  negat = 0;

    if (value < 0) {
        other = pax_cast(u16, ~value) + 1;
        negat = 1;
    }

    if (negat != 0 || value == 0) size = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u16 temp = other; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        other /= base;
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i8(Arena* arena, Format_Options opts, i8 value)
{
    uptr size  = 0;
    u8   base  = opts.base;
    u8   other = pax_cast(u8, value);
    b32  negat = 0;

    if (value < 0) {
        other = pax_cast(u8, ~value) + 1;
        negat = 1;
    }

    if (negat != 0 || value == 0) size = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    for (u8 temp = other; temp != 0; temp /= base) size += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, size);

    for (uptr i = size; i > 0; i -= 1) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL)
            result.memory[i - 1] = pax_cast(u8, ascii);
        else
            break;

        other /= base;
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

b32
iptr_from_str8(str8 self, Format_Options opts, iptr* value)
{
    uptr index = 0;
    iptr base  = opts.base;
    iptr temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        iptr digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            switch (negat) {
                case 1: {
                    if (temp < (IPTR_MIN + digit) / base)
                        return 0;

                    temp = temp * base - digit;
                } break;

                case 0: {
                    if (temp > (IPTR_MAX - digit) / base)
                        return 0;

                    temp = temp * base + digit;
                } break;

                default: return 0;
            }
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
i64_from_str8(str8 self, Format_Options opts, i64* value)
{
    uptr index = 0;
    i64  base  = opts.base;
    i64  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i64 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            switch (negat) {
                case 1: {
                    if (temp < (I64_MIN + digit) / base)
                        return 0;

                    temp = temp * base - digit;
                } break;

                case 0: {
                    if (temp > (I64_MAX - digit) / base)
                        return 0;

                    temp = temp * base + digit;
                } break;

                default: return 0;
            }
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
i32_from_str8(str8 self, Format_Options opts, i32* value)
{
    uptr index = 0;
    i32  base  = opts.base;
    i32  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i32 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            switch (negat) {
                case 1: {
                    if (temp < (I32_MIN + digit) / base)
                        return 0;

                    temp = temp * base - digit;
                } break;

                case 0: {
                    if (temp > (I32_MAX - digit) / base)
                        return 0;

                    temp = temp * base + digit;
                } break;

                default: return 0;
            }
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
i16_from_str8(str8 self, Format_Options opts, i16* value)
{
    uptr index = 0;
    i16  base  = opts.base;
    i16  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i16 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            switch (negat) {
                case 1: {
                    if (temp < (I16_MIN + digit) / base)
                        return 0;

                    temp = temp * base - digit;
                } break;

                case 0: {
                    if (temp > (I16_MAX - digit) / base)
                        return 0;

                    temp = temp * base + digit;
                } break;

                default: return 0;
            }
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

b32
i8_from_str8(str8 self, Format_Options opts, i8* value)
{
    uptr index = 0;
    i8   base  = opts.base;
    i8   temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((opts.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((opts.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > index + 1 && self.memory[index] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i8 digit = digit_from_ascii(self.memory[index], base);

        if (digit >= 0 && digit < base) {
            switch (negat) {
                case 1: {
                    if (temp < (I8_MIN + digit) / base)
                        return 0;

                    temp = temp * base - digit;
                } break;

                case 0: {
                    if (temp > (I8_MAX - digit) / base)
                        return 0;

                    temp = temp * base + digit;
                } break;

                default: return 0;
            }
        } else
            return 0;
    }

    *value = temp;

    return 1;
}

} // namespace pax

#endif // PAX_FORMAT_STR8_CPP
