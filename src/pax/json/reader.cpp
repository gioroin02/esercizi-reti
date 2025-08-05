#ifndef PAX_JSON_READER_CPP
#define PAX_JSON_READER_CPP

#include "reader.hpp"

namespace pax {

JSON_Reader
json_reader_make(Arena* arena, isiz length, buf8* buffer)
{
    JSON_Reader result = {};

    result.queue  = pax_queue_reserve(arena, JSON_Group_Type, length);
    result.buffer = buffer;

    return result;
}

buf8*
json_reader_set_buffer(JSON_Reader* self, buf8* buffer)
{
    buf8* result = self->buffer;

    if (buffer != 0)
        self->buffer = buffer;
    else
        return 0;

    return result;
}

JSON_Event
json_reader_event(JSON_Reader* self, Arena* arena)
{
    JSON_Scanner scanner = json_scanner_make(self->buffer,
        self->line, self->column);

    JSON_Token token = json_token_none();

    while (token.type != JSON_TOKEN_COUNT) {
        token = json_scanner_token(&scanner, arena);

        b32  colon = self->colon;
        b32  comma = self->comma;
        str8 name  = self->name;

        self->line   = scanner.line;
        self->column = scanner.column;
        self->colon  = 0;
        self->comma  = 0;

        JSON_Group_Type parent = JSON_GROUP_NONE;
        JSON_Event      event  = json_event_none();

        pax_queue_get_tail(&self->queue, JSON_Group_Type, &parent);

        switch (token.type) {
            case JSON_TOKEN_OPEN_OBJ: {
                JSON_Group_Type group = JSON_GROUP_OBJECT;

                pax_queue_insert_tail(&self->queue,
                    JSON_Group_Type, &group);

                if (parent == JSON_GROUP_OBJECT && name.length > 0)
                    event = json_event_name(name);
            } break;

            case JSON_TOKEN_OPEN_ARR: {
                JSON_Group_Type group = JSON_GROUP_ARRAY;

                pax_queue_insert_tail(&self->queue,
                    JSON_Group_Type, &group);

                if (parent == JSON_GROUP_OBJECT && name.length > 0)
                    event = json_event_name(name);
            } break;

            case JSON_TOKEN_CLOSE_OBJ: {
                queue_drop_tail(&self->queue);

                event = json_event_stop();
            } break;

            case JSON_TOKEN_CLOSE_ARR: {
                queue_drop_tail(&self->queue);

                event = json_event_stop();
            } break;

            case JSON_TOKEN_COLON: {
                str8 message = pax_str8("Unexpected token");
                str8 content = pax_str8(":");
                isiz line    = self->line;
                isiz column  = self->column;

                self->colon = 1;

                if (parent != JSON_GROUP_OBJECT || name.length <= 0)
                    return json_event_error(arena, message, content, line, column);
            } break;

            case JSON_TOKEN_COMMA: {
                str8 message = pax_str8("Unexpected token");
                str8 content = pax_str8(",");
                isiz line    = self->line;
                isiz column  = self->column;

                self->comma = 1;

                if (parent == JSON_GROUP_NONE)
                    return json_event_error(arena, message, content, line, column);
            }

            case JSON_TOKEN_STRING: {
                if (colon != 0)
                    event = json_event_string(token.string);
                else
                    self->name = token.string;
            } break;

            case JSON_TOKEN_ABSOLUTE: {
                event = json_event_absolute(token.absolute);
            } break;

            case JSON_TOKEN_RELATIVE: {
                event = json_event_relative(token.relative);
            } break;

            case JSON_TOKEN_FLOATING: {
                event = json_event_floating(token.floating);
            } break;

            case JSON_TOKEN_TRUE: {
                event = json_event_boolean(1);
            } break;

            case JSON_TOKEN_FALSE: {
                event = json_event_boolean(0);
            } break;

            case JSON_TOKEN_NULL: {
                event = json_event_null();
            } break;

            case JSON_TOKEN_ERROR: {
                str8 message = token.error.message;
                str8 content = token.error.content;
                isiz line    = token.error.line;
                isiz column  = token.error.column;

                JSON_Event event = json_event_error(arena,
                    message, content, line, column);

                pax_queue_insert_tail(&self->queue,
                    JSON_Event, &event);
            } break;

            default: break;
        }

        if (event.type == JSON_EVENT_NONE) continue;

        switch (parent) {
            case JSON_GROUP_OBJECT:
                return json_event_object(event, self->name);

            case JSON_GROUP_ARRAY:
                return json_event_array(event);

            default: break;
        }

        return event;
    }

    return json_event_count();
}

} // namespace pax

#endif // PAX_JSON_READER_CPP
