#ifndef PAX_FORMAT_OPTIONS_CPP
#define PAX_FORMAT_OPTIONS_CPP

#include "options.hpp"

namespace pax {

Format_Options
format_options(i8 radix, usiz flags)
{
    Format_Options result = {};

    if (radix >= 2) {
        result.flags = flags;
        result.radix = radix;
    }

    return result;
}

Format_Options
format_options_simple(i8 radix)
{
    Format_Options result = {};

    if (radix >= 2)
        result.radix = radix;

    return result;
}

} // namespace pax

#endif // PAX_FORMAT_OPTIONS_CPP
