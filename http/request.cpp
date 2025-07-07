#ifndef HTTP_REQUEST_CPP
#define HTTP_REQUEST_CPP

#include "request.hpp"

HTTP_Request_Writer
http_request_writer_init(Arena* arena)
{
    HTTP_Request_Writer result = {};

    result.builder =
        str_builder_make(arena);

    result.body = 0;
    result.line = 0;

    return result;
}

void
http_request_writer_clear(HTTP_Request_Writer* self)
{
    str_builder_clear(&self->builder);

    self->line = 0;
    self->body = 0;
}

b32
http_request_write(HTTP_Request_Writer* self, Socket_TCP session)
{
    Buffer buffer = buffer_from_str_builder(&self->builder);

    str_builder_clear(&self->builder);

    return socket_tcp_write(session, buffer);
}

b32
http_request_write_start(HTTP_Request_Writer* self, str8 method, str8 resource, str8 version)
{
    if (self->line != 0) return 0;

    str_builder_str8(&self->builder, method);
    str_builder_str8(&self->builder, SPACE);
    str_builder_str8(&self->builder, resource);
    str_builder_str8(&self->builder, SPACE);
    str_builder_str8(&self->builder, version);
    str_builder_str8(&self->builder, CRLF);

    self->line += 1;

    return 1;
}

b32
http_request_write_header(HTTP_Request_Writer* self, str8 key, str8 value)
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
http_request_write_content(HTTP_Request_Writer* self, Buffer buffer)
{
    if (self->body == 0)
        str_builder_str8(&self->builder, CRLF);

    str_builder_buffer(&self->builder, buffer);

    self->body  = 1;
    self->line += 1;

    return 1;
}

HTTP_Request_Reader
http_request_reader_init(Arena* arena, uptr length)
{
    HTTP_Request_Reader result = {};

    result.buffer =
        buffer_reserve(arena, length);

    result.length = 0;
    result.offset = 0;
    result.line   = 0;
    result.body   = 0;

    return result;
}

void
http_request_reader_clear(HTTP_Request_Reader* self)
{
    buffer_clear(&self->buffer);

    self->length = 0;
    self->offset = 0;
    self->line   = 0;
    self->body   = 0;
}

b32
http_request_read(HTTP_Request_Reader* self, Socket_TCP session)
{
    if (self->offset < self->buffer.size)
        buffer_slide(&self->buffer, self->offset);

    self->offset = 0;

    return socket_tcp_read(session, &self->buffer);
}

b32
http_request_read_start(HTTP_Request_Reader* self, str8* method, str8* resource, str8* version)
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

    if (method   != 0) *method   = str8_trim_spaces(left);
    if (resource != 0) *resource = str8_trim_spaces(center);
    if (version  != 0) *version  = str8_trim_spaces(right);

    return 1;
}

b32
http_request_read_header(HTTP_Request_Reader* self, str8* key, str8* value)
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
http_request_read_content(HTTP_Request_Reader* self, Buffer* content)
{
    u8*  memory = self->buffer.memory + self->offset;
    uptr length = self->buffer.size   - self->offset;

    str8 string = str8_make(memory, length);

    if (self->body == 0) return 0;

    buffer_encode_str8(content, string);

    return 1;
}

Hash_Map<str8, str8>
http_request_heading(HTTP_Request_Reader* self, Arena* arena, Socket_TCP session)
{
    Hash_Map<str8, str8> result =
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

        while (self->offset < self->buffer.size) {
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

Buffer
http_request_content(HTTP_Request_Reader* self, Arena* arena, uptr length, Socket_TCP session)
{
    Buffer result = buffer_reserve(arena, length);

    if (result.length != 0) {
        buffer_slide(&self->buffer, self->offset);

        length -= self->buffer.size;

        buffer_encode_buffer(&result, self->buffer);
        buffer_clear(&self->buffer);

        while (length > 0) {
            if (http_request_read(self, session) == 0) break;

            length -= self->buffer.size;

            buffer_encode_buffer(&result, self->buffer);
            buffer_clear(&self->buffer);
        }
    }

    return result;
}

str8
http_heading_get_content_type(Hash_Map<str8, str8>* self, str8 other)
{
    return hash_map_get_or(self, HTTP_HEADER_CONTENT_TYPE, other);
}

uptr
http_heading_get_content_length(Hash_Map<str8, str8>* self, uptr other)
{
    str8 string = {};
    u64  result = other;

    if (hash_map_get(self, HTTP_HEADER_CONTENT_LENGTH, &string) == 0)
        return other;

    Format_Spec spec = format_spec(10, FORMAT_FLAG_NONE);

    if (str8_parse_u64(string, spec, &result) == 0)
        return other;

    return result;
}

#endif // HTTP_REQUEST_CPP
