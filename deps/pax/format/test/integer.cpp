#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GRN(str) "\x1b[32m" str "\x1b[0m"
#define YLW(str) "\x1b[33m" str "\x1b[0m"
#define BLU(str) "\x1b[34m" str "\x1b[0m"
#define PRP(str) "\x1b[35m" str "\x1b[0m"
#define AZR(str) "\x1b[36m" str "\x1b[0m"

#define TRUE  GRN("T")
#define FALSE RED("F")

void
show_str8_parse_i64(Format_Spec spec, str8 string)
{
    i64 value = 0;
    b32 state = str8_parse_i64(string, spec, &value);

    printf("i64(" PRP("'%24.*s'") ") -> %s | %lli\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_parse_i32(Format_Spec spec, str8 string)
{
    i32 value = 0;
    b32 state = str8_parse_i32(string, spec, &value);

    printf("i32(" PRP("'%24.*s'") ") -> %s | %li\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_parse_i16(Format_Spec spec, str8 string)
{
    i16 value = 0;
    b32 state = str8_parse_i16(string, spec, &value);

    printf("i16(" PRP("'%24.*s'") ") -> %s | %i\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_parse_i8(Format_Spec spec, str8 string)
{
    i8  value = 0;
    b32 state = str8_parse_i8(string, spec, &value);

    printf("i8(" PRP("'%24.*s'") ") -> %s | %i\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

int
main()
{
    Format_Spec spec = {};

    spec.base  = 10;
    spec.flags = FORMAT_FLAG_LEADING_ZERO |
                 FORMAT_FLAG_LEADING_PLUS;

    show_str8_parse_i64(spec, pax_str8("1"));
    show_str8_parse_i64(spec, pax_str8("+1"));
    show_str8_parse_i64(spec, pax_str8("0"));
    show_str8_parse_i64(spec, pax_str8("+0"));
    show_str8_parse_i64(spec, pax_str8("127"));
    show_str8_parse_i64(spec, pax_str8("128"));
    show_str8_parse_i64(spec, pax_str8("-128"));
    show_str8_parse_i64(spec, pax_str8("-129"));
    show_str8_parse_i64(spec, pax_str8("32767"));
    show_str8_parse_i64(spec, pax_str8("32768"));
    show_str8_parse_i64(spec, pax_str8("-32768"));
    show_str8_parse_i64(spec, pax_str8("-32769"));
    show_str8_parse_i64(spec, pax_str8("2147483647"));
    show_str8_parse_i64(spec, pax_str8("2147483648"));
    show_str8_parse_i64(spec, pax_str8("-2147483648"));
    show_str8_parse_i64(spec, pax_str8("-2147483649"));
    show_str8_parse_i64(spec, pax_str8("9223372036854775807"));
    show_str8_parse_i64(spec, pax_str8("9223372036854775808"));
    show_str8_parse_i64(spec, pax_str8("-9223372036854775808"));
    show_str8_parse_i64(spec, pax_str8("-9223372036854775809"));
    show_str8_parse_i64(spec, pax_str8("-150"));

    printf("\n");

    show_str8_parse_i32(spec, pax_str8("1"));
    show_str8_parse_i32(spec, pax_str8("+1"));
    show_str8_parse_i32(spec, pax_str8("0"));
    show_str8_parse_i32(spec, pax_str8("+0"));
    show_str8_parse_i32(spec, pax_str8("127"));
    show_str8_parse_i32(spec, pax_str8("128"));
    show_str8_parse_i32(spec, pax_str8("-128"));
    show_str8_parse_i32(spec, pax_str8("-129"));
    show_str8_parse_i32(spec, pax_str8("32767"));
    show_str8_parse_i32(spec, pax_str8("32768"));
    show_str8_parse_i32(spec, pax_str8("-32768"));
    show_str8_parse_i32(spec, pax_str8("-32769"));
    show_str8_parse_i32(spec, pax_str8("2147483647"));
    show_str8_parse_i32(spec, pax_str8("2147483648"));
    show_str8_parse_i32(spec, pax_str8("-2147483648"));
    show_str8_parse_i32(spec, pax_str8("-2147483649"));
    show_str8_parse_i32(spec, pax_str8("9223372036854775807"));
    show_str8_parse_i32(spec, pax_str8("9223372036854775808"));
    show_str8_parse_i32(spec, pax_str8("-9223372036854775808"));
    show_str8_parse_i32(spec, pax_str8("-9223372036854775809"));
    show_str8_parse_i32(spec, pax_str8("-150"));

    printf("\n");

    show_str8_parse_i16(spec, pax_str8("1"));
    show_str8_parse_i16(spec, pax_str8("+1"));
    show_str8_parse_i16(spec, pax_str8("0"));
    show_str8_parse_i16(spec, pax_str8("+0"));
    show_str8_parse_i16(spec, pax_str8("127"));
    show_str8_parse_i16(spec, pax_str8("128"));
    show_str8_parse_i16(spec, pax_str8("-128"));
    show_str8_parse_i16(spec, pax_str8("-129"));
    show_str8_parse_i16(spec, pax_str8("32767"));
    show_str8_parse_i16(spec, pax_str8("32768"));
    show_str8_parse_i16(spec, pax_str8("-32768"));
    show_str8_parse_i16(spec, pax_str8("-32769"));
    show_str8_parse_i16(spec, pax_str8("2147483647"));
    show_str8_parse_i16(spec, pax_str8("2147483648"));
    show_str8_parse_i16(spec, pax_str8("-2147483648"));
    show_str8_parse_i16(spec, pax_str8("-2147483649"));
    show_str8_parse_i16(spec, pax_str8("9223372036854775807"));
    show_str8_parse_i16(spec, pax_str8("9223372036854775808"));
    show_str8_parse_i16(spec, pax_str8("-9223372036854775808"));
    show_str8_parse_i16(spec, pax_str8("-9223372036854775809"));
    show_str8_parse_i16(spec, pax_str8("-150"));

    printf("\n");

    show_str8_parse_i8(spec, pax_str8("1"));
    show_str8_parse_i8(spec, pax_str8("+1"));
    show_str8_parse_i8(spec, pax_str8("0"));
    show_str8_parse_i8(spec, pax_str8("+0"));
    show_str8_parse_i8(spec, pax_str8("127"));
    show_str8_parse_i8(spec, pax_str8("128"));
    show_str8_parse_i8(spec, pax_str8("-128"));
    show_str8_parse_i8(spec, pax_str8("-129"));
    show_str8_parse_i8(spec, pax_str8("32767"));
    show_str8_parse_i8(spec, pax_str8("32768"));
    show_str8_parse_i8(spec, pax_str8("-32768"));
    show_str8_parse_i8(spec, pax_str8("-32769"));
    show_str8_parse_i8(spec, pax_str8("2147483647"));
    show_str8_parse_i8(spec, pax_str8("2147483648"));
    show_str8_parse_i8(spec, pax_str8("-2147483648"));
    show_str8_parse_i8(spec, pax_str8("-2147483649"));
    show_str8_parse_i8(spec, pax_str8("9223372036854775807"));
    show_str8_parse_i8(spec, pax_str8("9223372036854775808"));
    show_str8_parse_i8(spec, pax_str8("-9223372036854775808"));
    show_str8_parse_i8(spec, pax_str8("-9223372036854775809"));
    show_str8_parse_i8(spec, pax_str8("-150"));

    printf("\n");

    spec.base = 2;

    show_str8_parse_i8(spec, pax_str8("1101"));
    show_str8_parse_i8(spec, pax_str8("01111111"));
    show_str8_parse_i8(spec, pax_str8("10000000"));
    show_str8_parse_i8(spec, pax_str8("-10000000"));
    show_str8_parse_i8(spec, pax_str8("-10000001"));
}
