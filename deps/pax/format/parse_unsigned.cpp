#ifndef PAX_FORMAT_PARSE_UNSIGNED_CPP
#define PAX_FORMAT_PARSE_UNSIGNED_CPP

#include "parse_unsigned.hpp"

namespace pax {

b32
str8_parse_u64(str8 self, Format_Spec spec, u64* value)
{
    uptr index = 0;
    u64  base  = spec.base;
    u64  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = ascii_digit_index(self.memory[index], base);

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
str8_parse_u32(str8 self, Format_Spec spec, u32* value)
{
    uptr index = 0;
    u32  base  = spec.base;
    u32  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = ascii_digit_index(self.memory[index], base);

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
str8_parse_u16(str8 self, Format_Spec spec, u16* value)
{
    uptr index = 0;
    u16  base  = spec.base;
    u16  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = ascii_digit_index(self.memory[index], base);

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
str8_parse_u8(str8 self, Format_Spec spec, u8* value)
{
    uptr index = 0;
    u8   base  = spec.base;
    u8   temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = ascii_digit_index(self.memory[index], base);

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

b32
str16_parse_u64(str16 self, Format_Spec spec, u64* value)
{
    uptr index = 0;
    u64  base  = spec.base;
    u64  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = ascii_digit_index(self.memory[index], base);

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
str16_parse_u32(str16 self, Format_Spec spec, u32* value)
{
    uptr index = 0;
    u32  base  = spec.base;
    u32  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = ascii_digit_index(self.memory[index], base);

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
str16_parse_u16(str16 self, Format_Spec spec, u16* value)
{
    uptr index = 0;
    u16  base  = spec.base;
    u16  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = ascii_digit_index(self.memory[index], base);

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
str16_parse_u8(str16 self, Format_Spec spec, u8* value)
{
    uptr index = 0;
    u8   base  = spec.base;
    u8   temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = ascii_digit_index(self.memory[index], base);

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

b32
str32_parse_u64(str32 self, Format_Spec spec, u64* value)
{
    uptr index = 0;
    u64  base  = spec.base;
    u64  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u64 digit = ascii_digit_index(self.memory[index], base);

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
str32_parse_u32(str32 self, Format_Spec spec, u32* value)
{
    uptr index = 0;
    u32  base  = spec.base;
    u32  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u32 digit = ascii_digit_index(self.memory[index], base);

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
str32_parse_u16(str32 self, Format_Spec spec, u16* value)
{
    uptr index = 0;
    u16  base  = spec.base;
    u16  temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u16 digit = ascii_digit_index(self.memory[index], base);

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
str32_parse_u8(str32 self, Format_Spec spec, u8* value)
{
    uptr index = 0;
    u8   base  = spec.base;
    u8   temp  = 0;

    if (self.length < 1) return 0;

    switch (self.memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self.length > 1 && self.memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self.length; index += 1) {
        u8 digit = ascii_digit_index(self.memory[index], base);

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

b32
buffer_parse_u64(Buffer* self, Format_Spec spec, u64* value)
{
    uptr index = 0;
    u64  base  = spec.base;
    u64  temp  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        u64 digit = ascii_digit_index(self->memory[index], base);

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
buffer_parse_u32(Buffer* self, Format_Spec spec, u32* value)
{
    uptr index = 0;
    u32  base  = spec.base;
    u32  temp  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        u32 digit = ascii_digit_index(self->memory[index], base);

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
buffer_parse_u16(Buffer* self, Format_Spec spec, u16* value)
{
    uptr index = 0;
    u16  base  = spec.base;
    u16  temp  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        u16 digit = ascii_digit_index(self->memory[index], base);

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
buffer_parse_u8(Buffer* self, Format_Spec spec, u8* value)
{
    uptr index = 0;
    u8   base  = spec.base;
    u8   temp  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((spec.flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((spec.flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        if (self->size > 1 && self->memory[0] == ASCII_ZERO)
            return 0;
    }

    for (; index < self->size; index += 1) {
        u8 digit = ascii_digit_index(self->memory[index], base);

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

} // namespace pax

#endif // PAX_FORMAT_PARSE_UNSIGNED_CPP
