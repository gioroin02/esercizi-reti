#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "imports.hpp"
#include "helpers.hpp"

//
// Types
//

struct HTTP_Response_Writer
{
    Str_Builder builder = {};

    uptr line = 0;
    uptr body = 0;
};

struct HTTP_Response_Reader
{
    Buffer buffer = {};

    uptr length = 0;
    uptr offset = 0;
    uptr line   = 0;
    uptr body   = 0;
};

//
// Procs
//

/* HTTP_Response_Writer */

HTTP_Response_Writer
http_response_writer_init(Arena* arena);

void
http_response_writer_clear(HTTP_Response_Writer* self);

b32
http_response_write(HTTP_Response_Writer* self, Socket_TCP session);

b32
http_response_write_start(HTTP_Response_Writer* self, str8 version, str8 status, str8 message);

b32
http_response_write_header(HTTP_Response_Writer* self, str8 key, str8 value);

b32
http_response_write_content(HTTP_Response_Writer* self, Buffer content);

/* HTTP_Response_Reader */

HTTP_Response_Reader
http_response_reader_init(Arena* arena, uptr length);

void
http_response_reader_clear(HTTP_Response_Reader* self);

b32
http_response_read(HTTP_Response_Reader* self, Socket_TCP session);

b32
http_response_read_start(HTTP_Response_Reader* self, str8* version, str8* status, str8* message);

b32
http_response_read_header(HTTP_Response_Reader* self, str8* key, str8* value);

b32
http_response_read_content(HTTP_Response_Reader *self, Buffer* content);

#endif // HTTP_RESPONSE_HPP
