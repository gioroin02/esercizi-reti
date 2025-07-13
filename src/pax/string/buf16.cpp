#ifndef PAX_STRING_BUF16_CPP
#define PAX_STRING_BUF16_CPP

#include "buf16.hpp"

namespace pax {

uptr
buf16_write_codepoint_head(buf16* self, u32 value)
{
    uptr size = utf16_units_to_write(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size -= size;
    self->head  = prev % self->length;

    utf16_encode_forw_circ(self->memory,
        self->length, self->head, value);

    return size;
}

uptr
buf16_write_codepoint_tail(buf16* self, u32 value)
{
    uptr size = utf16_units_to_write(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    utf16_encode_forw_circ(self->memory,
        self->length, self->tail, value);

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf16_write_str8_head(buf16* self, str8 value)
{
    uptr size = utf16_units_from_str8(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf8_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf16_encode_forw_circ(self->memory, self->length,
            (self->head + j) % self->length, unicode);
    }

    return size;
}

uptr
buf16_write_str8_tail(buf16* self, str8 value)
{
    uptr size = utf16_units_from_str8(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf8_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf16_encode_forw_circ(self->memory, self->length,
            (self->tail + j) % self->length, unicode);
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf16_write_str16_head(buf16* self, str16 value)
{
    uptr size = value.length;
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        self->memory[(self->head + i) % self->length] = value.memory[i];

    return size;
}

uptr
buf16_write_str16_tail(buf16* self, str16 value)
{
    uptr size = value.length;
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0; i < size; i += 1)
        self->memory[(self->tail + i) % self->length] = value.memory[i];

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf16_write_str32_head(buf16* self, str32 value)
{
    uptr size = utf16_units_from_str32(value);
    uptr prev = self->head + self->length - size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    self->size += size;
    self->head  = prev % self->length;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf32_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf16_encode_forw_circ(self->memory, self->length,
            (self->head + j) % self->length, unicode);
    }

    return size;
}

uptr
buf16_write_str32_tail(buf16* self, str32 value)
{
    uptr size = utf16_units_from_str32(value);
    uptr next = self->tail + size;

    if (self->size < 0 || self->size + size > self->length)
        return 0;

    for (uptr i = 0, j = 0; j < size;) {
        u32 unicode = 0;

        i += utf32_decode_forw(value.memory,
            value.length, i, &unicode);

        j += utf16_encode_forw_circ(self->memory, self->length,
            (self->tail + j) % self->length, unicode);
    }

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

uptr
buf16_read_codepoint_head(buf16* self, u32* value)
{
    uptr size = utf16_decode_forw_circ(self->memory,
        self->length, self->head, value);

    uptr next = self->head + size;

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

uptr
buf16_read_codepoint_tail(buf16* self, u32* value)
{
    uptr prev = self->tail + self->length - 1;

    uptr size = utf16_decode_back_circ(self->memory,
        self->length, prev % self->length, value);

    prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    return size;
}

str16
buf16_read_str16_head(buf16* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr next = self->head + size;

    str16 result = str16_reserve(arena, size);

    if (result.length == 0) return result;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return result;
}

str16
buf16_read_str16_tail(buf16* self, Arena* arena, uptr length)
{
    uptr size = pax_min(self->size, length);
    uptr prev = self->tail + self->length - size;

    str16 result = str16_reserve(arena, size);

    if (result.length == 0) return result;

    self->size -= size;
    self->tail  = prev % self->length;

    for (uptr i = 0; i < size; i += 1)
        result.memory[i] = self->memory[(self->tail + i) % self->length];

    return result;
}

} // namespace pax

#endif // PAX_STRING_BUF16_CPP
