#include "common.hpp"

#include <stdio.h>

static const str8 HTTP_RESPONSE_OK = pax_str8("HTTP/1.1 200 OK\r\n\r\n");

static const str8 HTTP_HEADER_METHOD         = pax_str8("Method");
static const str8 HTTP_HEADER_RESOURCE       = pax_str8("Resource");
static const str8 HTTP_HEADER_RESOURCE_ARGS  = pax_str8("Resource-Args");
static const str8 HTTP_HEADER_VERSION        = pax_str8("Version");
static const str8 HTTP_HEADER_CONTENT_TYPE   = pax_str8("Content-Type");
static const str8 HTTP_HEADER_CONTENT_DISP   = pax_str8("Content-Disposition");
static const str8 HTTP_HEADER_CONTENT_LENGTH = pax_str8("Content-Length");

static const str8 MIME_TEXT_HTML            = pax_str8("text/html");
static const str8 MIME_APP_FORM_URL_ENCODED = pax_str8("application/x-www-form-urlencoded");
static const str8 MIME_MPART_FORM_DATA      = pax_str8("multipart/form-data");

uptr
hash_str8(str8 key)
{
    uptr p = 31;
    uptr m = 1e9 + 1;

    uptr power = 1;

    uptr result = 0;

    for (uptr i = 0; i < key.length; i += 1) {
        uptr temp =
            (key.memory[i] - ASCII_LOWER_A + 1) * power;

        result = (result + temp) % m;
        power  = (power  * p)    % m;
    }

    return result;
}

str8
headers_get_method(Hash_Map<str8, str8>* headers)
{
    str8 result = {};

    if (hash_map_get(headers, HTTP_HEADER_METHOD, &result) == 0)
        return result;

    return result;
}

str8
headers_get_resource(Hash_Map<str8, str8>* headers)
{
    str8 result = {};

    if (hash_map_get(headers, HTTP_HEADER_RESOURCE, &result) == 0)
        return result;

    return result;
}

Hash_Map<str8, str8>
headers_get_resource_args(Hash_Map<str8, str8>* headers, Arena* arena)
{
    Hash_Map<str8, str8> result =
        hash_map_reserve<str8, str8>(arena, 64, &hash_str8);

    str8 string = {};

    if (hash_map_get(headers, HTTP_HEADER_RESOURCE_ARGS, &string) == 0)
        return result;

    str8 pair  = {};
    str8 key   = {};
    str8 value = {};

    while (string.length != 0) {
        pair = str8_split_on(string, pax_str8("&"), &string);
        key  = str8_split_on(pair, pax_str8("="), &value);

        key   = str8_trim_spaces(key);
        value = str8_trim_spaces(value);

        hash_map_insert(&result, str8_copy(arena, key),
            str8_copy(arena, value));
    }

    return result;
}

str8
headers_get_version(Hash_Map<str8, str8>* headers)
{
    str8 result = {};

    if (hash_map_get(headers, HTTP_HEADER_VERSION, &result) == 0)
        return result;

    return result;
}

Hash_Map<str8, str8>
headers_get_content_type(Hash_Map<str8, str8>* headers, Arena* arena, str8* type)
{
    Hash_Map<str8, str8> result =
        hash_map_reserve<str8, str8>(arena, 64, &hash_str8);

    str8 string = {};

    if (hash_map_get(headers, HTTP_HEADER_CONTENT_TYPE, &string) == 0)
        return result;

    str8 left  = {};
    str8 right = {};

    left = str8_split_on(string, pax_str8(";"), &right);

    if (type != 0) *type = str8_trim_spaces(left);

    right = str8_trim_spaces(right);

    str8 pair  = {};
    str8 key   = {};
    str8 value = {};

    while (right.length != 0) {
        pair = str8_split_on(right, pax_str8(";"), &right);
        key  = str8_split_on(pair, pax_str8("="), &value);

        key   = str8_trim_spaces(key);
        value = str8_trim_spaces(value);

        hash_map_insert(&result, str8_copy(arena, key),
            str8_copy(arena, value));
    }

    return result;
}

uptr
headers_get_content_length(Hash_Map<str8, str8>* headers, uptr other)
{
    Format_Spec spec = format_spec(10,
        FORMAT_FLAG_LEADING_ZERO | FORMAT_FLAG_LEADING_PLUS);

    str8 string = {};
    uptr result = other;

    if (hash_map_get(headers, HTTP_HEADER_CONTENT_LENGTH, &string) == 0)
        return result;

    if (string.length != 0)
        str8_parse_u64(string, spec, &result);

    return result;
}

Hash_Map<str8, str8>
content_multipart_form_data(str8 content, Arena* arena, str8* data)
{
    Hash_Map<str8, str8> result =
        hash_map_reserve<str8, str8>(arena, 64, &hash_str8);

    str8 left  = {};
    str8 right = {};

    left = str8_split_on(content, pax_str8("\r\n\r\n"), &right);

    left  = str8_trim_spaces(left);
    right = str8_trim_spaces(right);

    if (data != 0) *data = str8_copy(arena, right);

    str8 pair  = {};
    str8 key   = {};
    str8 value = {};

    while (left.length != 0) {
        pair = str8_split_on(left, pax_str8("\r\n"), &left);
        key  = str8_split_on(pair, pax_str8(":"), &value);

        key   = str8_trim_spaces(key);
        value = str8_trim_spaces(value);

        hash_map_insert(&result, str8_copy(arena, key),
            str8_copy(arena, value));
    }

    return result;
}

Hash_Map<str8, str8>
headers_get_content_disp(Hash_Map<str8, str8>* headers, Arena* arena, str8* disp)
{
    Hash_Map<str8, str8> result =
        hash_map_reserve<str8, str8>(arena, 64, &hash_str8);

    str8 string = {};

    if (hash_map_get(headers, HTTP_HEADER_CONTENT_DISP, &string) == 0)
        return result;

    str8 left  = {};
    str8 right = {};

    left = str8_split_on(string, pax_str8(";"), &right);

    if (disp != 0) *disp = str8_trim_spaces(left);

    right = str8_trim_spaces(right);

    str8 pair  = {};
    str8 key   = {};
    str8 value = {};

    while (right.length != 0) {
        pair = str8_split_on(right, pax_str8(";"), &right);
        key  = str8_split_on(pair, pax_str8("="), &value);

        key   = str8_trim_spaces(key);
        value = str8_trim_spaces(value);

        hash_map_insert(&result, str8_copy(arena, key),
            str8_copy(arena, value));
    }

    return result;
}

int
main()
{
    Arena arena = system_reserve(128);

    HTTP_Request request  = http_request_reserve(&arena, MEMORY_KIB / 2);
    Buffer       response = buffer_reserve(&arena, 16 * MEMORY_KIB);

    Address server_addr = address_any(ADDRESS_KIND_IP4);

    if (system_network_start() == 0) return 1;

    Socket_TCP server = server_start(&arena, SERVER_PORT, server_addr);

    if (server == 0) return 1;

    uptr offset = arena_offset(&arena);

    while (1) {
        Socket_TCP session = session_open(server, &arena);

        Hash_Map<str8, str8> headers =
            hash_map_reserve<str8, str8>(&arena, 1024, &hash_str8);

        /* Head */

        b32 body = 0;

        while (body == 0) {
            if (http_request_read(&request, session) == 0) break;

            if (request.line == 0) {
                str8 method        = {};
                str8 resource      = {};
                str8 resource_args = {};
                str8 version       = {};

                http_request_method(&request, &method);
                http_request_resource(&request, &resource, &resource_args);
                http_request_version(&request, &version);

                hash_map_insert(&headers, str8_copy(&arena, HTTP_HEADER_METHOD),
                    str8_copy(&arena, method));

                hash_map_insert(&headers, str8_copy(&arena, HTTP_HEADER_RESOURCE),
                    str8_copy(&arena, resource));

                hash_map_insert(&headers, str8_copy(&arena, HTTP_HEADER_RESOURCE_ARGS),
                    str8_copy(&arena, resource_args));

                hash_map_insert(&headers, str8_copy(&arena, HTTP_HEADER_VERSION),
                    str8_copy(&arena, version));
            }

            while (request.offset < request.buffer.size) {
                str8 key   = {};
                str8 value = {};

                if (http_request_header(&request, &key, &value, &body) == 0)
                    break;

                hash_map_insert(&headers, str8_copy(&arena, key),
                    str8_copy(&arena, value));
            }
        }

        str8 content_type = {};

        Hash_Map<str8, str8> content_args =
            headers_get_content_type(&headers, &arena, &content_type);

        Buffer content_data = buffer_reserve(&arena,
            headers_get_content_length(&headers, 0));

        /* Body */

        if (content_data.length != 0) {
            uptr payload = 0;

            buffer_slide(&request.buffer, request.offset);

            payload += request.buffer.size;

            buffer_encode_buffer(&content_data, request.buffer);
            buffer_clear(&request.buffer);

            while (payload < content_data.length) {
                if (http_request_read(&request, session) == 0) break;

                payload += request.buffer.size;

                buffer_encode_buffer(&content_data, request.buffer);
                buffer_clear(&request.buffer);
            }
        }

        /* Debug info */

        printf(INFO " Headers (%llu):\n", headers.inner.size);

        for (uptr i = 0; i < headers.inner.size; i += 1) {
            str8 key   = array_get_or(&headers.key,   i, pax_str8("<empty>"));
            str8 value = array_get_or(&headers.value, i, pax_str8("<empty>"));

            printf(DEBUG "     - " YLW("'%.*s'") " => " PRP("'%.*s'") "\n",
                pax_cast(int, key.length), key.memory,
                pax_cast(int, value.length), value.memory);
        }

        str8 method   = headers_get_method(&headers);
        str8 resource = headers_get_resource(&headers);
        str8 version  = headers_get_version(&headers);

        Hash_Map<str8, str8> resource_args = headers_get_resource_args(&headers, &arena);

        printf(INFO " Resource Args (%llu):\n", resource_args.inner.size);

        for (uptr i = 0; i < resource_args.inner.size; i += 1) {
            str8 key   = array_get_or(&resource_args.key,   i, pax_str8("<empty>"));
            str8 value = array_get_or(&resource_args.value, i, pax_str8("<empty>"));

            printf(DEBUG "     - " YLW("'%.*s'") " => " PRP("'%.*s'") "\n",
                pax_cast(int, key.length), key.memory,
                pax_cast(int, value.length), value.memory);
        }

        printf(INFO " Content (%llu):\n", content_data.length);

        if (content_data.length != 0) {
            printf(DEBUG "     - " PRP("'%.*s'") "\n",
                pax_cast(int, content_type.length), content_type.memory);
        }

        buffer_encode_str8(&response, HTTP_RESPONSE_OK);

        str8 path      = pax_str8("./data/http");
        str8 index     = pax_str8("index.html");
        str8 not_found = pax_str8("not_found.html");

        printf(INFO " Requested resource " PRP("'%.*s'") "\n",
            pax_cast(int, resource.length), resource.memory);

        resource = str8_trim_prefix(resource, pax_str8("/"));

        if (resource.length == 0) resource = index;

        File_Props props = {};

        if (file_props(&props, &arena, path, resource) == 0) {
            resource = not_found;

            file_props(&props, &arena, path, resource);
        }

        uptr size = file_size(&props);

        printf(INFO " Responding with content of file " PRP("'%.*s/%.*s'") " " YLW("%llu") "\n",
            pax_cast(int, path.length), path.memory,
            pax_cast(int, resource.length), resource.memory, size);

        if (file_is_dir(&props) == 0) {
            File   file    = file_open(&arena, path, resource, FILE_PERM_READ);
            Buffer content = buffer_reserve(&arena, size);

            if (file != 0)
                file_read(file, &content);

            buffer_encode_buffer(&response, content);

            file_close(file);
        }

        if (str8_is_equal(method, pax_str8("POST")) != 0) {
            if (str8_is_equal(content_type, MIME_MPART_FORM_DATA) != 0) {
                str8 boundary_start = hash_map_get_or(&content_args,
                    pax_str8("boundary"), pax_str8(""));

                str8 boundary_stop = {};

                boundary_start = str8_append(&arena, pax_str8("--"), boundary_start);
                boundary_stop  = str8_append(&arena, boundary_start, pax_str8("--"));

                str8 payload = str8_make(content_data.memory, content_data.size);

                payload = str8_slice_since_first(payload, boundary_start);
                payload = str8_slice_until_first(payload, boundary_stop);
                payload = str8_trim_spaces(payload);

                Hash_Map<str8, str8> payload_args =
                    content_multipart_form_data(payload, &arena, &payload);

                printf(INFO " Payload args (%llu):\n", payload_args.inner.size);

                for (uptr i = 0; i < payload_args.inner.size; i += 1) {
                    str8 key   = array_get_or(&payload_args.key,   i, pax_str8("<empty>"));
                    str8 value = array_get_or(&payload_args.value, i, pax_str8("<empty>"));

                    printf(DEBUG "     - " YLW("'%.*s'") " => " PRP("'%.*s'") "\n",
                        pax_cast(int, key.length), key.memory,
                        pax_cast(int, value.length), value.memory);
                }

                str8 content_disp = {};

                Hash_Map<str8, str8> content_disp_args =
                    headers_get_content_disp(&payload_args, &arena, &content_disp);

                printf(INFO " Content Disp args (%llu):\n", content_disp_args.inner.size);

                for (uptr i = 0; i < content_disp_args.inner.size; i += 1) {
                    str8 key   = array_get_or(&content_disp_args.key,   i, pax_str8("<empty>"));
                    str8 value = array_get_or(&content_disp_args.value, i, pax_str8("<empty>"));

                    printf(DEBUG "     - " YLW("'%.*s'") " => " PRP("'%.*s'") "\n",
                        pax_cast(int, key.length), key.memory,
                        pax_cast(int, value.length), value.memory);
                }

                str8 name = {};

                if (hash_map_get(&content_disp_args, pax_str8("filename"), &name) != 0) {
                    name = str8_slice_since_first(name, pax_str8("\""));
                    name = str8_slice_until_first(name, pax_str8("\""));

                    File   file = file_open_new(&arena, path, name, FILE_PERM_WRITE);
                    Buffer temp = buffer_make_full(payload.memory, payload.length);

                    printf(TRACE " %p\n", file);

                    if (file != 0)
                        file_write(file, temp);

                    file_close(file);

                    printf(TRACE " PAYLOAD = [%.*s]\n", pax_cast(int, payload.length),
                        payload.memory);
                }
            }
        }

        session_write(session, response);
        session_close(session);

        http_request_clear(&request);

        buffer_clear(&response);

        arena_rewind(&arena, offset);
    }

    server_stop(server);

    system_network_stop();
}