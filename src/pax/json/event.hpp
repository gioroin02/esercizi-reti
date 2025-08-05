#ifndef PAX_JSON_EVENT_HPP
#define PAX_JSON_EVENT_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

enum JSON_Event_Type
{
    JSON_EVENT_NONE,
    JSON_EVENT_NAME,
    JSON_EVENT_STOP,
    JSON_EVENT_STRING,
    JSON_EVENT_ABSOLUTE,
    JSON_EVENT_RELATIVE,
    JSON_EVENT_FLOATING,
    JSON_EVENT_BOOLEAN,
    JSON_EVENT_NULL,
    JSON_EVENT_ERROR,
    JSON_EVENT_COUNT,
};

enum JSON_Group_Type
{
    JSON_GROUP_NONE,
    JSON_GROUP_OBJECT,
    JSON_GROUP_ARRAY,
};

struct JSON_Event_Error
{
    str8 message = {};
    str8 content = {};
    isiz line    = 0;
    isiz column  = 0;
};

struct JSON_Event
{
    JSON_Event_Type type  = JSON_EVENT_NONE;
    JSON_Group_Type group = JSON_GROUP_NONE;

    str8 name = {};

    union
    {
        JSON_Event_Error error;

        str8 string;
        usiz absolute;
        isiz relative;
        f64  floating;
        b32  boolean;
    };
};

//
// Procs
//

/* JSON_Event */

JSON_Event
json_event_none();

JSON_Event
json_event_object(JSON_Event value, str8 name);

JSON_Event
json_event_array(JSON_Event value);

JSON_Event
json_event_name(str8 name);

JSON_Event
json_event_stop();

JSON_Event
json_event_string(str8 value);

JSON_Event
json_event_absolute(usiz value);

JSON_Event
json_event_relative(isiz value);

JSON_Event
json_event_floating(f64 value);

JSON_Event
json_event_boolean(b32 value);

JSON_Event
json_event_null();

JSON_Event
json_event_error(Arena* arena, str8 message, str8 content, isiz line, isiz column);

JSON_Event
json_event_count();

} // namespace pax

#endif // PAX_JSON_EVENT_HPP
