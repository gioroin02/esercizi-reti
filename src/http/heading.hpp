#ifndef HTTP_HEADING_HPP
#define HTTP_HEADING_HPP

#include "imports.hpp"
#include "helpers.hpp"

//
// Types
//

using HTTP_Heading = Hash_Map<str8, str8>;

//
// Values
//

static const str8 HTTP_METHOD         = pax_str8("Method");
static const str8 HTTP_METHOD_GET     = pax_str8("GET");
static const str8 HTTP_METHOD_HEAD    = pax_str8("HEAD");
static const str8 HTTP_METHOD_POST    = pax_str8("POST");
static const str8 HTTP_METHOD_PUT     = pax_str8("PUT");
static const str8 HTTP_METHOD_DELETE  = pax_str8("DELETE");
static const str8 HTTP_METHOD_CONNECT = pax_str8("CONNECT");
static const str8 HTTP_METHOD_OPTIONS = pax_str8("OPTIONS");
static const str8 HTTP_METHOD_TRACE   = pax_str8("TRACE");
static const str8 HTTP_METHOD_PATCH   = pax_str8("PATCH");

static const str8 HTTP_RESOURCE = pax_str8("Resource");

static const str8 HTTP_VERSION     = pax_str8("Version");
static const str8 HTTP_VERSION_1_1 = pax_str8("HTTP/1.1");

static const str8 HTTP_STATUS                       = pax_str8("Status");
static const str8 HTTP_STATUS_OK                    = pax_str8("200");
static const str8 HTTP_STATUS_BAD_REQUEST           = pax_str8("400");
static const str8 HTTP_STATUS_METHOD_NOT_ALLOWED    = pax_str8("405");
static const str8 HTTP_STATUS_I_AM_A_TEAPOT         = pax_str8("418");
static const str8 HTTP_STATUS_UNPROCESSABLE_CONTENT = pax_str8("422");

static const str8 HTTP_MESSAGE                       = pax_str8("Message");
static const str8 HTTP_MESSAGE_OK                    = pax_str8("OK");
static const str8 HTTP_MESSAGE_BAD_REQUEST           = pax_str8("Bad Request");
static const str8 HTTP_MESSAGE_METHOD_NOT_ALLOWED    = pax_str8("Method Not Allowed");
static const str8 HTTP_MESSAGE_I_AM_A_TEAPOT         = pax_str8("I'm a teapot");
static const str8 HTTP_MESSAGE_UNPROCESSABLE_CONTENT = pax_str8("Unprocessable Content");

static const str8 HTTP_HEADER_CONTENT_TYPE   = pax_str8("Content-Type");
static const str8 HTTP_HEADER_CONTENT_DISP   = pax_str8("Content-Disposition");
static const str8 HTTP_HEADER_CONTENT_LENGTH = pax_str8("Content-Length");

static const str8 MIME_TEXT_HTML                    = pax_str8("text/html");
static const str8 MIME_APPLICATION_FORM_URL_ENCODED = pax_str8("application/x-www-form-urlencoded");
static const str8 MIME_MULTIPART_FORM_DATA          = pax_str8("multipart/form-data");

//
// Procs
//

str8
http_heading_get_method(HTTP_Heading* self, str8 other);

str8
http_heading_get_resource(HTTP_Heading* self, str8 other);

str8
http_heading_get_version(HTTP_Heading* self, str8 other);

uptr
http_heading_get_status(HTTP_Heading* self, uptr other);

str8
http_heading_get_message(HTTP_Heading* self, str8 other);

HTTP_Heading
http_parse_resource(Arena* arena, str8* string);

str8
http_heading_get_content_type(HTTP_Heading* self, str8 other);

HTTP_Heading
http_parse_content_type(Arena* arena, str8* string);

HTTP_Heading
http_parse_content_disp(Arena* arena, str8* string);

uptr
http_heading_get_content_length(HTTP_Heading* self, uptr other);

HTTP_Heading
http_parse_multipart(Arena* arena, str8* string);

HTTP_Heading
http_parse_url_encoded(Arena* arena, str8 string);

#endif // HTTP_HEADING_HPP
