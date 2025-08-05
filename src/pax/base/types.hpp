#ifndef PAX_BASE_TYPES_HPP
#define PAX_BASE_TYPES_HPP

#include "platform.hpp"

#define __pax_string__(expr)        # expr
#define __pax_concat__(left, right) left ## right

//
// Defines
//

#define pax_string(expr)        __pax_string__(expr)
#define pax_concat(left, right) __pax_concat__(left, right)

#define pax_as(type, expr) ((type) (expr))

#define pax_as_f64(expr)  pax_as(pax::f64, expr)
#define pax_as_f64p(expr) pax_as(pax::f64*, expr)
#define pax_as_f32(expr)  pax_as(pax::f32, expr)
#define pax_as_f32p(expr) pax_as(pax::f32*, expr)

#define pax_as_u64(expr)  pax_as(pax::u64, expr)
#define pax_as_u64p(expr) pax_as(pax::u64*, expr)
#define pax_as_u32(expr)  pax_as(pax::u32, expr)
#define pax_as_u32p(expr) pax_as(pax::u32*, expr)
#define pax_as_u16(expr)  pax_as(pax::u16, expr)
#define pax_as_u16p(expr) pax_as(pax::u16*, expr)
#define pax_as_u8(expr)   pax_as(pax::u8, expr)
#define pax_as_u8p(expr)  pax_as(pax::u8*, expr)

#define pax_as_usiz(expr)  pax_as(pax::usiz, expr)
#define pax_as_usizp(expr) pax_as(pax::usiz*, expr)

#define pax_as_i64(expr)  pax_as(pax::i64, expr)
#define pax_as_i64p(expr) pax_as(pax::i64*, expr)
#define pax_as_i32(expr)  pax_as(pax::i32, expr)
#define pax_as_i32p(expr) pax_as(pax::i32*, expr)
#define pax_as_i16(expr)  pax_as(pax::i16, expr)
#define pax_as_i16p(expr) pax_as(pax::i16*, expr)
#define pax_as_i8(expr)   pax_as(pax::i8, expr)
#define pax_as_i8p(expr)  pax_as(pax::i8*, expr)

#define pax_as_isiz(expr)  pax_as(pax::isiz, expr)
#define pax_as_isizp(expr) pax_as(pax::isiz*, expr)

#define pax_as_b64(expr)  pax_as(pax::b64, expr)
#define pax_as_b64p(expr) pax_as(pax::b64*, expr)
#define pax_as_b32(expr)  pax_as(pax::b32, expr)
#define pax_as_b32p(expr) pax_as(pax::b32*, expr)
#define pax_as_b16(expr)  pax_as(pax::b16, expr)
#define pax_as_b16p(expr) pax_as(pax::b16*, expr)
#define pax_as_b8(expr)   pax_as(pax::b8, expr)
#define pax_as_b8p(expr)  pax_as(pax::b8*, expr)

#define pax_as_voidp(expr) pax_as(void*, expr)

#define pax_null(type) pax_as(type*, 0)

#define pax_size_of(type) pax_as_isiz(sizeof(type))

#define pax_array_bytes(array)  pax_size_of(array)
#define pax_array_stride(array) pax_size_of((array)[0])

#define pax_array_length(array) \
    (pax_array_bytes(array) / pax_array_stride(array))

#define pax_min(x, y) ((x) < (y) ? (x) : (y))
#define pax_max(x, y) ((x) < (y) ? (y) : (x))

#define pax_limit(x, y, z) pax_min(pax_max(x, y), z)

namespace pax {

//
// Types
//

#if PAX_ARCH == PAX_ARCH_64

    using f64  = double;
    using f32  = float;

    using u64  = unsigned long long;
    using u32  = unsigned int;
    using u16  = unsigned short;
    using u8   = unsigned char;
    using usiz = u64;

    using i64  = long long;
    using i32  = int;
    using i16  = short;
    using i8   = char;
    using isiz = i64;

    using b64  = u64;
    using b32  = u32;
    using b16  = u16;
    using b8   = u8;

#else

    #error "Architecture not supported or unknown"

#endif

// Procs

/* Absolute value */

usiz
abs_isiz(isiz value);

u64
abs_i64(i64 value);

u32
abs_i32(i32 value);

u16
abs_i16(i16 value);

u8
abs_i8(i8 value);

/* Sign */

b32
sign_isiz(isiz value);

b32
sign_i64(i64 value);

b32
sign_i32(i32 value);

b32
sign_i16(i16 value);

b32
sign_i8(i8 value);

} // namespace pax

#endif // PAX_BASE_TYPES_HPP
