#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "imports.hpp"
#include "heading.hpp"

//
// Types
//

struct HTTP_Response_Writer
{
    buf8 buffer = {};

    usiz line = 0;
    usiz body = 0;
};

struct HTTP_Response_Reader
{
    buf8 buffer = {};

    usiz line = 0;
    usiz body = 0;
};

//
// Procs
//

/* HTTP_Response_Writer */

HTTP_Response_Writer
http_response_writer_init(Arena* arena, usiz length);

void
http_response_writer_clear(HTTP_Response_Writer* self);

b32
http_response_write(HTTP_Response_Writer* self, Socket_TCP session);

b32
http_response_write_start(HTTP_Response_Writer* self, str8 version, str8 status, str8 message);

b32
http_response_write_header(HTTP_Response_Writer* self, str8 key, str8 value);

usiz
http_response_write_content(HTTP_Response_Writer* self, buf8* content);

usiz
http_response_write_content_str8(HTTP_Response_Writer* self, str8 content);

/* HTTP_Response_Reader */

HTTP_Response_Reader
http_response_reader_init(Arena* arena, usiz length);

void
http_response_reader_clear(HTTP_Response_Reader* self);

b32
http_response_read(HTTP_Response_Reader* self, Socket_TCP session);

b32
http_response_read_start(HTTP_Response_Reader* self, str8* version, str8* status, str8* message);

b32
http_response_read_header(HTTP_Response_Reader* self, str8* key, str8* value);

/* Helpers */

HTTP_Heading
http_response_heading(HTTP_Response_Reader* self, Arena* arena, Socket_TCP session);

buf8
http_response_content(HTTP_Response_Reader* self, Arena* arena, usiz length, Socket_TCP session);

#endif // HTTP_RESPONSE_HPP
