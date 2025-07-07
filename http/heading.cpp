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
    u64  result = other;

    if (hash_map_get(self, HTTP_STATUS, &string) == 0)
        return other;

    Format_Spec spec = format_spec(10, FORMAT_FLAG_NONE);

    if (str8_parse_u64(string, spec, &result) == 0)
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

uptr
http_heading_get_content_length(HTTP_Heading* self, uptr other)
{
    str8 string = {};
    u64  result = other;

    if (hash_map_get(self, HTTP_HEADER_CONTENT_LENGTH, &string) == 0)
        return other;

    Format_Spec spec = format_spec(10, FORMAT_FLAG_NONE);

    if (str8_parse_u64(string, spec, &result) == 0)
        return other;

    return result;
}

#endif // HTTP_HEADING_CPP
