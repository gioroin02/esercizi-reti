#ifndef PAX_JSON_READER_HPP
#define PAX_JSON_READER_HPP

#include "scanner.hpp"
#include "event.hpp"

namespace pax {

//
// Types
//

struct JSON_Reader
{
    Queue queue  = {};
    buf8* buffer = 0;
    isiz  line   = 0;
    isiz  column = 0;
    str8  name   = {};
    b32   colon  = 0;
    b32   comma  = 0;
};

//
// Procs
//

/* JSON_Reader */

JSON_Reader
json_reader_make(Arena* arena, isiz length, buf8* buffer);

buf8*
json_reader_set_buffer(JSON_Reader* self, buf8* buffer);

JSON_Event
json_reader_event(JSON_Reader* self, Arena* arena);

} // namespace pax

#endif // PAX_JSON_READER_HPP
