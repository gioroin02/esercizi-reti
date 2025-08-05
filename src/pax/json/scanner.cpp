#ifndef PAX_JSON_SCANNER_CPP
#define PAX_JSON_SCANNER_CPP

#include "scanner.hpp"

namespace pax {

JSON_Scanner
json_scanner_make(buf8* buffer, isiz line, isiz column)
{
    JSON_Scanner result = {};

    result.buffer = buffer;

    if (line   >= 0) result.line   = line;
    if (column >= 0) result.column = column;

    return result;
}

buf8*
json_scanner_set_buffer(JSON_Scanner* self, buf8* buffer)
{
    buf8* result = self->buffer;

    if (buffer != 0)
        self->buffer = buffer;
    else
        return 0;

    return result;
}

JSON_Token
json_scanner_token(JSON_Scanner* self, Arena* arena)
{
    u32 ascii = json_scanner_skip_spaces(self);

    switch (ascii) {
        case ASCII_NULL: return json_token_count();

        case ASCII_BRACE_LEFT:
        case ASCII_BRACE_RIGHT:
        case ASCII_SQUARE_LEFT:
        case ASCII_SQUARE_RIGHT:
        case ASCII_COLON:
        case ASCII_COMMA: {
            JSON_Token_Type type = JSON_TOKEN_NULL;

            str8 string = json_scanner_symbol(self, arena, &type);

            switch (type) {
                case JSON_TOKEN_OPEN_OBJ:  return json_token_open_obj();
                case JSON_TOKEN_OPEN_ARR:  return json_token_open_arr();
                case JSON_TOKEN_CLOSE_OBJ: return json_token_close_obj();
                case JSON_TOKEN_CLOSE_ARR: return json_token_close_arr();
                case JSON_TOKEN_COLON:     return json_token_colon();
                case JSON_TOKEN_COMMA:     return json_token_comma();

                default: break;
            }

            return json_token_error(arena, pax_str8("Unknown symbol"),
                string, self->line, self->column);
        } break;

        case ASCII_MARK_QUOTE: {
            JSON_Token_Type type = JSON_TOKEN_NULL;

            str8 string = json_scanner_string(self, arena, &type);

            if (type == JSON_TOKEN_STRING)
                return json_token_string(string);

            return json_token_error(arena, pax_str8("Invalid string"),
                string, self->line, self->column);
        } break;

        case ASCII_PLUS:
        case ASCII_MINUS:
        case ASCII_ZERO:
        case ASCII_ONE:
        case ASCII_TWO:
        case ASCII_THREE:
        case ASCII_FOUR:
        case ASCII_FIVE:
        case ASCII_SIX:
        case ASCII_SEVEN:
        case ASCII_EIGHT:
        case ASCII_NINE: {
            JSON_Token_Type type = JSON_TOKEN_NULL;

            str8 string = json_scanner_number(self, arena, &type);

            switch (type) {
                case JSON_TOKEN_ABSOLUTE:
                    return json_scanner_absolute(self, arena, string);

                case JSON_TOKEN_RELATIVE:
                    return json_scanner_relative(self, arena, string);

                case JSON_TOKEN_FLOATING:
                    return json_scanner_floating(self, arena, string);

                default: break;
            }

            return json_token_error(arena, pax_str8("Invalid number"),
                string, self->line, self->column);
        } break;

        case ASCII_LOWER_T:
        case ASCII_LOWER_F:
        case ASCII_LOWER_N: {
            JSON_Token_Type type = JSON_TOKEN_NULL;

            str8 string = json_scanner_word(self, arena, &type);

            switch (type) {
                case JSON_TOKEN_TRUE:  return json_token_true();
                case JSON_TOKEN_FALSE: return json_token_false();
                case JSON_TOKEN_NULL:  return json_token_null();

                default: break;
            }

            return json_token_error(arena, pax_str8("Unknown name"),
                string, self->line, self->column);
        } break;

        default: break;
    }

    return json_token_error(arena, pax_str8("Unknown symbol"),
        str8_from_unicode(arena, ascii), self->line, self->column);
}

str8
json_scanner_symbol(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type)
{
    u32 ascii = json_scanner_peek(self, 0);

    JSON_Token_Type temp = JSON_TOKEN_NULL;

    switch (ascii) {
        case ASCII_BRACE_LEFT:   { temp = JSON_TOKEN_OPEN_OBJ;  } break;
        case ASCII_BRACE_RIGHT:  { temp = JSON_TOKEN_CLOSE_OBJ; } break;
        case ASCII_SQUARE_LEFT:  { temp = JSON_TOKEN_OPEN_ARR;  } break;
        case ASCII_SQUARE_RIGHT: { temp = JSON_TOKEN_CLOSE_ARR; } break;
        case ASCII_COLON:        { temp = JSON_TOKEN_COLON;     } break;
        case ASCII_COMMA:        { temp = JSON_TOKEN_COMMA;     } break;

        default: break;
    }

    str8 string = str8_reserve(arena, 1);

    for (isiz i = 0; i < string.length; i += 1)
        string.memory[i] = buf8_get_head_or(self->buffer, i, 0);

    json_scanner_step(self, 1);

    if (type != 0) *type = temp;

    return string;
}

str8
json_scanner_string(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type)
{
    u32  ascii = json_scanner_peek(self, 0);
    isiz index = 0;

    if (ascii != ASCII_MARK_QUOTE) return {};

    index += 1;
    ascii  = json_scanner_peek(self, index);

    while (ascii != ASCII_NULL) {
        if (ascii == ASCII_MARK_QUOTE) break;

        index += 1;
        ascii  = json_scanner_peek(self, index);
    }

    if (ascii != ASCII_MARK_QUOTE) return {};

    str8 string = str8_reserve(arena, index - 1);

    for (isiz i = 0; i < string.length; i += 1)
        string.memory[i] = buf8_get_head_or(self->buffer, i + 1, 0);

    json_scanner_step(self, index + 1);

    if (type != 0) *type = JSON_TOKEN_STRING;

    return string;
}

str8
json_scanner_number(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type)
{
    u32  ascii = json_scanner_peek(self, 0);
    isiz index = 0;

    JSON_Token_Type temp = JSON_TOKEN_ABSOLUTE;

    while (ascii != ASCII_NULL) {
        b32 state = 0;

        if (ascii_is_digit(ascii, 10) != 0) state = 1;

        switch (ascii) {
            case ASCII_POINT:
            case ASCII_LOWER_E:
            case ASCII_UPPER_E: {
                state = 1;

                if (temp == JSON_TOKEN_ABSOLUTE || temp == JSON_TOKEN_RELATIVE)
                    temp = JSON_TOKEN_FLOATING;
            } break;

            case ASCII_PLUS: { state = 1; } break;

            case ASCII_MINUS: {
                state = 1;

                if (temp == JSON_TOKEN_ABSOLUTE)
                    temp = JSON_TOKEN_RELATIVE;
            } break;

            default: break;
        }

        if (state == 0) break;

        index += 1;
        ascii  = json_scanner_peek(self, index);
    }

    str8 string = str8_reserve(arena, index);

    for (isiz i = 0; i < string.length; i += 1)
        string.memory[i] = buf8_get_head_or(self->buffer, i, 0);

    json_scanner_step(self, index);

    if (type != 0) *type = temp;

    return string;
}

JSON_Token
json_scanner_absolute(JSON_Scanner* self, Arena* arena, str8 string)
{
    Format_Options options = format_options_simple(10);

    usiz value = 0;

    if (usiz_from_str8(string, options, &value) != 0)
        return json_token_absolute(value);

    return json_token_error(arena, pax_str8("Invalid number"),
        string, self->line, self->column);
}

JSON_Token
json_scanner_relative(JSON_Scanner* self, Arena* arena, str8 string)
{
    Format_Options options = format_options_simple(10);

    isiz value = 0;

    if (isiz_from_str8(string, options, &value) != 0)
        return json_token_relative(value);

    return json_token_error(arena, pax_str8("Invalid number"),
        string, self->line, self->column);
}

JSON_Token
json_scanner_floating(JSON_Scanner* self, Arena* arena, str8 string)
{
    return json_token_error(arena, pax_str8("Not implemented yet"),
        string, self->line, self->column);
}

str8
json_scanner_word(JSON_Scanner* self, Arena* arena, JSON_Token_Type* type)
{
    u32  ascii = json_scanner_peek(self, 0);
    isiz index = 0;

    JSON_Token_Type temp = JSON_TOKEN_NULL;

    while (ascii != ASCII_NULL) {
        b32 state = 0;

        if (ascii_is_digit(ascii, 10) != 0) state = 1;
        if (ascii_is_letter(ascii)    != 0) state = 1;

        if (state == 0) break;

        index += 1;
        ascii  = json_scanner_peek(self, index);
    }

    str8 string = str8_reserve(arena, index);

    for (isiz i = 0; i < string.length; i += 1)
        string.memory[i] = buf8_get_head_or(self->buffer, i, 0);

    json_scanner_step(self, index);

    if (str8_is_equal(string, pax_str8("null"))  != 0) temp = JSON_TOKEN_NULL;
    if (str8_is_equal(string, pax_str8("true"))  != 0) temp = JSON_TOKEN_TRUE;
    if (str8_is_equal(string, pax_str8("false")) != 0) temp = JSON_TOKEN_FALSE;

    if (type != 0) *type = temp;

    return string;
}

u32
json_scanner_peek(JSON_Scanner* self, isiz offset)
{
    return buf8_get_head_or(self->buffer,
        offset % self->buffer->length, ASCII_NULL);
}

u32
json_scanner_step(JSON_Scanner* self, isiz offset)
{
    offset = buf8_drop_head(self->buffer, offset);

    self->column += offset;

    return buf8_get_head_or(self->buffer,
        0, ASCII_NULL);
}

u32
json_scanner_expect(JSON_Scanner* self, u32 value)
{
    u32 ascii = buf8_get_head_or(self->buffer,
        0, ASCII_NULL);

    if (ascii == value) return json_scanner_step(self, 1);

    return ASCII_NULL;
}

u32
json_scanner_skip_spaces(JSON_Scanner* self)
{
    u32  ascii = json_scanner_peek(self, 0);
    isiz index = 0;

    while (ascii_is_space(ascii) != 0) {
        index += 1;

        if (ascii == ASCII_LINE_FEED) {
            self->line   += 1;
            self->column  = 0;
        }

        ascii = json_scanner_peek(self, index);
    }

    return json_scanner_step(self, index);
}

} // namespace pax

#endif // PAX_JSON_SCANNER_CPP
