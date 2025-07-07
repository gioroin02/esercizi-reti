#ifndef PAX_FORMAT_FORMAT_SPEC_CPP
#define PAX_FORMAT_FORMAT_SPEC_CPP

#include "format_spec.hpp"

namespace pax {

Format_Spec
format_spec(uptr base, uptr flags)
{
    Format_Spec result = {};

    result.base  = base;
    result.flags = flags;

    return result;
}

} // namespace pax

#endif // PAX_FORMAT_FORMAT_SPEC_CPP
