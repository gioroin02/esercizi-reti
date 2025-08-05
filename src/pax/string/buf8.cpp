#ifndef PAX_STRING_BUF8_CPP
#define PAX_STRING_BUF8_CPP

#include "buf8.hpp"

namespace pax {

isiz
buf8_write_utf8_head(buf8* self, u32 value)
{
    UTF8 utf8 = {};

    if (utf8_encode(&utf8, value) == 0) return 0;

    if (self->size < 0 || self->size + utf8.size > self->length)
        return 0;

    isiz prev = self->head + self->length - utf8.size;

    self->size += utf8.size;
    self->head  = prev % self->length;

    for (isiz i = 0; i < utf8.size; i += 1)
        self->memory[(self->head + i) % self->length] = utf8.memory[i];

    return utf8.size;
}

isiz
buf8_write_str8_head(buf8* self, str8 value)
{
    isiz size = value.length;
    isiz prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0; i < size; i += 1)
        self->memory[(self->head + i) % self->length] = value.memory[i];

    return size;
}

isiz
buf8_write_str16_head(buf8* self, str16 value)
{
    isiz size = utf8_units_from_str16(value);
    isiz prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0, j = 0; j < size;) {
        UTF8 utf8    = {};
        u32  unicode = 0;

        i += str16_read_utf16_forw(value, i, &unicode);

        utf8_encode(&utf8, unicode);

        for (isiz k = 0; k < utf8.size; k += 1)
            self->memory[(self->head + j + k) % self->length] = utf8.memory[k];

        j += utf8.size;
    }

    return size;
}

isiz
buf8_write_str32_head(buf8* self, str32 value)
{
    isiz size = utf8_units_from_str32(value);
    isiz prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0, j = 0; j < size;) {
        UTF8 utf8    = {};
        u32  unicode = 0;

        i += str32_read_utf32_forw(value, i, &unicode);

        utf8_encode(&utf8, unicode);

        for (isiz k = 0; k < utf8.size; k += 1)
            self->memory[(self->head + j + k) % self->length] = utf8.memory[k];

        j += utf8.size;
    }

    return size;
}

isiz
buf8_write_utf8_tail(buf8* self, u32 value)
{
    UTF8 utf8 = {};

    if (utf8_encode(&utf8, value) == 0) return 0;

    if (self->size < 0 || self->size + utf8.size > self->length)
        return 0;

    isiz next = self->tail + utf8.size;

    for (isiz i = 0; i < utf8.size; i += 1)
        self->memory[(self->tail + i) % self->length] = utf8.memory[i];

    self->size += utf8.size;
    self->tail  = next % self->length;

    return utf8.size;
}

isiz
buf8_write_str8_tail(buf8* self, str8 value)
{
    isiz size = value.length;
    isiz next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (isiz i = 0; i < size; i += 1)
        self->memory[(self->tail + i) % self->length] = value.memory[i];

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

isiz
buf8_write_str16_tail(buf8* self, str16 value)
{
    isiz size = utf8_units_from_str16(value);
    isiz next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (isiz i = 0, j = 0; j < size;) {
        UTF8 utf8    = {};
        u32  unicode = 0;

        i += str16_read_utf16_forw(value, i, &unicode);

        utf8_encode(&utf8, unicode);

        for (isiz k = 0; k < utf8.size; k += 1)
            self->memory[(self->tail + j + k) % self->length] = utf8.memory[k];

        j += utf8.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

isiz
buf8_write_str32_tail(buf8* self, str32 value)
{
    isiz size = utf8_units_from_str32(value);
    isiz next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (isiz i = 0, j = 0; j < size;) {
        UTF8 utf8    = {};
        u32  unicode = 0;

        i += str32_read_utf32_forw(value, i, &unicode);

        utf8_encode(&utf8, unicode);

        for (isiz k = 0; k < utf8.size; k += 1)
            self->memory[(self->tail + j + k) % self->length] = utf8.memory[k];

        j += utf8.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

isiz
buf8_read_utf8_head(buf8* self, u32* value)
{
    UTF8 utf8 = {};

    if (self->size > 0 && self->size <= self->length)
        utf8.size = utf8_units_to_read(self->memory[self->head]);

    if (utf8.size <= 0 || utf8.size > self->size)
        return 0;

    for (isiz i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = self->memory[(self->head + i) % self->length];

    if (utf8_decode(&utf8, value) == 0) return 0;

    isiz next = self->head + utf8.size;

    self->size -= utf8.size;
    self->head  = next % self->length;

    return utf8.size;
}

isiz
buf8_read_utf8_tail(buf8* self, u32* value)
{
    UTF8 utf8  = {};
    isiz index = (self->tail + self->length - 1) % self->length;
    isiz count = 0;

    for (; count < 4; count += 1) {
        if (utf8_is_trailing(self->memory[index]) == 0)
            break;

        index = (index + self->length - 1) % self->length;
    }

    utf8.size = count + 1;

    if (utf8.size != utf8_units_to_read(self->memory[index]))
        return 0;

    isiz prev = self->tail + self->length - utf8.size;

    for (isiz i = 0; i < utf8.size; i += 1)
        utf8.memory[i] = self->memory[(prev + i) % self->length];

    if (utf8_decode(&utf8, value) == 0) return 0;

    self->size -= utf8.size;
    self->tail  = prev % self->length;

    return utf8.size;
}

str8
buf8_read_str8_head(buf8* self, Arena* arena, isiz length)
{
    isiz size = pax_limit(self->size, 0, length);
    isiz next = self->head + size;

    str8 result = str8_reserve(arena, size);

    if (result.length <= 0) return result;

    for (isiz i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return result;
}

str8
buf8_read_str8_tail(buf8* self, Arena* arena, isiz length)
{
    isiz size = pax_limit(self->size, 0, length);
    isiz prev = self->tail + self->length - size;

    str8 result = str8_reserve(arena, size);

    if (result.length <= 0) return result;

    self->size -= size;
    self->tail  = prev % self->length;

    for (isiz i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->tail + i) % self->length];

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUF8_CPP
