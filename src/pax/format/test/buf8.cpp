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
show_buf8_write_uptr_tail(buf8* buffer, Format_Options opts, uptr value)
{
    b32 state = buf8_write_uptr_tail(buffer, opts, value);

    printf("write (" PURPLE("%llu") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u64_tail(buf8* buffer, Format_Options opts, u64 value)
{
    b32 state = buf8_write_u64_tail(buffer, opts, value);

    printf("write (" PURPLE("%llu") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u32_tail(buf8* buffer, Format_Options opts, u32 value)
{
    b32 state = buf8_write_u32_tail(buffer, opts, value);

    printf("write (" PURPLE("%u") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u16_tail(buf8* buffer, Format_Options opts, u16 value)
{
    b32 state = buf8_write_u16_tail(buffer, opts, value);

    printf("write (" PURPLE("%u") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_u8_tail(buf8* buffer, Format_Options opts, u8 value)
{
    b32 state = buf8_write_u8_tail(buffer, opts, value);

    printf("write (" PURPLE("%u") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_uptr_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    uptr value = 0;
    b32  state = buf8_read_uptr_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%llu") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u64_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u64 value = 0;
    b32 state = buf8_read_u64_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%llu") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u32_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u32 value = 0;
    b32 state = buf8_read_u32_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%u") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u16_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u16 value = 0;
    b32 state = buf8_read_u16_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%u") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_u8_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    u8  value = 0;
    b32 state = buf8_read_u8_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%u") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_uptr(buf8* self, Format_Options opts, uptr value)
{
    show_buf8_write_uptr_tail(self, opts, value);
    show_buf8_read_uptr_head(self, opts);
}

void
show_buf8_u64(buf8* self, Format_Options opts, u64 value)
{
    show_buf8_write_u64_tail(self, opts, value);
    show_buf8_read_u64_head(self, opts);
}

void
show_buf8_u32(buf8* self, Format_Options opts, u32 value)
{
    show_buf8_write_u32_tail(self, opts, value);
    show_buf8_read_u32_head(self, opts);
}

void
show_buf8_u16(buf8* self, Format_Options opts, u16 value)
{
    show_buf8_write_u16_tail(self, opts, value);
    show_buf8_read_u16_head(self, opts);
}

void
show_buf8_u8(buf8* self, Format_Options opts, u8 value)
{
    show_buf8_write_u8_tail(self, opts, value);
    show_buf8_read_u8_head(self, opts);
}

void
show_buf8_uptr_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_uptr_head(self, opts);
}

void
show_buf8_u64_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u64_head(self, opts);
}

void
show_buf8_u32_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u32_head(self, opts);
}

void
show_buf8_u16_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u16_head(self, opts);
}

void
show_buf8_u8_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_u8_head(self, opts);
}

void
show_buf8_write_iptr_tail(buf8* buffer, Format_Options opts, iptr value)
{
    b32 state = buf8_write_iptr_tail(buffer, opts, value);

    printf("write (" PURPLE("%lli") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i64_tail(buf8* buffer, Format_Options opts, i64 value)
{
    b32 state = buf8_write_i64_tail(buffer, opts, value);

    printf("write (" PURPLE("%lli") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i32_tail(buf8* buffer, Format_Options opts, i32 value)
{
    b32 state = buf8_write_i32_tail(buffer, opts, value);

    printf("write (" PURPLE("%i") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i16_tail(buf8* buffer, Format_Options opts, i16 value)
{
    b32 state = buf8_write_i16_tail(buffer, opts, value);

    printf("write (" PURPLE("%i") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_write_i8_tail(buf8* buffer, Format_Options opts, i8 value)
{
    b32 state = buf8_write_i8_tail(buffer, opts, value);

    printf("write (" PURPLE("%i") ") -> ", value);

    printf(FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    printf("'" FORE_RESET);

    printf(" %s \n", state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_iptr_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    iptr value = 0;
    b32  state = buf8_read_iptr_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%lli") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i64_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i64 value = 0;
    b32 state = buf8_read_i64_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%lli") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i32_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i32 value = 0;
    b32 state = buf8_read_i32_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%i") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i16_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i16 value = 0;
    b32 state = buf8_read_i16_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%i") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_read_i8_head(buf8* buffer, Format_Options opts)
{
    printf("read (" FORE_BLUE "'");

    for (uptr i = 0; i < buffer->size; i += 1)
        printf("%c", buffer->memory[(buffer->head + i) % buffer->length]);

    i8  value = 0;
    b32 state = buf8_read_i8_head(buffer, opts, &value);

    printf("'" FORE_RESET ") -> " PURPLE("%i") ", %s\n", value, state != 0 ? TRUE : FALSE);
}

void
show_buf8_iptr(buf8* self, Format_Options opts, iptr value)
{
    show_buf8_write_iptr_tail(self, opts, value);
    show_buf8_read_iptr_head(self, opts);
}

void
show_buf8_i64(buf8* self, Format_Options opts, i64 value)
{
    show_buf8_write_i64_tail(self, opts, value);
    show_buf8_read_i64_head(self, opts);
}

void
show_buf8_i32(buf8* self, Format_Options opts, i32 value)
{
    show_buf8_write_i32_tail(self, opts, value);
    show_buf8_read_i32_head(self, opts);
}

void
show_buf8_i16(buf8* self, Format_Options opts, i16 value)
{
    show_buf8_write_i16_tail(self, opts, value);
    show_buf8_read_i16_head(self, opts);
}

void
show_buf8_i8(buf8* self, Format_Options opts, i8 value)
{
    show_buf8_write_i8_tail(self, opts, value);
    show_buf8_read_i8_head(self, opts);
}

void
show_buf8_iptr_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_iptr_head(self, opts);
}

void
show_buf8_i64_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i64_head(self, opts);
}

void
show_buf8_i32_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i32_head(self, opts);
}

void
show_buf8_i16_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i16_head(self, opts);
}

void
show_buf8_i8_from_str8(buf8* self, Format_Options opts, str8 value)
{
    buf8_clear(self);
    buf8_write_str8_tail(self, value);

    show_buf8_read_i8_head(self, opts);
}

int
main()
{
    u8 memory[MEMORY_KIB] = {};

    Arena arena = pax_arena(memory);

    buf8 buffer = buf8_reserve(&arena, 256);

    Format_Options opts = format_options(10, FORMAT_FLAG_LEADING_PLUS);

    printf("VALID:\n");

    show_buf8_uptr(&buffer, opts, UPTR_MAX);
    show_buf8_uptr(&buffer, opts, UPTR_MIN);

    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("255"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("256"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("65535"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("65536"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("4294967295"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("4294967296"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("18446744073709551615"));

    printf("\nINVALID:\n");

    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("18446744073709551616"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("-1"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("+0001"));
    show_buf8_uptr_from_str8(&buffer, opts, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_iptr(&buffer, opts, IPTR_MAX);
    show_buf8_iptr(&buffer, opts, IPTR_MIN);

    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("+0"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("127"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("128"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-128"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-129"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("32767"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("32768"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-32768"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-32769"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("2147483647"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("2147483648"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-2147483648"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-2147483649"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("9223372036854775807"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-9223372036854775808"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("9223372036854775808"));
    show_buf8_iptr_from_str8(&buffer, opts, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_u64(&buffer, opts, U64_MAX);
    show_buf8_u64(&buffer, opts, U64_MIN);

    show_buf8_u64_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("255"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("256"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("65535"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("65536"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("4294967295"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("4294967296"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("18446744073709551615"));

    printf("\nINVALID:\n");

    show_buf8_u64_from_str8(&buffer, opts, pax_str8("18446744073709551616"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("-1"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("+0001"));
    show_buf8_u64_from_str8(&buffer, opts, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i64(&buffer, opts, I64_MAX);
    show_buf8_i64(&buffer, opts, I64_MIN);

    show_buf8_i64_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("+0"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("127"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("128"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-128"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-129"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("32767"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("32768"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-32768"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-32769"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("2147483647"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("2147483648"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-2147483648"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-2147483649"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("9223372036854775807"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-9223372036854775808"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i64_from_str8(&buffer, opts, pax_str8("9223372036854775808"));
    show_buf8_i64_from_str8(&buffer, opts, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);
    printf("\nVALID:\n");

    show_buf8_u32(&buffer, opts, U32_MAX);
    show_buf8_u32(&buffer, opts, U32_MIN);

    show_buf8_u32_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("255"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("256"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("65535"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("65536"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("4294967295"));

    printf("\nINVALID:\n");

    show_buf8_u32_from_str8(&buffer, opts, pax_str8("4294967296"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("18446744073709551615"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("18446744073709551616"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("-1"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("+0001"));
    show_buf8_u32_from_str8(&buffer, opts, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i32(&buffer, opts, I32_MAX);
    show_buf8_i32(&buffer, opts, I32_MIN);

    show_buf8_i32_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("+0"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("127"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("128"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-128"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-129"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("32767"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("32768"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-32768"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-32769"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("2147483647"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-2147483648"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i32_from_str8(&buffer, opts, pax_str8("2147483648"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-2147483649"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("9223372036854775807"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("9223372036854775808"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-9223372036854775808"));
    show_buf8_i32_from_str8(&buffer, opts, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_u16(&buffer, opts, U16_MAX);
    show_buf8_u16(&buffer, opts, U16_MIN);

    show_buf8_u16_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("255"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("256"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("65535"));

    printf("\nINVALID:\n");

    show_buf8_u16_from_str8(&buffer, opts, pax_str8("65536"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("4294967295"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("4294967296"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("18446744073709551615"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("18446744073709551616"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("-1"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("+0001"));
    show_buf8_u16_from_str8(&buffer, opts, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i16(&buffer, opts, I16_MAX);
    show_buf8_i16(&buffer, opts, I16_MIN);

    show_buf8_i16_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("+0"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("127"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("128"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-128"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-129"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("32767"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-32768"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i16_from_str8(&buffer, opts, pax_str8("32768"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-32769"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("2147483647"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("2147483648"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-2147483648"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-2147483649"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("9223372036854775807"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("9223372036854775808"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-9223372036854775808"));
    show_buf8_i16_from_str8(&buffer, opts, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_u8(&buffer, opts, U8_MAX);
    show_buf8_u8(&buffer, opts, U8_MIN);

    show_buf8_u8_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("255"));

    printf("\nINVALID:\n");

    show_buf8_u8_from_str8(&buffer, opts, pax_str8("256"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("65535"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("65536"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("4294967295"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("4294967296"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("18446744073709551615"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("18446744073709551616"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("-1"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("+0001"));
    show_buf8_u8_from_str8(&buffer, opts, pax_str8("01"));

    buf8_clear(&buffer);

    printf("\nVALID:\n");

    show_buf8_i8(&buffer, opts, I8_MAX);
    show_buf8_i8(&buffer, opts, I8_MIN);

    show_buf8_i8_from_str8(&buffer, opts, pax_str8("1"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("+1"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("0"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("+0"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("127"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-128"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-1"));

    printf("\nINVALID:\n");

    show_buf8_i8_from_str8(&buffer, opts, pax_str8("128"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-129"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("32767"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("32768"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-32768"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-32769"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("2147483647"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("2147483648"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-2147483648"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-2147483649"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("9223372036854775807"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("9223372036854775808"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-9223372036854775808"));
    show_buf8_i8_from_str8(&buffer, opts, pax_str8("-9223372036854775809"));

    buf8_clear(&buffer);
}
