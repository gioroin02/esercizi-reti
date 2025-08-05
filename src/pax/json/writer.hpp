#ifndef PAX_JSON_WRITER_HPP
#define PAX_JSON_WRITER_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

struct JSON_Writer
{
    Queue queue  = {};
    buf8* buffer = 0;
};

//
// Procs
//

b32
json_writer_make(Arena* arena, isiz length);

buf8*
json_writer_set_buffer(JSON_Writer* self, buf8* buffer);

b32
json_writer_object(JSON_Writer* self);

b32
json_writer_array(JSON_Writer* self);

b32
json_writer_name(JSON_Writer* self, str8 name);

b32
json_writer_stop(JSON_Writer* self);

b32
json_writer_string(JSON_Writer* self);

b32
json_writer_absolute(JSON_Writer* self, usiz value);

b32
json_writer_relative(JSON_Writer* self, isiz value);

b32
json_writer_floating(JSON_Writer* self, f64 value);

b32
json_writer_boolean(JSON_Writer* self, b32 value);

b32
json_writer_null(JSON_Writer* self);

} // namespace pax

#endif // PAX_JSON_WRITER_HPP
