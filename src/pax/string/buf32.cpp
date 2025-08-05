#ifndef PAX_STRING_BUF32_CPP
#define PAX_STRING_BUF32_CPP

#include "buf32.hpp"

namespace pax {

isiz
buf32_write_utf32_head(buf32* self, u32 value)
{
    UTF32 utf32 = {};

    if (utf32_encode(&utf32, value) == 0) return 0;

    if (self->size < 0 || self->size + utf32.size > self->length)
        return 0;

    isiz prev = self->head + self->length - utf32.size;

    self->size += utf32.size;
    self->head  = prev % self->length;

    for (isiz i = 0; i < utf32.size; i += 1)
        self->memory[(self->head + i) % self->length] = utf32.memory[i];

    return utf32.size;
}

isiz
buf32_write_str8_head(buf32* self, str8 value)
{
    isiz size = utf32_units_from_str8(value);
    isiz prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0, j = 0; j < size;) {
        UTF32 utf32   = {};
        u32   unicode = 0;

        i += str8_read_utf8_forw(value, i, &unicode);

        utf32_encode(&utf32, unicode);

        for (isiz k = 0; k < utf32.size; k += 1)
            self->memory[(self->head + j + k) % self->length] = utf32.memory[k];

        j += utf32.size;
    }

    return size;
}

isiz
buf32_write_str16_head(buf32* self, str16 value)
{
    isiz size = utf32_units_from_str16(value);
    isiz prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0, j = 0; j < size;) {
        UTF32 utf32   = {};
        u32   unicode = 0;

        i += str16_read_utf16_forw(value, i, &unicode);

        utf32_encode(&utf32, unicode);

        for (isiz k = 0; k < utf32.size; k += 1)
            self->memory[(self->head + j + k) % self->length] = utf32.memory[k];

        j += utf32.size;
    }

    return size;
}

isiz
buf32_write_str32_head(buf32* self, str32 value)
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
buf32_write_utf32_tail(buf32* self, u32 value)
{
    UTF32 utf32 = {};

    if (utf32_encode(&utf32, value) == 0) return 0;

    if (self->size < 0 || self->size + utf32.size > self->length)
        return 0;

    isiz next = self->tail + utf32.size;

    for (isiz i = 0; i < utf32.size; i += 1)
        self->memory[(self->tail + i) % self->length] = utf32.memory[i];

    self->size += utf32.size;
    self->tail  = next % self->length;

    return utf32.size;
}

isiz
buf32_write_str8_tail(buf32* self, str8 value)
{
    isiz size = utf32_units_from_str8(value);
    isiz next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (isiz i = 0, j = 0; j < size;) {
        UTF32 utf32   = {};
        u32   unicode = 0;

        i += str8_read_utf8_forw(value, i, &unicode);

        utf32_encode(&utf32, unicode);

        for (isiz k = 0; k < utf32.size; k += 1)
            self->memory[(self->tail + j + k) % self->length] = utf32.memory[k];

        j += utf32.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

isiz
buf32_write_str16_tail(buf32* self, str16 value)
{
    isiz size = utf32_units_from_str16(value);
    isiz next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (isiz i = 0, j = 0; j < size;) {
        UTF32 utf32   = {};
        u32   unicode = 0;

        i += str16_read_utf16_forw(value, i, &unicode);

        utf32_encode(&utf32, unicode);

        for (isiz k = 0; k < utf32.size; k += 1)
            self->memory[(self->tail + j + k) % self->length] = utf32.memory[k];

        j += utf32.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

isiz
buf32_write_str32_tail(buf32* self, str32 value)
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
buf32_read_utf32_head(buf32* self, u32* value)
{
    UTF32 utf32 = {};

    if (self->size > 0 && self->size <= self->length)
        utf32.size = utf32_units_to_read(self->memory[self->head]);

    if (utf32.size <= 0 || utf32.size > self->size)
        return 0;

    for (isiz i = 0; i < utf32.size; i += 1)
        utf32.memory[i] = self->memory[(self->head + i) % self->length];

    if (utf32_decode(&utf32, value) == 0) return 0;

    isiz next = self->head + utf32.size;

    self->size -= utf32.size;
    self->head  = next % self->length;

    return utf32.size;
}

isiz
buf32_read_utf32_tail(buf32* self, u32* value)
{
    UTF32 utf32 = {};
    isiz  index = (self->tail + self->length - 1) % self->length;

    utf32.size = 1;

    if (utf32.size != utf32_units_to_read(self->memory[index]))
        return 0;

    isiz prev = self->tail + self->length - utf32.size;

    for (isiz i = 0; i < utf32.size; i += 1)
        utf32.memory[i] = self->memory[(prev + i) % self->length];

    if (utf32_decode(&utf32, value) == 0) return 0;

    self->size -= utf32.size;
    self->tail  = prev % self->length;

    return utf32.size;
}

str32
buf32_read_str32_head(buf32* self, Arena* arena, isiz length)
{
    isiz size = pax_limit(self->size, 0, length);
    isiz next = self->head + size;

    str32 result = str32_reserve(arena, size);

    if (result.length <= 0) return result;

    for (isiz i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return result;
}

str32
buf32_read_str32_tail(buf32* self, Arena* arena, isiz length)
{
    isiz size = pax_limit(self->size, 0, length);
    isiz prev = self->tail + self->length - size;

    str32 result = str32_reserve(arena, size);

    if (result.length <= 0) return result;

    self->size -= size;
    self->tail  = prev % self->length;

    for (isiz i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->tail + i) % self->length];

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUF32_CPP
