#ifndef PAX_FORMAT_PARSE_INTEGER_CPP
#define PAX_FORMAT_PARSE_INTEGER_CPP

#include "parse_integer.hpp"

namespace pax {

b32
str8_parse_i64(str8 self, Format_Spec spec, i64* value)
{
    uptr index = 0;
    i64  base  = spec.base;
    i64  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i64 digit = ascii_digit_index(self.memory[index], base);

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
str8_parse_i32(str8 self, Format_Spec spec, i32* value)
{
    uptr index = 0;
    i32  base  = spec.base;
    i32  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i32 digit = ascii_digit_index(self.memory[index], base);

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
str8_parse_i16(str8 self, Format_Spec spec, i16* value)
{
    uptr index = 0;
    i16  base  = spec.base;
    i16  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i16 digit = ascii_digit_index(self.memory[index], base);

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
str8_parse_i8(str8 self, Format_Spec spec, i8* value)
{
    uptr index = 0;
    i8   base  = spec.base;
    i8   temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i8 digit = ascii_digit_index(self.memory[index], base);

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
str16_parse_i64(str16 self, Format_Spec spec, i64* value)
{
    uptr index = 0;
    i64  base  = spec.base;
    i64  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i64 digit = ascii_digit_index(self.memory[index], base);

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
str16_parse_i32(str16 self, Format_Spec spec, i32* value)
{
    uptr index = 0;
    i32  base  = spec.base;
    i32  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i32 digit = ascii_digit_index(self.memory[index], base);

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
str16_parse_i16(str16 self, Format_Spec spec, i16* value)
{
    uptr index = 0;
    i16  base  = spec.base;
    i16  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i16 digit = ascii_digit_index(self.memory[index], base);

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
str16_parse_i8(str16 self, Format_Spec spec, i8* value)
{
    uptr index = 0;
    i8   base  = spec.base;
    i8   temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i8 digit = ascii_digit_index(self.memory[index], base);

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
str32_parse_i64(str32 self, Format_Spec spec, i64* value)
{
    uptr index = 0;
    i64  base  = spec.base;
    i64  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i64 digit = ascii_digit_index(self.memory[index], base);

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
str32_parse_i32(str32 self, Format_Spec spec, i32* value)
{
    uptr index = 0;
    i32  base  = spec.base;
    i32  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i32 digit = ascii_digit_index(self.memory[index], base);

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
str32_parse_i16(str32 self, Format_Spec spec, i16* value)
{
    uptr index = 0;
    i16  base  = spec.base;
    i16  temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i16 digit = ascii_digit_index(self.memory[index], base);

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
str32_parse_i8(str32 self, Format_Spec spec, i8* value)
{
    uptr index = 0;
    i8   base  = spec.base;
    i8   temp  = 0;
    b32  negat = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        i8 digit = ascii_digit_index(self.memory[index], base);

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
buffer_parse_i64(Buffer* self, Format_Spec spec, i64* value)
{
    uptr index = 0;
    i64  base  = spec.base;
    i64  temp  = 0;
    b32  negat = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        i64 digit = ascii_digit_index(self->memory[index], base);

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
buffer_parse_i32(Buffer* self, Format_Spec spec, i32* value)
{
    uptr index = 0;
    i32  base  = spec.base;
    i32  temp  = 0;
    b32  negat = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        i32 digit = ascii_digit_index(self->memory[index], base);

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
buffer_parse_i16(Buffer* self, Format_Spec spec, i16* value)
{
    uptr index = 0;
    i16  base  = spec.base;
    i16  temp  = 0;
    b32  negat = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        i16 digit = ascii_digit_index(self->memory[index], base);

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
buffer_parse_i8(Buffer* self, Format_Spec spec, i8* value)
{
    uptr index = 0;
    i8   base  = spec.base;
    i8   temp  = 0;
    b32  negat = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case ASCII_MINUS: {
            index += 1;
            negat  = 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        i8 digit = ascii_digit_index(self->memory[index], base);

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

#endif // PAX_FORMAT_PARSE_INTEGER_CPP
