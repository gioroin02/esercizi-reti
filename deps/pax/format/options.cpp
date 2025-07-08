#ifndef PAX_FORMAT_OPTIONS_CPP
#define PAX_FORMAT_OPTIONS_CPP

#include "options.hpp"

namespace pax {

Format_Options
format_options(uptr base, uptr flags)
{
    Format_Options result = {};

    result.base  = base;
    result.flags = flags;

    return result;
}

} // namespace pax

#endif // PAX_FORMAT_OPTIONS_CPP
