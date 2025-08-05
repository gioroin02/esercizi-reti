#ifndef PAX_BASE_CONST_HPP
#define PAX_BASE_CONST_HPP

#include "types.hpp"

namespace pax {

//
// Values
//

/* Sizes */

static const isiz F64_SIZE  = pax_size_of(f64);
static const isiz F32_SIZE  = pax_size_of(f32);

static const isiz U64_SIZE  = pax_size_of(u64);
static const isiz U32_SIZE  = pax_size_of(u32);
static const isiz U16_SIZE  = pax_size_of(u16);
static const isiz U8_SIZE   = pax_size_of(u8);
static const isiz USIZ_SIZE = pax_size_of(usiz);

static const isiz I64_SIZE  = pax_size_of(i64);
static const isiz I32_SIZE  = pax_size_of(i32);
static const isiz I16_SIZE  = pax_size_of(i16);
static const isiz I8_SIZE   = pax_size_of(i8);
static const isiz ISIZ_SIZE = pax_size_of(isiz);

static const isiz B64_SIZE  = pax_size_of(b64);
static const isiz B32_SIZE  = pax_size_of(b32);
static const isiz B16_SIZE  = pax_size_of(b16);
static const isiz B8_SIZE   = pax_size_of(b8);

static const isiz VOIDP_SIZE = pax_size_of(void*);

/* Floating 64 */

static const u64 __F64_ZERO__     = 0x0000000000000000;
static const u64 __F64_ZERO_POS__ = 0x0000000000000000;
static const u64 __F64_ZERO_NEG__ = 0x8000000000000000;
static const u64 __F64_INF__      = 0x7ff0000000000000;
static const u64 __F64_INF_POS__  = 0x7ff0000000000000;
static const u64 __F64_INF_NEG__  = 0xfff0000000000000;
static const u64 __F64_NAN__      = 0x7ff8000000000000;
static const u64 __F64_NAN_POS__  = 0x7ff8000000000000;
static const u64 __F64_NAN_NEG__  = 0xfff8000000000000;

static const f64 F64_ZERO     = *pax_as_f64p(&__F64_ZERO__);
static const f64 F64_ZERO_POS = *pax_as_f64p(&__F64_ZERO_POS__);
static const f64 F64_ZERO_NEG = *pax_as_f64p(&__F64_ZERO_NEG__);
static const f64 F64_INF      = *pax_as_f64p(&__F64_INF__);
static const f64 F64_INF_POS  = *pax_as_f64p(&__F64_INF_POS__);
static const f64 F64_INF_NEG  = *pax_as_f64p(&__F64_INF_NEG__);
static const f64 F64_NAN      = *pax_as_f64p(&__F64_NAN__);
static const f64 F64_NAN_POS  = *pax_as_f64p(&__F64_NAN_POS__);
static const f64 F64_NAN_NEG  = *pax_as_f64p(&__F64_NAN_NEG__);

static const u64 F64_MASK_FRAC = 0x000fffffffffffff;
static const u64 F64_MASK_EXP  = 0x7ff0000000000000;
static const u64 F64_MASK_SIGN = 0x8000000000000000;

static const u64 F64_SIZE_FRAC = 52;
static const u64 F64_SIZE_EXP  = 11;
static const u64 F64_SIGE_SIGN = 1;

static const i32 F64_EXP_BIAS =  1023; // 16 + 16 bits
static const i32 F64_EXP_MAX  =  1023; // 16 + 16 bits
static const i32 F64_EXP_MIN  = -1022; // 16 + 16 bits

/* Floating 32 */

static const u32 __F32_ZERO__     = 0x00000000;
static const u32 __F32_ZERO_POS__ = 0x00000000;
static const u32 __F32_ZERO_NEG__ = 0x80000000;
static const u32 __F32_INF__      = 0x7f800000;
static const u32 __F32_INF_POS__  = 0x7f800000;
static const u32 __F32_INF_NEG__  = 0xff800000;
static const u32 __F32_NAN__      = 0x7fc00000;
static const u32 __F32_NAN_POS__  = 0x7fc00000;
static const u32 __F32_NAN_NEG__  = 0xffc00000;

static const f32 F32_ZERO     = *pax_as_f32p(&__F32_ZERO__);
static const f32 F32_ZERO_POS = *pax_as_f32p(&__F32_ZERO_POS__);
static const f32 F32_ZERO_NEG = *pax_as_f32p(&__F32_ZERO_NEG__);
static const f32 F32_INF      = *pax_as_f32p(&__F32_INF__);
static const f32 F32_INF_POS  = *pax_as_f32p(&__F32_INF_POS__);
static const f32 F32_INF_NEG  = *pax_as_f32p(&__F32_INF_NEG__);
static const f32 F32_NAN      = *pax_as_f32p(&__F32_NAN__);
static const f32 F32_NAN_POS  = *pax_as_f32p(&__F32_NAN_POS__);
static const f32 F32_NAN_NEG  = *pax_as_f32p(&__F32_NAN_NEG__);

static const u32 F32_MASK_FRAC = 0x007fffff;
static const u32 F32_MASK_EXP  = 0x7f800000;
static const u32 F32_MASK_SIGN = 0x80000000;

static const u32 F32_SIZE_FRAC = 23;
static const u32 F32_SIZE_EXP  = 8;
static const u32 F32_SIZE_SIGN = 1;

static const i16 F32_EXP_BIAS =  127; // 8 + 8 bits
static const i16 F32_EXP_MAX  =  127; // 8 + 8 bits
static const i16 F32_EXP_MIN  = -126; // 8 + 8 bits

/* Absolute 64 */

static const u64 U64_MAX  = 0xffffffffffffffff;
static const u64 U64_MIN  = 0x0000000000000000;
static const u64 U64_ZERO = 0x0000000000000000;

/* Absolute 32 */

static const u32 U32_MAX  = 0xffffffff;
static const u32 U32_MIN  = 0x00000000;
static const u32 U32_ZERO = 0x00000000;

/* Absolute 16 */

static const u16 U16_MAX  = 0xffff;
static const u16 U16_MIN  = 0x0000;
static const u16 U16_ZERO = 0x0000;

/* Absolute 8 */

static const u8 U8_MAX  = 0xff;
static const u8 U8_MIN  = 0x00;
static const u8 U8_ZERO = 0x00;

/* Relative 64 */

static const i64 I64_MAX  = 0x7fffffffffffffff;
static const i64 I64_MIN  = 0x8000000000000000;
static const i64 I64_ZERO = 0x0000000000000000;

/* Relative 32 */

static const i32 I32_MAX  = 0x7fffffff;
static const i32 I32_MIN  = 0x80000000;
static const i32 I32_ZERO = 0x00000000;

/* Relative 16 */

static const i16 I16_MAX  = 0x7fff;
static const i16 I16_MIN  = 0x8000;
static const i16 I16_ZERO = 0x0000;

/* Relative 8 */

static const i8 I8_MAX  = 0x7f;
static const i8 I8_MIN  = 0x80;
static const i8 I8_ZERO = 0x00;

/* Boolean 64 */

static const b64 B64_FALSE = 0;

/* Boolean 32 */

static const b32 B32_FALSE = 0;

/* Boolean 16 */

static const b16 B16_FALSE = 0;

/* Boolean 8 */

static const b8 B8_FALSE = 0;

/* Platform dependent */

#if PAX_ARCH == PAX_ARCH_64

    static const usiz USIZ_MAX  = U64_MAX;
    static const usiz USIZ_MIN  = U64_MIN;
    static const usiz USIZ_ZERO = U64_ZERO;

    static const isiz ISIZ_MAX  = I64_MAX;
    static const isiz ISIZ_MIN  = I64_MIN;
    static const isiz ISIZ_ZERO = I64_ZERO;

#else

    #error "Architecture not supported or unknown"

#endif

} // namespace pax

#endif // PAX_BASE_CONST_HPP
