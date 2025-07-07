#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP

#include "imports.hpp"

static const str8 HTTP_METHOD        = pax_str8("Method");
static const str8 HTTP_METHOD_GET    = pax_str8("GET");
static const str8 HTTP_METHOD_POST   = pax_str8("POST");
static const str8 HTTP_METHOD_PUT    = pax_str8("PUT");
static const str8 HTTP_METHOD_DELETE = pax_str8("DELETE");

static const str8 HTTP_RESOURCE = pax_str8("Resource");

static const str8 HTTP_VERSION     = pax_str8("Version");
static const str8 HTTP_VERSION_1_1 = pax_str8("HTTP/1.1");

static const str8 HTTP_STATUS_200 = pax_str8("200");

static const str8 HTTP_MESSAGE_OK = pax_str8("OK");

static const str8 HTTP_HEADER_CONTENT_TYPE   = pax_str8("Content-Type");
static const str8 HTTP_HEADER_CONTENT_DISP   = pax_str8("Content-Disposition");
static const str8 HTTP_HEADER_CONTENT_LENGTH = pax_str8("Content-Length");

static const str8 MIME_TEXT_HTML                          = pax_str8("text/html");
static const str8 MIME_APPPLICATION_X_WWW_FORM_URLENCODED = pax_str8("application/x-www-form-urlencoded");
static const str8 MIME_MULTIPART_FORM_DATA                = pax_str8("multipart/form-data");

#endif // HTTP_HEADERS_HPP
