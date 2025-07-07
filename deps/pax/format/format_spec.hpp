#ifndef PAX_FORMAT_FORMAT_SPEC_HPP
#define PAX_FORMAT_FORMAT_SPEC_HPP

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

struct Format_Spec
{
    uptr flags = FORMAT_FLAG_NONE;
    uptr base  = 10;
};

//
// Procs
//

/* Format_Spec */

Format_Spec
format_spec(uptr base, uptr flags);

} // namespace pax

#endif // PAX_FORMAT_FORMAT_SPEC_HPP
