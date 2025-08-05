#ifndef PAX_JSON_EVENT_CPP
#define PAX_JSON_EVENT_CPP

#include "event.hpp"

namespace pax {

JSON_Event
json_event_none()
{
    JSON_Event result = {};

    result.type = JSON_EVENT_NONE;

    return result;
}

JSON_Event
json_event_object(JSON_Event value, str8 name)
{
    JSON_Event result = value;

    result.group = JSON_GROUP_OBJECT;
    result.name  = name;

    return result;
}

JSON_Event
json_event_array(JSON_Event value)
{
    JSON_Event result = value;

    result.group = JSON_GROUP_ARRAY;

    return result;
}

JSON_Event
json_event_name(str8 name)
{
    JSON_Event result = {};

    result.type = JSON_EVENT_NAME;
    result.name = name;

    return result;
}

JSON_Event
json_event_stop()
{
    JSON_Event result = {};

    result.type = JSON_EVENT_STOP;

    return result;
}

JSON_Event
json_event_string(str8 value)
{
    JSON_Event result = {};

    result.type   = JSON_EVENT_STRING;
    result.string = value;

    return result;
}

JSON_Event
json_event_absolute(usiz value)
{
    JSON_Event result = {};

    result.type     = JSON_EVENT_ABSOLUTE;
    result.absolute = value;

    return result;
}

JSON_Event
json_event_relative(isiz value)
{
    JSON_Event result = {};

    result.type     = JSON_EVENT_RELATIVE;
    result.relative = value;

    return result;
}

JSON_Event
json_event_floating(f64 value)
{
    JSON_Event result = {};

    result.type     = JSON_EVENT_FLOATING;
    result.floating = value;

    return result;
}

JSON_Event
json_event_boolean(b32 value)
{
    JSON_Event result = {};

    result.type    = JSON_EVENT_BOOLEAN;
    result.boolean = value;

    return result;
}

JSON_Event
json_event_null()
{
    JSON_Event result = {};

    result.type = JSON_EVENT_NULL;

    return result;
}

JSON_Event
json_event_error(Arena* arena, str8 message, str8 content, isiz line, isiz column)
{
    JSON_Event result = {};

    result.type = JSON_EVENT_ERROR;

    result.error.message = str8_copy(arena, message);
    result.error.content = str8_copy(arena, content);
    result.error.line    = line;
    result.error.column  = column;

    return result;
}

JSON_Event
json_event_count()
{
    JSON_Event result = {};

    result.type = JSON_EVENT_COUNT;

    return result;
}

} // namespace pax

#endif // PAX_JSON_EVENT_CPP
