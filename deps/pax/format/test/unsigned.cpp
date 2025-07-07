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
show_str8_parse_u64(Format_Spec spec, str8 string)
{
    u64 value = 0;
    b32 state = str8_parse_u64(string, spec, &value);

    printf("u64(" PRP("'%24.*s'") ") -> %s | %llu\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_parse_u32(Format_Spec spec, str8 string)
{
    u32 value = 0;
    b32 state = str8_parse_u32(string, spec, &value);

    printf("u32(" PRP("'%24.*s'") ") -> %s | %lu\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_parse_u16(Format_Spec spec, str8 string)
{
    u16 value = 0;
    b32 state = str8_parse_u16(string, spec, &value);

    printf("u16(" PRP("'%24.*s'") ") -> %s | %u\n",
        pax_cast(int, string.length), string.memory,
        state ? TRUE : FALSE, value);
}

void
show_str8_parse_u8(Format_Spec spec, str8 string)
{
    u8  value = 0;
    b32 state = str8_parse_u8(string, spec, &value);

    printf("u8(" PRP("'%24.*s'") ") -> %s | %u\n",
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

    show_str8_parse_u64(spec, pax_str8("1"));
    show_str8_parse_u64(spec, pax_str8("+1"));
    show_str8_parse_u64(spec, pax_str8("0"));
    show_str8_parse_u64(spec, pax_str8("+0001"));
    show_str8_parse_u64(spec, pax_str8("01"));
    show_str8_parse_u64(spec, pax_str8("255"));
    show_str8_parse_u64(spec, pax_str8("256"));
    show_str8_parse_u64(spec, pax_str8("65535"));
    show_str8_parse_u64(spec, pax_str8("65536"));
    show_str8_parse_u64(spec, pax_str8("4294967295"));
    show_str8_parse_u64(spec, pax_str8("4294967296"));
    show_str8_parse_u64(spec, pax_str8("18446744073709551615"));
    show_str8_parse_u64(spec, pax_str8("18446744073709551616"));
    show_str8_parse_u64(spec, pax_str8("-150"));

    printf("\n");

    show_str8_parse_u32(spec, pax_str8("1"));
    show_str8_parse_u32(spec, pax_str8("+1"));
    show_str8_parse_u32(spec, pax_str8("0"));
    show_str8_parse_u32(spec, pax_str8("+0"));
    show_str8_parse_u32(spec, pax_str8("255"));
    show_str8_parse_u32(spec, pax_str8("256"));
    show_str8_parse_u32(spec, pax_str8("65535"));
    show_str8_parse_u32(spec, pax_str8("65536"));
    show_str8_parse_u32(spec, pax_str8("4294967295"));
    show_str8_parse_u32(spec, pax_str8("4294967296"));
    show_str8_parse_u32(spec, pax_str8("18446744073709551615"));
    show_str8_parse_u32(spec, pax_str8("18446744073709551616"));
    show_str8_parse_u32(spec, pax_str8("-150"));

    printf("\n");

    show_str8_parse_u16(spec, pax_str8("1"));
    show_str8_parse_u16(spec, pax_str8("+1"));
    show_str8_parse_u16(spec, pax_str8("0"));
    show_str8_parse_u16(spec, pax_str8("+0"));
    show_str8_parse_u16(spec, pax_str8("255"));
    show_str8_parse_u16(spec, pax_str8("256"));
    show_str8_parse_u16(spec, pax_str8("65535"));
    show_str8_parse_u16(spec, pax_str8("65536"));
    show_str8_parse_u16(spec, pax_str8("4294967295"));
    show_str8_parse_u16(spec, pax_str8("4294967296"));
    show_str8_parse_u16(spec, pax_str8("18446744073709551615"));
    show_str8_parse_u16(spec, pax_str8("18446744073709551616"));
    show_str8_parse_u16(spec, pax_str8("-150"));

    printf("\n");

    show_str8_parse_u8(spec, pax_str8("1"));
    show_str8_parse_u8(spec, pax_str8("+1"));
    show_str8_parse_u8(spec, pax_str8("0"));
    show_str8_parse_u8(spec, pax_str8("+0"));
    show_str8_parse_u8(spec, pax_str8("255"));
    show_str8_parse_u8(spec, pax_str8("256"));
    show_str8_parse_u8(spec, pax_str8("65535"));
    show_str8_parse_u8(spec, pax_str8("65536"));
    show_str8_parse_u8(spec, pax_str8("4294967295"));
    show_str8_parse_u8(spec, pax_str8("4294967296"));
    show_str8_parse_u8(spec, pax_str8("18446744073709551615"));
    show_str8_parse_u8(spec, pax_str8("18446744073709551616"));
    show_str8_parse_u8(spec, pax_str8("-150"));

    printf("\n");

    spec.base = 2;

    show_str8_parse_u8(spec, pax_str8("1101"));
    show_str8_parse_u8(spec, pax_str8("11111111"));
    show_str8_parse_u8(spec, pax_str8("111111110"));
}
