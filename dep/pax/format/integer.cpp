#ifndef PAX_FORMAT_INTEGER_CPP
#define PAX_FORMAT_INTEGER_CPP

#include "integer.hpp"

namespace pax {

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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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

b32
iptr_from_str16(str16 self, Format_Options opts, iptr* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i64_from_str16(str16 self, Format_Options opts, i64* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i32_from_str16(str16 self, Format_Options opts, i32* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i16_from_str16(str16 self, Format_Options opts, i16* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i8_from_str16(str16 self, Format_Options opts, i8* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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

b32
iptr_from_str32(str32 self, Format_Options opts, iptr* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i64_from_str32(str32 self, Format_Options opts, i64* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i32_from_str32(str32 self, Format_Options opts, i32* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i16_from_str32(str32 self, Format_Options opts, i16* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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
i8_from_str32(str32 self, Format_Options opts, i8* value)
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
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
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

b32
iptr_from_buffer(Buffer self, Format_Options opts, iptr* value)
{
    return iptr_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
i64_from_buffer(Buffer self, Format_Options opts, i64* value)
{
    return i64_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
i32_from_buffer(Buffer self, Format_Options opts, i32* value)
{
    return i32_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
i16_from_buffer(Buffer self, Format_Options opts, i16* value)
{
    return i16_from_str8(str8_make(self.memory, self.size), opts, value);
}

b32
i8_from_buffer(Buffer self, Format_Options opts, i8* value)
{
    return i8_from_str8(str8_make(self.memory, self.size), opts, value);
}

str8
str8_from_iptr(Arena* arena, Format_Options opts, iptr value)
{
    uptr index = 0;
    uptr base  = opts.base;
    uptr other = pax_cast(uptr, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(uptr, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (uptr temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u8, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i64(Arena* arena, Format_Options opts, i64 value)
{
    uptr index = 0;
    u64  base  = opts.base;
    u64  other = pax_cast(u64, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u64, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u64 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u8, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i32(Arena* arena, Format_Options opts, i32 value)
{
    uptr index = 0;
    u32  base  = opts.base;
    u32  other = pax_cast(u32, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u32, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u32 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u8, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i16(Arena* arena, Format_Options opts, i16 value)
{
    uptr index = 0;
    u16  base  = opts.base;
    u16  other = pax_cast(u16, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u16, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u16 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u8, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str8
str8_from_i8(Arena* arena, Format_Options opts, i8 value)
{
    uptr index = 0;
    u8   base  = opts.base;
    u8   other = pax_cast(u8, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u8, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u8 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr offset = arena_offset(arena);
    str8 result = str8_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u8, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_iptr(Arena* arena, Format_Options opts, iptr value)
{
    uptr index = 0;
    uptr base  = opts.base;
    uptr other = pax_cast(uptr, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(uptr, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (uptr temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u16, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_i64(Arena* arena, Format_Options opts, i64 value)
{
    uptr index = 0;
    u64  base  = opts.base;
    u64  other = pax_cast(u64, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u64, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u64 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u16, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_i32(Arena* arena, Format_Options opts, i32 value)
{
    uptr index = 0;
    u32  base  = opts.base;
    u32  other = pax_cast(u32, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u32, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u32 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u16, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_i16(Arena* arena, Format_Options opts, i16 value)
{
    uptr index = 0;
    u16  base  = opts.base;
    u16  other = pax_cast(u16, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u16, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u16 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u16, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str16
str16_from_i8(Arena* arena, Format_Options opts, i8 value)
{
    uptr index = 0;
    u8   base  = opts.base;
    u8   other = pax_cast(u8, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u8, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u8 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str16 result = str16_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = pax_cast(u16, ascii);
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_iptr(Arena* arena, Format_Options opts, iptr value)
{
    uptr index = 0;
    uptr base  = opts.base;
    uptr other = pax_cast(uptr, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(uptr, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (uptr temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = ascii;
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_i64(Arena* arena, Format_Options opts, i64 value)
{
    uptr index = 0;
    u64  base  = opts.base;
    u64  other = pax_cast(u64, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u64, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u64 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = ascii;
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_i32(Arena* arena, Format_Options opts, i32 value)
{
    uptr index = 0;
    u32  base  = opts.base;
    u32  other = pax_cast(u32, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u32, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u32 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = ascii;
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_i16(Arena* arena, Format_Options opts, i16 value)
{
    uptr index = 0;
    u16  base  = opts.base;
    u16  other = pax_cast(u16, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u16, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u16 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = ascii;
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

str32
str32_from_i8(Arena* arena, Format_Options opts, i8 value)
{
    uptr index = 0;
    u8   base  = opts.base;
    u8   other = pax_cast(u8, value);
    b32  negat = 0;

    if (value < 0) {
        other  = pax_cast(u8, ~value + 1);
        negat  = 1;
        index += 1;
    }

    for (u8 temp = other; temp != 0; temp /= base)
        index += 1;

    if (value == 0) index = 1;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        index += 1;

    uptr  offset = arena_offset(arena);
    str32 result = str32_reserve(arena, index);

    while (index > 0) {
        u32 ascii = ascii_from_digit(other, base);

        if (ascii != ASCII_NULL) {
            other /= base;
            index -= 1;

            result.memory[index] = ascii;
        } else {
            arena_rewind(arena, offset);

            return {};
        }
    }

    if (negat != 0) result.memory[0] = ASCII_MINUS;

    if (negat == 0 && (opts.flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        result.memory[0] = ASCII_PLUS;

    return result;
}

} // namespace pax

#endif // PAX_FORMAT_INTEGER_CPP
