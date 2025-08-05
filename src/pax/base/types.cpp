#ifndef PAX_BASE_TYPES_CPP
#define PAX_BASE_TYPES_CPP

#include "types.hpp"

namespace pax {

usiz
abs_isiz(isiz value)
{
    if (value < 0)
        return -pax_as_usiz(value);

    return pax_as_usiz(value);
}

u64
abs_i64(i64 value)
{
    if (value < 0)
        return -pax_as_u64(value);

    return pax_as_u64(value);
}

u32
abs_i32(i32 value)
{
    if (value < 0)
        return -pax_as_u32(value);

    return pax_as_u32(value);
}

u16
abs_i16(i16 value)
{
    if (value < 0)
        return -pax_as_u16(value);

    return pax_as_u16(value);
}

u8
abs_i8(i8 value)
{
    if (value < 0)
        return -pax_as_u8(value);

    return pax_as_u8(value);
}

b32
sign_isiz(isiz value)
{
    if (value < 0)
        return 1;

    return 0;
}

b32
sign_i64(i64 value)
{
    if (value < 0)
        return 1;

    return 0;
}

b32
sign_i32(i32 value)
{
    if (value < 0)
        return 1;

    return 0;
}

b32
sign_i16(i16 value)
{
    if (value < 0)
        return 1;

    return 0;
}

b32
sign_i8(i8 value)
{
    if (value < 0)
        return 1;

    return 0;
}

} // namespace pax

#endif // PAX_BASE_TYPES_CPP
