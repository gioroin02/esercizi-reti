#ifndef PAX_FORMAT_BUF16_CPP
#define PAX_FORMAT_BUF16_CPP

#include "buf16.hpp"

namespace pax {

b32
buf16_write_usiz_tail(buf16* self, Format_Options options, usiz value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    usiz radix = options.radix;
    usiz other = value;

    for (usiz temp = other; temp != 0; temp /= radix) size += 1;

    if (value == 0) size += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_u64_tail(buf16* self, Format_Options options, u64 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u64  radix = options.radix;
    u64  other = value;

    for (u64 temp = other; temp != 0; temp /= radix) size += 1;

    if (value == 0) size += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_u32_tail(buf16* self, Format_Options options, u32 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u32  radix = options.radix;
    u32  other = value;

    for (u32 temp = other; temp != 0; temp /= radix) size += 1;

    if (value == 0) size += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_u16_tail(buf16* self, Format_Options options, u16 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u16  radix = options.radix;
    u16  other = value;

    for (u16 temp = other; temp != 0; temp /= radix) size += 1;

    if (value == 0) size += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_u8_tail(buf16* self, Format_Options options, u8 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u8   radix = options.radix;
    u8   other = value;

    for (u8 temp = other; temp != 0; temp /= radix) size += 1;

    if (value == 0) size += 1;

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0) size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if ((flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_read_usiz_head(buf16* self, Format_Options options, usiz* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    usiz radix = options.radix;
    usiz other = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        usiz digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

        if (other > (USIZ_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_u64_head(buf16* self, Format_Options options, u64* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    u64  radix = options.radix;
    u64  other = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        u64 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

        if (other > (U64_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_u32_head(buf16* self, Format_Options options, u32* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    u32  radix = options.radix;
    u32  other = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        u32 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

        if (other > (U32_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_u16_head(buf16* self, Format_Options options, u16* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    u16  radix = options.radix;
    u16  other = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        u16 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

        if (other > (U16_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_u8_head(buf16* self, Format_Options options, u8* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    u8   radix = options.radix;
    u8   other = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        u8 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

        if (other > (U8_MAX - digit) / radix)
            return 0;

        other = other * radix + digit;
        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_write_isiz_tail(buf16* self, Format_Options options, isiz value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    usiz radix = options.radix;
    usiz other = abs_isiz(value);
    b32  sign  = sign_isiz(value);

    for (usiz temp = other; temp != 0; temp /= radix) size += 1;

    if (sign != 0 || value == 0) size += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) self->memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_i64_tail(buf16* self, Format_Options options, i64 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u64  radix = options.radix;
    u64  other = abs_i64(value);
    b32  sign  = sign_i64(value);

    for (u64 temp = other; temp != 0; temp /= radix) size += 1;

    if (sign != 0 || value == 0) size += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) self->memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_i32_tail(buf16* self, Format_Options options, i32 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u32  radix = options.radix;
    u32  other = abs_i32(value);
    b32  sign  = sign_i32(value);

    for (u32 temp = other; temp != 0; temp /= radix) size += 1;

    if (sign != 0 || value == 0) size += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) self->memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_i16_tail(buf16* self, Format_Options options, i16 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u16  radix = options.radix;
    u16  other = abs_i16(value);
    b32  sign  = sign_i16(value);

    for (u16 temp = other; temp != 0; temp /= radix) size += 1;

    if (sign != 0 || value == 0) size += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) self->memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_write_i8_tail(buf16* self, Format_Options options, i8 value)
{
    isiz size  = 0;
    usiz flags = options.flags;
    u8   radix = options.radix;
    u8   other = abs_i8(value);
    b32  sign  = sign_i8(value);

    for (u8 temp = other; temp != 0; temp /= radix) size += 1;

    if (sign != 0 || value == 0) size += 1;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        size += 1;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    isiz next  = self->tail + size;
    isiz index = next % self->length;

    while (index != self->tail) {
        u32 ascii = ascii_digit_from_index(other, radix, 0);

        index  = (index + self->length - 1) % self->length;
        other /= radix;

        if (ascii != ASCII_NULL)
            self->memory[index] = ascii;
        else
            break;
    }

    if (sign != 0) self->memory[index] = ASCII_MINUS;

    if (sign == 0 && (flags & FORMAT_FLAG_LEADING_PLUS) != 0)
        self->memory[index] = ASCII_PLUS;

    self->size += size;
    self->tail  = next % self->length;

    return 1;
}

b32
buf16_read_isiz_head(buf16* self, Format_Options options, isiz* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    isiz radix = options.radix;
    isiz other = 0;
    b32  sign  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        case ASCII_MINUS: {
            index  = (index + 1) % self->length;
            size  += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        isiz digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

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

        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_i64_head(buf16* self, Format_Options options, i64* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    i64  radix = options.radix;
    i64  other = 0;
    b32  sign  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        case ASCII_MINUS: {
            index  = (index + 1) % self->length;
            size  += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        i64 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

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

        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_i32_head(buf16* self, Format_Options options, i32* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    i32  radix = options.radix;
    i32  other = 0;
    b32  sign  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        case ASCII_MINUS: {
            index  = (index + 1) % self->length;
            size  += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        i32 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

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

        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_i16_head(buf16* self, Format_Options options, i16* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    i16  radix = options.radix;
    i16  other = 0;
    b32  sign  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        case ASCII_MINUS: {
            index  = (index + 1) % self->length;
            size  += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        i16 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

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

        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

b32
buf16_read_i8_head(buf16* self, Format_Options options, i8* value)
{
    isiz size  = 0;
    isiz index = self->head;
    usiz flags = options.flags;
    i8   radix = options.radix;
    i8   other = 0;
    b32  sign  = 0;

    if (self->size < 1) return 0;

    switch (self->memory[index]) {
        case ASCII_PLUS: {
            if ((flags & FORMAT_FLAG_LEADING_PLUS) == 0)
                return 0;

            index  = (index + 1) % self->length;
            size  += 1;
        } break;

        case ASCII_MINUS: {
            index  = (index + 1) % self->length;
            size  += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((flags & FORMAT_FLAG_LEADING_ZERO) == 0) {
        u32 ascii = self->memory[index];

        if (self->size > size + 1 && ascii == ASCII_ZERO)
            return 0;
    }

    for (; size < self->size; size += 1) {
        i8 digit = ascii_index_from_digit(self->memory[index], radix);

        if (digit < 0 || digit >= radix) break;

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

        index = (index + 1) % self->length;
    }

    if (size <= 0) return 0;

    isiz next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    if (value != 0) *value = other;

    return 1;
}

} // namespace pax

#endif // PAX_FORMAT_BUF16_CPP
