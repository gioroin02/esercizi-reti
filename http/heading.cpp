#ifndef HTTP_HEADING_CPP
#define HTTP_HEADING_CPP

#include "heading.hpp"

str8
http_heading_get_method(HTTP_Heading* self, str8 other)
{
    return hash_map_get_or(self, HTTP_METHOD, other);
}

str8
http_heading_get_resource(HTTP_Heading* self, str8 other)
{
    return hash_map_get_or(self, HTTP_RESOURCE, other);
}

str8
http_heading_get_version(HTTP_Heading* self, str8 other)
{
    return hash_map_get_or(self, HTTP_VERSION, other);
}

uptr
http_heading_get_status(HTTP_Heading* self, uptr other)
{
    str8 string = {};
    uptr result = other;

    if (hash_map_get(self, HTTP_STATUS, &string) == 0)
        return other;

    Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

    if (uptr_from_str8(string, opts, &result) == 0)
        return other;

    return result;
}

str8
http_heading_get_message(HTTP_Heading* self, str8 other)
{
    return hash_map_get_or(self, HTTP_MESSAGE, other);
}

str8
http_heading_get_content_type(HTTP_Heading* self, str8 other)
{
    return hash_map_get_or(self, HTTP_HEADER_CONTENT_TYPE, other);
}

HTTP_Heading
http_parse_content_type(Arena* arena, str8* string)
{
    HTTP_Heading result =
        hash_map_reserve<str8, str8>(arena, 64, &http_hash_str8);

    str8 left  = {};
    str8 right = {};

    if (string == 0) return result;

    left = str8_split_on(*string, pax_str8(";"), &right);

    left  = str8_trim_spaces(left);
    right = str8_trim_spaces(right);

    *string = left;

    str8 pair  = {};
    str8 key   = {};
    str8 value = {};

    while (right.length != 0) {
        pair = str8_split_on(right, pax_str8(";"), &right);
        key  = str8_split_on(pair, pax_str8("="), &value);

        key   = str8_trim_spaces(key);
        value = str8_trim_spaces(value);

        hash_map_insert(&result, str8_copy(arena, key),
            str8_copy(arena, value));
    }

    return result;
}

HTTP_Heading
http_parse_content_disp(Arena* arena, str8* string)
{
    HTTP_Heading result =
        hash_map_reserve<str8, str8>(arena, 64, &http_hash_str8);

    str8 left  = {};
    str8 right = {};

    if (string == 0) return result;

    left = str8_split_on(*string, pax_str8(";"), &right);

    left  = str8_trim_spaces(left);
    right = str8_trim_spaces(right);

    *string = left;

    str8 pair  = {};
    str8 key   = {};
    str8 value = {};

    while (right.length != 0) {
        pair = str8_split_on(right, pax_str8(";"), &right);
        key  = str8_split_on(pair, pax_str8("="), &value);

        key   = str8_trim_spaces(key);
        value = str8_trim_spaces(value);

        hash_map_insert(&result, str8_copy(arena, key),
            str8_copy(arena, value));
    }

    return result;
}

uptr
http_heading_get_content_length(HTTP_Heading* self, uptr other)
{
    str8 string = {};
    uptr result = other;

    if (hash_map_get(self, HTTP_HEADER_CONTENT_LENGTH, &string) == 0)
        return other;

    Format_Options opts = format_options(10, FORMAT_FLAG_NONE);

    if (uptr_from_str8(string, opts, &result) == 0)
        return other;

    return result;
}

HTTP_Heading
http_parse_multipart(Arena* arena, str8* string)
{
    HTTP_Heading result =
        hash_map_reserve<str8, str8>(arena, 64, &http_hash_str8);

    str8 left  = {};
    str8 right = {};

    if (string == 0) return result;

    left = str8_split_on(*string, pax_str8("\r\n\r\n"), &right);

    left  = str8_trim_spaces(left);
    right = str8_trim_spaces(right);

    *string = right;

    str8 pair  = {};
    str8 key   = {};
    str8 value = {};

    while (left.length != 0) {
        pair = str8_split_on(left, pax_str8("\r\n"), &left);
        key  = str8_split_on(pair, pax_str8(":"), &value);

        key   = str8_trim_spaces(key);
        value = str8_trim_spaces(value);

        hash_map_insert(&result, str8_copy(arena, key),
            str8_copy(arena, value));
    }

    return result;
}

#endif // HTTP_HEADING_CPP
