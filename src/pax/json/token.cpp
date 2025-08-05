#ifndef PAX_JSON_TOKEN_CPP
#define PAX_JSON_TOKEN_CPP

#include "token.hpp"

namespace pax {

JSON_Token
json_token_none()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_NONE;

    return result;
}

JSON_Token
json_token_open_obj()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_OPEN_OBJ;

    return result;
}

JSON_Token
json_token_open_arr()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_OPEN_ARR;

    return result;
}

JSON_Token
json_token_close_obj()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_CLOSE_OBJ;

    return result;
}

JSON_Token
json_token_close_arr()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_CLOSE_ARR;

    return result;
}

JSON_Token
json_token_colon()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_COLON;

    return result;
}

JSON_Token
json_token_comma()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_COMMA;

    return result;
}

JSON_Token
json_token_string(str8 value)
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_STRING;

    result.string = value;

    return result;
}

JSON_Token
json_token_absolute(usiz value)
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_ABSOLUTE;

    result.absolute = value;

    return result;
}

JSON_Token
json_token_relative(isiz value)
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_RELATIVE;

    result.relative = value;

    return result;
}

JSON_Token
json_token_floating(f64 value)
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_FLOATING;

    result.floating = value;

    return result;
}

JSON_Token
json_token_true()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_TRUE;

    return result;
}

JSON_Token
json_token_false()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_FALSE;

    return result;
}

JSON_Token
json_token_null()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_NULL;

    return result;
}

JSON_Token
json_token_error(Arena* arena, str8 message, str8 content, isiz line, isiz column)
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_ERROR;

    result.error.message = str8_copy(arena, message);
    result.error.content = str8_copy(arena, content);
    result.error.line    = line;
    result.error.column  = column;

    return result;
}

JSON_Token
json_token_count()
{
    JSON_Token result = {};

    result.type = JSON_TOKEN_COUNT;

    return result;
}

} // namespace pax

#endif // PAX_JSON_TOKEN_CPP
