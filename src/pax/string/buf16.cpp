#ifndef PAX_STRING_BUF16_CPP
#define PAX_STRING_BUF16_CPP

#include "buf16.hpp"

namespace pax {

isiz
buf16_write_utf16_head(buf16* self, u32 value)
{
    UTF16 utf16 = {};

    if (utf16_encode(&utf16, value) == 0) return 0;

    if (self->size < 0 || self->size + utf16.size > self->length)
        return 0;

    isiz prev = self->head + self->length - utf16.size;

    self->size += utf16.size;
    self->head  = prev % self->length;

    for (isiz i = 0; i < utf16.size; i += 1)
        self->memory[(self->head + i) % self->length] = utf16.memory[i];

    return utf16.size;
}

isiz
buf16_write_str8_head(buf16* self, str8 value)
{
    isiz size = utf16_units_from_str8(value);
    isiz prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0, j = 0; j < size;) {
        UTF16 utf16   = {};
        u32   unicode = 0;

        i += str8_read_utf8_forw(value, i, &unicode);

        utf16_encode(&utf16, unicode);

        for (isiz k = 0; k < utf16.size; k += 1)
            self->memory[(self->head + j + k) % self->length] = utf16.memory[k];

        j += utf16.size;
    }

    return size;
}

isiz
buf16_write_str16_head(buf16* self, str16 value)
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
buf16_write_str32_head(buf16* self, str32 value)
{
    isiz size = utf16_units_from_str32(value);
    isiz prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (isiz i = 0, j = 0; j < size;) {
        UTF16 utf16   = {};
        u32   unicode = 0;

        i += str32_read_utf32_forw(value, i, &unicode);

        utf16_encode(&utf16, unicode);

        for (isiz k = 0; k < utf16.size; k += 1)
            self->memory[(self->head + j + k) % self->length] = utf16.memory[k];

        j += utf16.size;
    }

    return size;
}

isiz
buf16_write_utf16_tail(buf16* self, u32 value)
{
    UTF16 utf16 = {};

    if (utf16_encode(&utf16, value) == 0) return 0;

    if (self->size < 0 || self->size + utf16.size > self->length)
        return 0;

    isiz next = self->tail + utf16.size;

    for (isiz i = 0; i < utf16.size; i += 1)
        self->memory[(self->tail + i) % self->length] = utf16.memory[i];

    self->size += utf16.size;
    self->tail  = next % self->length;

    return utf16.size;
}

isiz
buf16_write_str8_tail(buf16* self, str8 value)
{
    isiz size = utf16_units_from_str8(value);
    isiz next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (isiz i = 0, j = 0; j < size;) {
        UTF16 utf16   = {};
        u32   unicode = 0;

        i += str8_read_utf8_forw(value, i, &unicode);

        utf16_encode(&utf16, unicode);

        for (isiz k = 0; k < utf16.size; k += 1)
            self->memory[(self->tail + j + k) % self->length] = utf16.memory[k];

        j += utf16.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

isiz
buf16_write_str16_tail(buf16* self, str16 value)
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
buf16_write_str32_tail(buf16* self, str32 value)
{
    isiz size = utf16_units_from_str32(value);
    isiz next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (isiz i = 0, j = 0; j < size;) {
        UTF16 utf16   = {};
        u32   unicode = 0;

        i += str32_read_utf32_forw(value, i, &unicode);

        utf16_encode(&utf16, unicode);

        for (isiz k = 0; k < utf16.size; k += 1)
            self->memory[(self->tail + j + k) % self->length] = utf16.memory[k];

        j += utf16.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

isiz
buf16_read_utf16_head(buf16* self, u32* value)
{
    UTF16 utf16 = {};

    if (self->size > 0 && self->size <= self->length)
        utf16.size = utf16_units_to_read(self->memory[self->head]);

    if (utf16.size <= 0 || utf16.size > self->size)
        return 0;

    for (isiz i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = self->memory[(self->head + i) % self->length];

    if (utf16_decode(&utf16, value) == 0) return 0;

    isiz next = self->head + utf16.size;

    self->size -= utf16.size;
    self->head  = next % self->length;

    return utf16.size;
}

isiz
buf16_read_utf16_tail(buf16* self, u32* value)
{
    UTF16 utf16 = {};
    isiz  index = (self->tail + self->length - 1) % self->length;
    isiz  count = 0;

    for (; count < 2; count += 1) {
        if (unicode_is_surrogate_low(self->memory[index]) == 0)
            break;

        index = (index + self->length - 1) % self->length;
    }

    utf16.size = count + 1;

    if (utf16.size != utf16_units_to_read(self->memory[index]))
        return 0;

    isiz prev = self->tail + self->length - utf16.size;

    for (isiz i = 0; i < utf16.size; i += 1)
        utf16.memory[i] = self->memory[(prev + i) % self->length];

    if (utf16_decode(&utf16, value) == 0) return 0;

    self->size -= utf16.size;
    self->tail  = prev % self->length;

    return utf16.size;
}

str16
buf16_read_str16_head(buf16* self, Arena* arena, isiz length)
{
    isiz size = pax_limit(self->size, 0, length);
    isiz next = self->head + size;

    str16 result = str16_reserve(arena, size);

    if (result.length <= 0) return result;

    for (isiz i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return result;
}

str16
buf16_read_str16_tail(buf16* self, Arena* arena, isiz length)
{
    isiz size = pax_limit(self->size, 0, length);
    isiz prev = self->tail + self->length - size;

    str16 result = str16_reserve(arena, size);

    if (result.length <= 0) return result;

    self->size -= size;
    self->tail  = prev % self->length;

    for (isiz i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->tail + i) % self->length];

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUF16_CPP
