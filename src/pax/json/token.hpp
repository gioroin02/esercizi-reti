#ifndef PAX_JSON_TOKEN_HPP
#define PAX_JSON_TOKEN_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

enum JSON_Token_Type
{
    JSON_TOKEN_NONE,

    JSON_TOKEN_OPEN_OBJ,
    JSON_TOKEN_OPEN_ARR,
    JSON_TOKEN_CLOSE_OBJ,
    JSON_TOKEN_CLOSE_ARR,
    JSON_TOKEN_COLON,
    JSON_TOKEN_COMMA,

    JSON_TOKEN_STRING,

    JSON_TOKEN_ABSOLUTE,
    JSON_TOKEN_RELATIVE,
    JSON_TOKEN_FLOATING,

    JSON_TOKEN_TRUE,
    JSON_TOKEN_FALSE,
    JSON_TOKEN_NULL,

    JSON_TOKEN_ERROR,
    JSON_TOKEN_COUNT,
};

struct JSON_Token_Error
{
    str8 message = {};
    str8 content = {};
    isiz line    = 0;
    isiz column  = 0;
};

struct JSON_Token
{
    JSON_Token_Type type = JSON_TOKEN_NONE;

    union
    {
        JSON_Token_Error error;

        str8 string;
        usiz absolute;
        isiz relative;
        f64  floating;
    };
};

//
// Procs
//

JSON_Token
json_token_none();

JSON_Token
json_token_open_obj();

JSON_Token
json_token_open_arr();

JSON_Token
json_token_close_obj();

JSON_Token
json_token_close_arr();

JSON_Token
json_token_colon();

JSON_Token
json_token_comma();

JSON_Token
json_token_string(str8 value);

JSON_Token
json_token_absolute(usiz value);

JSON_Token
json_token_relative(isiz value);

JSON_Token
json_token_floating(f64 value);

JSON_Token
json_token_true();

JSON_Token
json_token_false();

JSON_Token
json_token_null();

JSON_Token
json_token_error(Arena* arena, str8 message, str8 content, isiz line, isiz column);

JSON_Token
json_token_count();

} // namespace pax

#endif // PAX_JSON_TOKEN_HPP
