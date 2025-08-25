#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "imports.hpp"
#include "heading.hpp"

//
// Types
//

struct HTTP_Request_Writer
{
    buf8 buffer = {};

    usiz line = 0;
    usiz body = 0;
};

struct HTTP_Request_Reader
{
    buf8 buffer = {};

    usiz line = 0;
    usiz body = 0;
};

//
// Procs
//

/* HTTP_Request_Writer */

HTTP_Request_Writer
http_request_writer_init(Arena* arena, usiz length);

void
http_request_writer_clear(HTTP_Request_Writer* self);

b32
http_request_write(HTTP_Request_Writer* self, Socket_TCP session);

b32
http_request_write_start(HTTP_Request_Writer* self, str8 method, str8 resource, str8 version);

b32
http_request_write_header(HTTP_Request_Writer* self, str8 key, str8 value);

usiz
http_request_write_content(HTTP_Request_Writer* self, buf8* content);

usiz
http_request_write_content_str8(HTTP_Request_Writer* self, str8 content);

/* HTTP_Request_Reader */

HTTP_Request_Reader
http_request_reader_init(Arena* arena, usiz length);

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

buf8
http_request_content(HTTP_Request_Reader* self, Arena* arena, usiz length, Socket_TCP session);

#endif // HTTP_REQUEST_H
