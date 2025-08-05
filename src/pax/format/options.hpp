#ifndef PAX_FORMAT_OPTIONS_HPP
#define PAX_FORMAT_OPTIONS_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

enum Format_Flag
{
    FORMAT_FLAG_NONE         = 0x0,
    FORMAT_FLAG_LEADING_ZERO = 0x1,
    FORMAT_FLAG_LEADING_PLUS = 0x2,
};

struct Format_Options
{
    i8   radix = 10;
    usiz flags = FORMAT_FLAG_NONE;
};

//
// Procs
//

/* Format_Options */

Format_Options
format_options(i8 radix, usiz flags);

Format_Options
format_options_simple(i8 radix);

} // namespace pax

#endif // PAX_FORMAT_OPTIONS_HPP
