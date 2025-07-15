#ifndef HTTP_REQUEST_CPP
#define HTTP_REQUEST_CPP

#include "request.hpp"

HTTP_Request_Writer
http_request_writer_init(Arena* arena, uptr length)
{
    HTTP_Request_Writer result = {};

    result.buffer = buf8_reserve(arena, length);

    return result;
}

void
http_request_writer_clear(HTTP_Request_Writer* self)
{
    buf8_clear(&self->buffer);

    self->line = 0;
    self->body = 0;
}

b32
http_request_write(HTTP_Request_Writer* self, Socket_TCP session)
{
    return socket_tcp_write(session, &self->buffer);
}

b32
http_request_write_start(HTTP_Request_Writer* self, str8 method, str8 resource, str8 version)
{
    if (self->line != 0) return 0;

    buf8_write_str8_tail(&self->buffer, method);
    buf8_write_str8_tail(&self->buffer, SPACE);
    buf8_write_str8_tail(&self->buffer, resource);
    buf8_write_str8_tail(&self->buffer, SPACE);
    buf8_write_str8_tail(&self->buffer, version);
    buf8_write_str8_tail(&self->buffer, CRLF);

    self->line += 1;

    return 1;
}

b32
http_request_write_header(HTTP_Request_Writer* self, str8 key, str8 value)
{
    if (self->body != 0) return 0;

    buf8_write_str8_tail(&self->buffer, key);
    buf8_write_str8_tail(&self->buffer, COLON);
    buf8_write_str8_tail(&self->buffer, SPACE);
    buf8_write_str8_tail(&self->buffer, value);
    buf8_write_str8_tail(&self->buffer, CRLF);

    self->line += 1;

    return 1;
}

b32
http_request_write_content(HTTP_Request_Writer* self, buf8* buffer)
{
    if (self->body == 0)
        buf8_write_str8_tail(&self->buffer, CRLF);

    buf8_write_tail(&self->buffer, buffer);

    self->body  = 1;
    self->line += 1;

    return 1;
}

HTTP_Request_Reader
http_request_reader_init(Arena* arena, uptr length)
{
    HTTP_Request_Reader result = {};

    result.buffer = buf8_reserve(arena, length);

    return result;
}

void
http_request_reader_clear(HTTP_Request_Reader* self)
{
    buf8_clear(&self->buffer);

    self->line = 0;
    self->body = 0;
}

b32
http_request_read(HTTP_Request_Reader* self, Socket_TCP session)
{
    return socket_tcp_read(session, &self->buffer);
}

b32
http_request_read_start(HTTP_Request_Reader* self, str8* method, str8* resource, str8* version)
{
    buf8_normalize(&self->buffer);

    str8 string = str8_make(self->buffer.memory, self->buffer.size);

    if (self->line != 0 || str8_contains(string, CRLF) == 0)
        return 0;

    str8 line   = str8_split_on(string, CRLF, &string);
    str8 left   = {};
    str8 center = {};
    str8 right  = {};

    buf8_drop_head(&self->buffer, line.length + CRLF.length);

    self->line += 1;

    left   = str8_split_on(line, SPACE, &line);
    center = str8_split_on(line, SPACE, &right);

    if (method   != 0) *method   = str8_trim_spaces(left);
    if (resource != 0) *resource = str8_trim_spaces(center);
    if (version  != 0) *version  = str8_trim_spaces(right);

    return 1;
}

b32
http_request_read_header(HTTP_Request_Reader* self, str8* key, str8* value)
{
    buf8_normalize(&self->buffer);

    str8 string = str8_make(self->buffer.memory, self->buffer.size);

    if (self->body != 0 || str8_contains(string, CRLF) == 0)
        return 0;

    str8 line  = str8_split_on(string, CRLF, &string);
    str8 left  = {};
    str8 right = {};

    buf8_drop_head(&self->buffer, line.length + CRLF.length);

    self->line += 1;

    switch (line.length) {
        case 0: { self->body = 1; } break;

        default: {
            left = str8_split_on(line, COLON, &right);

            if (key   != 0) *key   = str8_trim_spaces(left);
            if (value != 0) *value = str8_trim_spaces(right);

            return 1;
        } break;
    }

    return 0;
}

HTTP_Heading
http_request_heading(HTTP_Request_Reader* self, Arena* arena, Socket_TCP session)
{
    HTTP_Heading result =
        hash_map_reserve<str8, str8>(arena, 512, &http_hash_str8);

    while (self->body == 0) {
        if (http_request_read(self, session) == 0) break;

        if (self->line == 0) {
            str8 method   = {};
            str8 resource = {};
            str8 version  = {};

            http_request_read_start(self, &method, &resource, &version);

            hash_map_insert(&result, str8_copy(arena, HTTP_METHOD),
                str8_copy(arena, method));

            hash_map_insert(&result, str8_copy(arena, HTTP_RESOURCE),
                str8_copy(arena, resource));

            hash_map_insert(&result, str8_copy(arena, HTTP_VERSION),
                str8_copy(arena, version));
        }

        while (self->buffer.size > 0) {
            str8 key   = {};
            str8 value = {};

            if (http_request_read_header(self, &key, &value) == 0)
                break;

            hash_map_insert(&result, str8_copy(arena, key),
                str8_copy(arena, value));
        }
    }

    return result;
}

buf8
http_request_content(HTTP_Request_Reader* self, Arena* arena, uptr length, Socket_TCP session)
{
    buf8 result = buf8_reserve(arena, length);

    if (result.length != 0) {
        buf8_write_tail(&result, &self->buffer);

        length -= self->buffer.size;

        while (length > 0) {
            if (http_request_read(self, session) == 0)
                break;

            buf8_write_tail(&result, &self->buffer);

            length -= self->buffer.size;
        }
    }

    return result;
}

#endif // HTTP_REQUEST_CPP
