#ifndef PAX_STRING_CONVERT_CPP
#define PAX_STRING_CONVERT_CPP

#include "convert.hpp"

namespace pax {

isiz
utf8_units_from_mem16(u16* memory, isiz length)
{
    isiz result = 0;

    for (isiz index = 0; index < length;) {
        u32 unicode = 0;

        isiz read = mem16_read_utf16_forw(memory,
            length, index, &unicode);

        isiz write = utf8_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

isiz
utf8_units_from_str16(str16 value)
{
    return utf8_units_from_mem16(value.memory, value.length);
}

isiz
utf8_units_from_mem32(u32* memory, isiz length)
{
    isiz result = 0;

    for (isiz index = 0; index < length;) {
        u32 unicode = 0;

        isiz read = mem32_read_utf32_forw(memory,
            length, index, &unicode);

        isiz write = utf8_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

isiz
utf8_units_from_str32(str32 value)
{
    return utf8_units_from_mem32(value.memory, value.length);
}

isiz
utf16_units_from_mem8(u8* memory, isiz length)
{
    isiz result = 0;

    for (isiz index = 0; index < length;) {
        u32 unicode = 0;

        isiz read = mem8_read_utf8_forw(memory,
            length, index, &unicode);

        isiz write = utf16_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

isiz
utf16_units_from_str8(str8 value)
{
    return utf16_units_from_mem8(value.memory, value.length);
}

isiz
utf16_units_from_mem32(u32* memory, isiz length)
{
    isiz result = 0;

    for (isiz index = 0; index < length;) {
        u32 unicode = 0;

        isiz read = mem32_read_utf32_forw(memory,
            length, index, &unicode);

        isiz write = utf16_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

isiz
utf16_units_from_str32(str32 value)
{
    return utf16_units_from_mem32(value.memory, value.length);
}

isiz
utf32_units_from_mem8(u8* memory, isiz length)
{
    isiz result = 0;

    for (isiz index = 0; index < length;) {
        u32 unicode = 0;

        isiz read = mem8_read_utf8_forw(memory,
            length, index, &unicode);

        isiz write = utf32_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

isiz
utf32_units_from_str8(str8 value)
{
    return utf32_units_from_mem8(value.memory, value.length);
}

isiz
utf32_units_from_mem16(u16* memory, isiz length)
{
    isiz result = 0;

    for (isiz index = 0; index < length;) {
        u32 unicode = 0;

        isiz read = mem16_read_utf16_forw(memory,
            length, index, &unicode);

        isiz write = utf32_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

isiz
utf32_units_from_str16(str16 value)
{
    return utf32_units_from_mem16(value.memory, value.length);
}

str8
str8_from_str16(Arena* arena, str16 value)
{
    isiz length = utf8_units_from_str16(value);
    str8 result = str8_reserve(arena, length);

    if (result.length <= 0) return result;

    for (isiz i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += str16_read_utf16_forw(value, i, &unicode);
        j += str8_write_utf8_forw(result, j, unicode);
    }

    return result;
}

str8
str8_from_str32(Arena* arena, str32 value)
{
    isiz length = utf8_units_from_str32(value);
    str8 result = str8_reserve(arena, length);

    if (result.length <= 0) return result;

    for (isiz i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += str32_read_utf32_forw(value, i, &unicode);
        j += str8_write_utf8_forw(result, j, unicode);
    }

    return result;
}

str16
str16_from_str8(Arena* arena, str8 value)
{
    usiz  length = utf16_units_from_str8(value);
    str16 result = str16_reserve(arena, length);

    if (result.length <= 0) return result;

    for (isiz i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += str8_read_utf8_forw(value, i, &unicode);
        j += str16_write_utf16_forw(result, j, unicode);
    }

    return result;
}

str16
str16_from_str32(Arena* arena, str32 value)
{
    usiz  length = utf16_units_from_str32(value);
    str16 result = str16_reserve(arena, length);

    if (result.length <= 0) return result;

    for (isiz i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += str32_read_utf32_forw(value, i, &unicode);
        j += str16_write_utf16_forw(result, j, unicode);
    }

    return result;
}

str32
str32_from_str8(Arena* arena, str8 value)
{
    usiz  length = utf32_units_from_str8(value);
    str32 result = str32_reserve(arena, length);

    if (result.length <= 0) return result;

    for (isiz i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += str8_read_utf8_forw(value, i, &unicode);
        j += str32_write_utf32_forw(result, j, unicode);
    }

    return result;
}

str32
str32_from_str16(Arena* arena, str16 value)
{
    usiz  length = utf32_units_from_str16(value);
    str32 result = str32_reserve(arena, length);

    if (result.length <= 0) return result;

    for (isiz i = 0, j = 0; j < length;) {
        u32 unicode = 0;

        i += str16_read_utf16_forw(value, i, &unicode);
        j += str32_write_utf32_forw(result, j, unicode);
    }

    return result;
}

} // namespace pax

#endif // PAX_STRING_CONVERT_CPP
