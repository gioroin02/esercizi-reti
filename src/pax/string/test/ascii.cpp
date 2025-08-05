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

static const str8 ASCII_NAMES[ASCII_COUNT] = {
    pax_to_str8(ASCII_NULL),
    pax_to_str8(ASCII_1),
    pax_to_str8(ASCII_2),
    pax_to_str8(ASCII_3),
    pax_to_str8(ASCII_4),
    pax_to_str8(ASCII_5),
    pax_to_str8(ASCII_6),
    pax_to_str8(ASCII_7),
    pax_to_str8(ASCII_SPACE_BACK),
    pax_to_str8(ASCII_TAB_HORIZONTAL),
    pax_to_str8(ASCII_LINE_FEED),
    pax_to_str8(ASCII_TAB_VERTICAL),
    pax_to_str8(ASCII_PAGE_FEED),
    pax_to_str8(ASCII_CARRIAGE_RETURN),
    pax_to_str8(ASCII_14),
    pax_to_str8(ASCII_15),
    pax_to_str8(ASCII_16),
    pax_to_str8(ASCII_17),
    pax_to_str8(ASCII_18),
    pax_to_str8(ASCII_19),
    pax_to_str8(ASCII_20),
    pax_to_str8(ASCII_21),
    pax_to_str8(ASCII_22),
    pax_to_str8(ASCII_23),
    pax_to_str8(ASCII_CANCEL),
    pax_to_str8(ASCII_25),
    pax_to_str8(ASCII_26),
    pax_to_str8(ASCII_ESCAPE),
    pax_to_str8(ASCII_28),
    pax_to_str8(ASCII_29),
    pax_to_str8(ASCII_30),
    pax_to_str8(ASCII_31),
    pax_to_str8(ASCII_SPACE),
    pax_to_str8(ASCII_MARK_EXCL),
    pax_to_str8(ASCII_MARK_QUOTE),
    pax_to_str8(ASCII_SHARP),
    pax_to_str8(ASCII_DOLLAR),
    pax_to_str8(ASCII_PERCENT),
    pax_to_str8(ASCII_AMPERSAND),
    pax_to_str8(ASCII_APOSTROPHE),
    pax_to_str8(ASCII_PAREN_LEFT),
    pax_to_str8(ASCII_PAREN_RIGHT),
    pax_to_str8(ASCII_ASTERISK),
    pax_to_str8(ASCII_PLUS),
    pax_to_str8(ASCII_COMMA),
    pax_to_str8(ASCII_MINUS),
    pax_to_str8(ASCII_POINT),
    pax_to_str8(ASCII_SLASH),
    pax_to_str8(ASCII_ZERO),
    pax_to_str8(ASCII_ONE),
    pax_to_str8(ASCII_TWO),
    pax_to_str8(ASCII_THREE),
    pax_to_str8(ASCII_FOUR),
    pax_to_str8(ASCII_FIVE),
    pax_to_str8(ASCII_SIX),
    pax_to_str8(ASCII_SEVEN),
    pax_to_str8(ASCII_EIGHT),
    pax_to_str8(ASCII_NINE),
    pax_to_str8(ASCII_COLON),
    pax_to_str8(ASCII_COLON_SEMI),
    pax_to_str8(ASCII_LESS),
    pax_to_str8(ASCII_EQUAL),
    pax_to_str8(ASCII_MORE),
    pax_to_str8(ASCII_MARK_QUEST),
    pax_to_str8(ASCII_COMMERCIAL),
    pax_to_str8(ASCII_UPPER_A),
    pax_to_str8(ASCII_UPPER_B),
    pax_to_str8(ASCII_UPPER_C),
    pax_to_str8(ASCII_UPPER_D),
    pax_to_str8(ASCII_UPPER_E),
    pax_to_str8(ASCII_UPPER_F),
    pax_to_str8(ASCII_UPPER_G),
    pax_to_str8(ASCII_UPPER_H),
    pax_to_str8(ASCII_UPPER_I),
    pax_to_str8(ASCII_UPPER_J),
    pax_to_str8(ASCII_UPPER_K),
    pax_to_str8(ASCII_UPPER_L),
    pax_to_str8(ASCII_UPPER_M),
    pax_to_str8(ASCII_UPPER_N),
    pax_to_str8(ASCII_UPPER_O),
    pax_to_str8(ASCII_UPPER_P),
    pax_to_str8(ASCII_UPPER_Q),
    pax_to_str8(ASCII_UPPER_R),
    pax_to_str8(ASCII_UPPER_S),
    pax_to_str8(ASCII_UPPER_T),
    pax_to_str8(ASCII_UPPER_U),
    pax_to_str8(ASCII_UPPER_V),
    pax_to_str8(ASCII_UPPER_W),
    pax_to_str8(ASCII_UPPER_X),
    pax_to_str8(ASCII_UPPER_Y),
    pax_to_str8(ASCII_UPPER_Z),
    pax_to_str8(ASCII_SQUARE_LEFT),
    pax_to_str8(ASCII_SLASH_BACK),
    pax_to_str8(ASCII_SQUARE_RIGHT),
    pax_to_str8(ASCII_CIRCUMFLEX),
    pax_to_str8(ASCII_UNDERSBASE),
    pax_to_str8(ASCII_TICK_BACK),
    pax_to_str8(ASCII_LOWER_A),
    pax_to_str8(ASCII_LOWER_B),
    pax_to_str8(ASCII_LOWER_C),
    pax_to_str8(ASCII_LOWER_D),
    pax_to_str8(ASCII_LOWER_E),
    pax_to_str8(ASCII_LOWER_F),
    pax_to_str8(ASCII_LOWER_G),
    pax_to_str8(ASCII_LOWER_H),
    pax_to_str8(ASCII_LOWER_I),
    pax_to_str8(ASCII_LOWER_J),
    pax_to_str8(ASCII_LOWER_K),
    pax_to_str8(ASCII_LOWER_L),
    pax_to_str8(ASCII_LOWER_M),
    pax_to_str8(ASCII_LOWER_N),
    pax_to_str8(ASCII_LOWER_O),
    pax_to_str8(ASCII_LOWER_P),
    pax_to_str8(ASCII_LOWER_Q),
    pax_to_str8(ASCII_LOWER_R),
    pax_to_str8(ASCII_LOWER_S),
    pax_to_str8(ASCII_LOWER_T),
    pax_to_str8(ASCII_LOWER_U),
    pax_to_str8(ASCII_LOWER_V),
    pax_to_str8(ASCII_LOWER_W),
    pax_to_str8(ASCII_LOWER_X),
    pax_to_str8(ASCII_LOWER_Y),
    pax_to_str8(ASCII_LOWER_Z),
    pax_to_str8(ASCII_BRACE_LEFT),
    pax_to_str8(ASCII_PIPE),
    pax_to_str8(ASCII_BRACE_RIGHT),
    pax_to_str8(ASCII_TILDE),
    pax_to_str8(ASCII_DELETE),
};

void
show_ascii_is_space()
{
    printf("Space:\n");

    for (u32 i = 0; i < ASCII_COUNT; i += 1) {
        str8 name = ASCII_NAMES[i];

        if (ascii_is_space(i) != 0)
            printf("- %.*s\n", pax_as_i32(name.length), name.memory);
    }
}

void
show_ascii_is_letter()
{
    printf("Letter:\n");

    for (u32 i = 0; i < ASCII_COUNT; i += 1) {
        str8 name = ASCII_NAMES[i];

        if (ascii_is_letter(i) != 0)
            printf("- %.*s\n", pax_as_i32(name.length), name.memory);
    }
}

void
show_ascii_index_from_letter()
{
    for (u8 i = 0; i < ASCII_COUNT; i += 1) {
        str8 name   = ASCII_NAMES[i];
        usiz letter = ascii_index_from_letter(i);

        if (letter != 26) {
            printf("- %.*s, %llu\n",
                pax_as_i32(name.length), name.memory, letter);
        }
    }
}

void
show_ascii_letter_from_index()
{
    for (isiz i = 0; i < 26; i += 1) {
        u8 lower = ascii_letter_from_index(i, 0);
        u8 upper = ascii_letter_from_index(i, 1);

        printf("- %llu", i);

        if (lower != ASCII_NULL) printf(": %c", lower);
        if (upper != ASCII_NULL) printf(", %c", upper);

        printf("\n");
    }
}

void
show_ascii_is_lower()
{
    printf("Lower:\n");

    for (u32 i = 0; i < ASCII_COUNT; i += 1) {
        str8 name = ASCII_NAMES[i];

        if (ascii_is_lower(i) != 0)
            printf("- %.*s\n", pax_as_i32(name.length), name.memory);
    }
}

void
show_ascii_index_from_lower()
{
    for (u8 i = 0; i < ASCII_COUNT; i += 1) {
        str8 name   = ASCII_NAMES[i];
        usiz letter = ascii_index_from_lower(i);

        if (letter != 26) {
            printf("- %.*s, %llu\n",
                pax_as_i32(name.length), name.memory, letter);
        }
    }
}

void
show_ascii_lower_from_index()
{
    for (isiz i = 0; i < 26; i += 1) {
        u8 lower = ascii_lower_from_index(i);

        printf("- %llu", i);

        if (lower != ASCII_NULL)
            printf(": %c", lower);

        printf("\n");
    }
}

void
show_ascii_is_upper()
{
    printf("Upper:\n");

    for (u32 i = 0; i < ASCII_COUNT; i += 1) {
        str8 name = ASCII_NAMES[i];

        if (ascii_is_upper(i) != 0)
            printf("- %.*s\n", pax_as_i32(name.length), name.memory);
    }
}

void
show_ascii_index_from_upper()
{
    for (u8 i = 0; i < ASCII_COUNT; i += 1) {
        str8 name   = ASCII_NAMES[i];
        usiz letter = ascii_index_from_upper(i);

        if (letter != 26) {
            printf("- %.*s, %llu\n",
                pax_as_i32(name.length), name.memory, letter);
        }
    }
}

void
show_ascii_upper_from_index()
{
    for (isiz i = 0; i < 26; i += 1) {
        u8 upper = ascii_upper_from_index(i);

        printf("- %llu", i);

        if (upper != ASCII_NULL)
            printf(": %c", upper);

        printf("\n");
    }
}

void
show_ascii_is_digit()
{
    for (usiz j = 2; j <= 16; j += 1) {
        printf("Digit (%llu):\n", j);

        for (u8 i = 0; i < ASCII_COUNT; i += 1) {
            str8 name = ASCII_NAMES[i];

            if (ascii_is_digit(i, j) != 0)
                printf("- %.*s\n", pax_as_i32(name.length), name.memory);
        }
    }
}

void
show_ascii_index_from_digit()
{
    for (usiz j = 2; j <= 16; j += 1) {
        printf("Digit (%llu):\n", j);

        for (u8 i = 0; i < ASCII_COUNT; i += 1) {
            str8 name  = ASCII_NAMES[i];
            usiz digit = ascii_index_from_digit(i, j);

            if (digit != j) {
                printf("- %.*s, %llu\n",
                    pax_as_i32(name.length), name.memory, digit);
            }
        }
    }
}

void
show_ascii_digit_from_index()
{
    for (usiz j = 2; j <= 16; j += 1) {
        printf("Digit (%llu):\n", j);

        for (isiz i = 0; i < j; i += 1) {
            u8 lower = ascii_digit_from_index(i, j, 0);
            u8 upper = ascii_digit_from_index(i, j, 1);

            printf("- %llu", i);

            if (lower != ASCII_NULL) printf(": %c", lower);
            if (upper != ASCII_NULL) printf(", %c", upper);

            printf("\n");
        }
    }
}

int
main()
{
    show_ascii_is_space();

    show_ascii_is_lower();
    show_ascii_index_from_lower();
    show_ascii_lower_from_index();

    show_ascii_is_upper();
    show_ascii_index_from_upper();
    show_ascii_upper_from_index();

    show_ascii_is_digit();
    show_ascii_index_from_digit();
    show_ascii_digit_from_index();

    show_ascii_is_letter();
    show_ascii_index_from_letter();
    show_ascii_letter_from_index();
}
