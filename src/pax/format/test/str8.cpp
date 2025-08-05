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
show_str8_from_usiz(Arena* arena, Format_Options options, usiz value)
{
    str8 string = str8_from_usiz(arena, options, value);

    printf("write (" PURPLE("%llu") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < string.length; i += 1)
        printf("%c", string.memory[i]);

    printf("' (%llu)" FORE_RESET "\n", string.length);
}

void
show_str8_from_isiz(Arena* arena, Format_Options options, isiz value)
{
    str8 string = str8_from_isiz(arena, options, value);

    printf("write (" PURPLE("%lli") ") -> ", value);

    printf(FORE_BLUE "'");

    for (isiz i = 0; i < string.length; i += 1)
        printf("%c", string.memory[i]);

    printf("' (%llu)" FORE_RESET "\n", string.length);
}

static u8 memory[MEMORY_KIB] = {};

int
main()
{
    Arena arena = arena_make(memory, MEMORY_KIB);

    usiz options_count = 5;

    Format_Options options_array[5] = {
        format_options_simple(10),
        format_options(10, FORMAT_FLAG_LEADING_ZERO | FORMAT_FLAG_LEADING_PLUS),
        format_options_simple(2),
        format_options_simple(8),
        format_options_simple(16),
    };

    for (isiz i = 0; i < options_count; i += 1) {
        printf("VALID:\n");

        show_str8_from_usiz(&arena, options_array[i], 255);
        show_str8_from_usiz(&arena, options_array[i], 0);

        printf("\nVALID:\n");

        show_str8_from_isiz(&arena, options_array[i], 255);
        show_str8_from_isiz(&arena, options_array[i], 0);
        show_str8_from_isiz(&arena, options_array[i], -256);

        if (i + 1 != options_count)
            printf("\n");
    }
}
