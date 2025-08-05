#ifndef HTTP_HELPERS_HPP
#define HTTP_HELPERS_HPP

#include "imports.hpp"

//
// Values
//

static const str8 CRLF  = pax_str8("\r\n");
static const str8 SPACE = pax_str8(" ");
static const str8 COLON = pax_str8(":");

//
// Procs
//

usiz
http_hash_str8(str8 key);

#endif // HTTP_HELPERS_HPP
