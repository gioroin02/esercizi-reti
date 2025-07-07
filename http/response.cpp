#ifndef HTTP_RESPONSE_CPP
#define HTTP_RESPONSE_CPP

#include "response.hpp"

HTTP_Response_Writer
http_response_writer_init(Arena* arena)
{
    HTTP_Response_Writer result = {};

    result.builder =
        str_builder_make(arena);

    result.body = 0;
    result.line = 0;

    return result;
}

void
http_response_writer_clear(HTTP_Response_Writer* self)
{
    str_builder_clear(&self->builder);

    self->line = 0;
    self->body = 0;
}

b32
http_response_write(HTTP_Response_Writer* self, Socket_TCP session)
{
    Buffer buffer = buffer_from_str_builder(&self->builder);

    str_builder_clear(&self->builder);

    return socket_tcp_write(session, buffer);
}

b32
http_response_write_start(HTTP_Response_Writer* self, str8 version, str8 status, str8 message)
{
    if (self->line != 0) return 0;

    str_builder_str8(&self->builder, version);
    str_builder_str8(&self->builder, SPACE);
    str_builder_str8(&self->builder, status);
    str_builder_str8(&self->builder, SPACE);
    str_builder_str8(&self->builder, message);
    str_builder_str8(&self->builder, CRLF);

    self->line += 1;

    return 1;
}

b32
http_response_write_header(HTTP_Response_Writer* self, str8 key, str8 value)
{
    if (self->body != 0) return 0;

    str_builder_str8(&self->builder, key);
    str_builder_str8(&self->builder, COLON);
    str_builder_str8(&self->builder, SPACE);
    str_builder_str8(&self->builder, value);
    str_builder_str8(&self->builder, CRLF);

    self->line += 1;

    return 1;
}

b32
http_response_write_content(HTTP_Response_Writer* self, Buffer buffer)
{
    if (self->body == 0)
        str_builder_str8(&self->builder, CRLF);

    str_builder_buffer(&self->builder, buffer);

    self->body  = 1;
    self->line += 1;

    return 1;
}

HTTP_Response_Reader
http_response_reader_init(Arena* arena, uptr length)
{
    HTTP_Response_Reader result = {};

    result.buffer =
        buffer_reserve(arena, length);

    result.length = 0;
    result.offset = 0;
    result.line   = 0;
    result.body   = 0;

    return result;
}

void
http_response_reader_clear(HTTP_Response_Reader* self)
{
    buffer_clear(&self->buffer);

    self->length = 0;
    self->offset = 0;
    self->line   = 0;
    self->body   = 0;
}

b32
http_response_read(HTTP_Response_Reader* self, Socket_TCP session)
{
    if (self->offset < self->buffer.size)
        buffer_slide(&self->buffer, self->offset);

    self->offset = 0;

    return socket_tcp_read(session, &self->buffer);
}

b32
http_response_read_start(HTTP_Response_Reader* self, str8* version, str8* status, str8* message)
{
    u8*  memory = self->buffer.memory + self->offset;
    uptr length = self->buffer.size   - self->offset;

    str8 string = str8_make(memory, length);

    if (self->line != 0 || str8_contains(string, CRLF) == 0) return 0;

    str8 line   = str8_split_on(string, CRLF, &string);
    str8 left   = {};
    str8 center = {};
    str8 right  = {};

    self->length += line.length + CRLF.length;
    self->offset += line.length + CRLF.length;
    self->line   += 1;

    left   = str8_split_on(line, SPACE, &line);
    center = str8_split_on(line, SPACE, &right);

    if (version != 0) *version = str8_trim_spaces(left);
    if (status  != 0) *status  = str8_trim_spaces(center);
    if (message != 0) *message = str8_trim_spaces(right);

    return 1;
}

b32
http_response_read_header(HTTP_Response_Reader* self, str8* key, str8* value)
{
    u8*  memory = self->buffer.memory + self->offset;
    uptr length = self->buffer.size   - self->offset;

    str8 string = str8_make(memory, length);

    if (self->body != 0 || str8_contains(string, CRLF) == 0) return 0;

    str8 line  = str8_split_on(string, CRLF, &string);
    str8 left  = {};
    str8 right = {};

    self->length += line.length + CRLF.length;
    self->offset += line.length + CRLF.length;
    self->line   += 1;

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

b32
http_response_read_content(HTTP_Response_Reader* self, Buffer* content)
{
    u8*  memory = self->buffer.memory + self->offset;
    uptr length = self->buffer.size   - self->offset;

    str8 string = str8_make(memory, length);

    if (self->body == 0) return 0;

    buffer_encode_str8(content, string);

    return 1;
}

#endif // HTTP_RESPONSE_CPP
