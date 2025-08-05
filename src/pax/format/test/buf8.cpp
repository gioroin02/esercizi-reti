#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

#define FORE_RESET  "\x1b[0m"
#define FORE_RED    "\x1b[31m"
#define FORE_GREEN  "\x1b[32m"
#define FORE_YELLOW "\x1b[33m"
#define FORE_BLUE   "\x1b[34m"
#define FORE_PURPLE "\x1b[35m"
#define FORE_AZURE  "\x1b[36m"

#define RED(expr)    FORE_RED    expr FORE_RESET
#define GREEN(expr)  FORE_GREEN  expr FORE_RESET
#define YELLOW(expr) FORE_YELLOW expr FORE_RESET
#define BLUE(expr)   FORE_BLUE   expr FORE_RESET
#define PURPLE(expr) FORE_PURPLE expr FORE_RESET
#define AZURE(expr)  FORE_AZURE  expr FORE_RESET

#define TRUE  GREEN("T")
#define FALSE RED("F")

void
show_buf8_write_usiz_tail(buf8* buffer, Format_Options options, usiz value)
{
    b32 state = buf8_write_usiz_tail(buffer, options, value);

    printf("write (" PURPLE("%llu") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u64_tail(buf8* buffer, Format_Options options, u64 value)
{
    b32 state = buf8_write_u64_tail(buffer, options, value);

    printf("write (" PURPLE("%llu") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u32_tail(buf8* buffer, Format_Options options, u32 value)
{
    b32 state = buf8_write_u32_tail(buffer, options, value);

    printf("write (" PURPLE("%u") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u16_tail(buf8* buffer, Format_Options options, u16 value)
{
    b32 state = buf8_write_u16_tail(buffer, options, value);

    printf("write (" PURPLE("%u") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u8_tail(buf8* buffer, Format_Options options, u8 value)
{
    b32 state = buf8_write_u8_tail(buffer, options, value);

    printf("write (" PURPLE("%u") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_usiz_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    usiz value = 0;
    b32  state = buf8_read_usiz_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%llu") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u64_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u64 value = 0;
    b32 state = buf8_read_u64_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%llu") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u32_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u32 value = 0;
    b32 state = buf8_read_u32_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%u") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u16_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u16 value = 0;
    b32 state = buf8_read_u16_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%u") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u8_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u8  value = 0;
    b32 state = buf8_read_u8_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%u") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_usiz(buf8* self, Format_Options options, usiz value)
{
    show_buf8_write_usiz_tail(self, options, value);
    show_buf8_read_usiz_head(self, options);
}

void
show_buf8_u64(buf8* self, Format_Options options, u64 value)
{
    show_buf8_write_u64_tail(self, options, value);
    show_buf8_read_u64_head(self, options);
}

void
show_buf8_u32(buf8* self, Format_Options options, u32 value)
{
    show_buf8_write_u32_tail(self, options, value);
    show_buf8_read_u32_head(self, options);
}

void
show_buf8_u16(buf8* self, Format_Options options, u16 value)
{
    show_buf8_write_u16_tail(self, options, value);
    show_buf8_read_u16_head(self, options);
}

void
show_buf8_u8(buf8* self, Format_Options options, u8 value)
{
    show_buf8_write_u8_tail(self, options, value);
    show_buf8_read_u8_head(self, options);
}

void
show_buf8_usiz_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_usiz_head(self, options);
}

void
show_buf8_u64_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u64_head(self, options);
}

void
show_buf8_u32_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u32_head(self, options);
}

void
show_buf8_u16_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u16_head(self, options);
}

void
show_buf8_u8_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u8_head(self, options);
}

void
show_buf8_write_isiz_tail(buf8* buffer, Format_Options options, isiz value)
{
    b32 state = buf8_write_isiz_tail(buffer, options, value);

    printf("write (" PURPLE("%lli") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i64_tail(buf8* buffer, Format_Options options, i64 value)
{
    b32 state = buf8_write_i64_tail(buffer, options, value);

    printf("write (" PURPLE("%lli") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i32_tail(buf8* buffer, Format_Options options, i32 value)
{
    b32 state = buf8_write_i32_tail(buffer, options, value);

    printf("write (" PURPLE("%i") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i16_tail(buf8* buffer, Format_Options options, i16 value)
{
    b32 state = buf8_write_i16_tail(buffer, options, value);

    printf("write (" PURPLE("%i") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i8_tail(buf8* buffer, Format_Options options, i8 value)
{
    b32 state = buf8_write_i8_tail(buffer, options, value);

    printf("write (" PURPLE("%i") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_isiz_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    isiz value = 0;
    b32  state = buf8_read_isiz_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%lli") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i64_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i64 value = 0;
    b32 state = buf8_read_i64_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%lli") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i32_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i32 value = 0;
    b32 state = buf8_read_i32_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%i") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i16_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i16 value = 0;
    b32 state = buf8_read_i16_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%i") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i8_head(buf8* buffer, Format_Options options)
{
    printf("read (" FORE_BLUE "'");

    for (isiz i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i8  value = 0;
    b32 state = buf8_read_i8_head(buffer, options, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%i") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_isiz(buf8* self, Format_Options options, isiz value)
{
    show_buf8_write_isiz_tail(self, options, value);
    show_buf8_read_isiz_head(self, options);
}

void
show_buf8_i64(buf8* self, Format_Options options, i64 value)
{
    show_buf8_write_i64_tail(self, options, value);
    show_buf8_read_i64_head(self, options);
}

void
show_buf8_i32(buf8* self, Format_Options options, i32 value)
{
    show_buf8_write_i32_tail(self, options, value);
    show_buf8_read_i32_head(self, options);
}

void
show_buf8_i16(buf8* self, Format_Options options, i16 value)
{
    show_buf8_write_i16_tail(self, options, value);
    show_buf8_read_i16_head(self, options);
}

void
show_buf8_i8(buf8* self, Format_Options options, i8 value)
{
    show_buf8_write_i8_tail(self, options, value);
    show_buf8_read_i8_head(self, options);
}

void
show_buf8_isiz_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_isiz_head(self, options);
}

void
show_buf8_i64_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i64_head(self, options);
}

void
show_buf8_i32_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i32_head(self, options);
}

void
show_buf8_i16_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i16_head(self, options);
}

void
show_buf8_i8_from_str8(buf8* self, Format_Options options, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i8_head(self, options);
}

static u8 memory[MEMORY_KIB] = {};

int
main()
{
    Arena arena  = arena_make(memory, MEMORY_KIB);
    buf8  buffer = buf8_reserve(&arena, 256);

    Format_Options options = format_options(10, FORMAT_FLAG_LEADING_PLUS);

    printf("VALID:\n");

    show_buf8_usiz(&buffer, options, USIZ_MAX);
    show_buf8_usiz(&buffer, options, USIZ_MIN);

    show_buf8_usiz_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("255"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("256"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("65535"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("65536"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("4294967295"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("4294967296"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("18446744073709551615"));

    printf("\nINVALID:\n");

    show_buf8_usiz_from_str8(&buffer, options, pax_str8("18446744073709551616"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("-1"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("+0001"));
    show_buf8_usiz_from_str8(&buffer, options, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_isiz(&buffer, options, ISIZ_MAX);
    show_buf8_isiz(&buffer, options, ISIZ_MIN);

    show_buf8_isiz_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("+0"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("127"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("128"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-128"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-129"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("32767"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("32768"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-32768"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-32769"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("2147483647"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("2147483648"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-2147483648"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-2147483649"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("9223372036854775807"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-9223372036854775808"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_isiz_from_str8(&buffer, options, pax_str8("9223372036854775808"));
    show_buf8_isiz_from_str8(&buffer, options, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_u64(&buffer, options, U64_MAX);
    show_buf8_u64(&buffer, options, U64_MIN);

    show_buf8_u64_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("255"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("256"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("65535"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("65536"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("4294967295"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("4294967296"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("18446744073709551615"));

    printf("\nINVALID:\n");

    show_buf8_u64_from_str8(&buffer, options, pax_str8("18446744073709551616"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("-1"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("+0001"));
    show_buf8_u64_from_str8(&buffer, options, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i64(&buffer, options, I64_MAX);
    show_buf8_i64(&buffer, options, I64_MIN);

    show_buf8_i64_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("+0"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("127"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("128"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-128"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-129"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("32767"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("32768"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-32768"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-32769"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("2147483647"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("2147483648"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-2147483648"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-2147483649"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("9223372036854775807"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-9223372036854775808"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i64_from_str8(&buffer, options, pax_str8("9223372036854775808"));
    show_buf8_i64_from_str8(&buffer, options, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);
    printf("\nVALID:\n");

    show_buf8_u32(&buffer, options, U32_MAX);
    show_buf8_u32(&buffer, options, U32_MIN);

    show_buf8_u32_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("255"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("256"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("65535"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("65536"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("4294967295"));

    printf("\nINVALID:\n");

    show_buf8_u32_from_str8(&buffer, options, pax_str8("4294967296"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("18446744073709551615"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("18446744073709551616"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("-1"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("+0001"));
    show_buf8_u32_from_str8(&buffer, options, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i32(&buffer, options, I32_MAX);
    show_buf8_i32(&buffer, options, I32_MIN);

    show_buf8_i32_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("+0"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("127"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("128"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-128"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-129"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("32767"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("32768"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-32768"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-32769"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("2147483647"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-2147483648"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i32_from_str8(&buffer, options, pax_str8("2147483648"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-2147483649"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("9223372036854775807"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("9223372036854775808"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-9223372036854775808"));
    show_buf8_i32_from_str8(&buffer, options, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_u16(&buffer, options, U16_MAX);
    show_buf8_u16(&buffer, options, U16_MIN);

    show_buf8_u16_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("255"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("256"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("65535"));

    printf("\nINVALID:\n");

    show_buf8_u16_from_str8(&buffer, options, pax_str8("65536"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("4294967295"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("4294967296"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("18446744073709551615"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("18446744073709551616"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("-1"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("+0001"));
    show_buf8_u16_from_str8(&buffer, options, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i16(&buffer, options, I16_MAX);
    show_buf8_i16(&buffer, options, I16_MIN);

    show_buf8_i16_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("+0"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("127"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("128"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-128"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-129"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("32767"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-32768"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i16_from_str8(&buffer, options, pax_str8("32768"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-32769"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("2147483647"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("2147483648"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-2147483648"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-2147483649"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("9223372036854775807"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("9223372036854775808"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-9223372036854775808"));
    show_buf8_i16_from_str8(&buffer, options, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_u8(&buffer, options, U8_MAX);
    show_buf8_u8(&buffer, options, U8_MIN);

    show_buf8_u8_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("255"));

    printf("\nINVALID:\n");

    show_buf8_u8_from_str8(&buffer, options, pax_str8("256"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("65535"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("65536"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("4294967295"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("4294967296"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("18446744073709551615"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("18446744073709551616"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("-1"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("+0001"));
    show_buf8_u8_from_str8(&buffer, options, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i8(&buffer, options, I8_MAX);
    show_buf8_i8(&buffer, options, I8_MIN);

    show_buf8_i8_from_str8(&buffer, options, pax_str8("1"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("+1"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("0"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("+0"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("127"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-128"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i8_from_str8(&buffer, options, pax_str8("128"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-129"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("32767"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("32768"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-32768"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-32769"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("2147483647"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("2147483648"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-2147483648"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-2147483649"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("9223372036854775807"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("9223372036854775808"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-9223372036854775808"));
    show_buf8_i8_from_str8(&buffer, options, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);
}
