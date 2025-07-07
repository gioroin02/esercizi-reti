#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "imports.hpp"
#include "heading.hpp"

//
// Types
//

struct HTTP_Request_Writer
{
    Str_Builder builder = {};

    uptr line = 0;
    uptr body = 0;
};

struct HTTP_Request_Reader
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

/* HTTP_Request_Writer */

HTTP_Request_Writer
http_request_writer_init(Arena* arena);

void
http_request_writer_clear(HTTP_Request_Writer* self);

b32
http_request_write(HTTP_Request_Writer* self, Socket_TCP session);

b32
http_request_write_start(HTTP_Request_Writer* self, str8 method, str8 resource, str8 version);

b32
http_request_write_header(HTTP_Request_Writer* self, str8 key, str8 value);

b32
http_request_write_content(HTTP_Request_Writer* self, Buffer content);

/* HTTP_Request_Reader */

HTTP_Request_Reader
http_request_reader_init(Arena* arena, uptr length);

void
http_request_reader_clear(HTTP_Request_Reader* self);

b32
http_request_read(HTTP_Request_Reader* self, Socket_TCP session);

b32
http_request_read_start(HTTP_Request_Reader* self, str8* method, str8* resource, str8* version);

b32
http_request_read_header(HTTP_Request_Reader* self, str8* key, str8* value);

/* Helpers */

HTTP_Heading
http_request_heading(HTTP_Request_Reader* self, Arena* arena, Socket_TCP session);

Buffer
http_request_content(HTTP_Request_Reader* self, Arena* arena, uptr length, Socket_TCP session);

#endif // HTTP_REQUEST_HPP
