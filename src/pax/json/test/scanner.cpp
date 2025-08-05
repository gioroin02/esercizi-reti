#include "../exports.hpp"

#include "../../memory/exports.hpp"

using namespace pax;

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED    "\x1b[31m"
#define FRONT_GREEN  "\x1b[32m"
#define FRONT_YELLOW "\x1b[33m"
#define FRONT_BLUE   "\x1b[34m"
#define FRONT_PURPLE "\x1b[35m"
#define FRONT_AZURE  "\x1b[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GREEN(expr)  FRONT_GREEN  expr COLOR_RESET
#define YELLOW(expr) FRONT_YELLOW expr COLOR_RESET
#define BLUE(expr)   FRONT_BLUE   expr COLOR_RESET
#define PURPLE(expr) FRONT_PURPLE expr COLOR_RESET
#define AZURE(expr)  FRONT_AZURE  expr COLOR_RESET

static const str8 STRING = pax_str8(
    "{\n  \"id\": 92,\n  \"firstName\": \"William\",\n  \"lastName\": \"Lynch\",\n  \"email\": \"uropg@fxw9j.com\",\n  \"active\": false,\n  \"tags\": [\n    \"work\",\n    \"agreement\",\n    \"right\"\n  ],\n  \"details\": {\n    \"age\": 16,\n    \"city\": \"Dhaka\",\n    \"country\": \"South Korea\",\n    \"phoneNumber\": \"(858) 226-4695\",\n    \"startDate\": \"2013-09-07T05:11:31.761Z\",\n    \"endDate\": \"2011-11-04T22:47:43.479Z\"\n  }\n}"
);

static const str8 STRING_0 = pax_str8(
    "{\n  \"id\": 92,\n  \"firstName\": \"William\",\n  \"lastName\": \"Lynch\",\n  \"email\": \"uropg@fxw9j.com\",\n  \"active\": false,\n  \"tags\": [\n    \"work\",\n    \"agreement\",\n    \"right\"\n  ],\n  \"details\": {\n    \"age\": 16,\n    \"ci");

static const str8 STRING_1 = pax_str8(
    "ty\": \"Dhaka\",\n    \"country\": \"South Korea\",\n    \"phoneNumber\": \"(858) 226-4695\",\n    \"startDate\": \"2013-09-07T05:11:31.761Z\",\n    \"endDate\": \"2011-11-04T22:47:43.479Z\"\n  }\n}"
);

int
main(int argc, char** argv)
{
    Arena arena  = system_reserve(16);
    buf8  buffer = buf8_reserve(&arena, MEMORY_KIB);

    buf8_write_str8_tail(&buffer, STRING_0);
    buf8_normalize(&buffer);

    printf(PURPLE("[chunk-start]") "\n%.*s" PURPLE("[chunk-stop]") "\n",
        pax_as(int, buffer.size), buffer.memory);

    JSON_Scanner scanner = json_scanner_make(&buffer, 0, 0);
    JSON_Token   token   = {};

    printf("\n");

    while (token.type != JSON_TOKEN_COUNT) {
        token = json_scanner_token(&scanner, &arena);

        switch (token.type) {
            case JSON_TOKEN_OPEN_OBJ: {
                printf("  OPEN_OBJ | {\n");
            } break;

            case JSON_TOKEN_OPEN_ARR: {
                printf("  OPEN_ARR | [\n");
            } break;

            case JSON_TOKEN_CLOSE_OBJ: {
                printf(" CLOSE_OBJ | }\n");
            } break;

            case JSON_TOKEN_CLOSE_ARR: {
                printf(" CLOSE_ARR | ]\n");
            } break;

            case JSON_TOKEN_COLON: {
                printf("     COLON | :\n");
            } break;

            case JSON_TOKEN_COMMA: {
                printf("     COMMA | ,\n");
            } break;

            case JSON_TOKEN_NULL: {
                printf("      NULL | null\n");
            } break;

            case JSON_TOKEN_TRUE: {
                printf("      TRUE | null\n");
            } break;

            case JSON_TOKEN_FALSE: {
                printf("     FALSE | null\n");
            } break;

            case JSON_TOKEN_STRING: {
                printf("    STRING | %.*s\n",
                    pax_as(int, token.string.length), token.string.memory);
            } break;

            case JSON_TOKEN_ABSOLUTE: {
                printf("  ABSOLUTE | %llu\n", token.absolute);
            } break;

            case JSON_TOKEN_RELATIVE: {
                printf("  RELATIVE | %lli\n", token.relative);
            } break;

            case JSON_TOKEN_FLOATING: {
                printf("  FLOATING | %lf\n", token.floating);
            } break;

            case JSON_TOKEN_ERROR: {
                str8 message = token.error.message;
                str8 content = token.error.content;
                isiz line    = token.error.line;
                isiz column  = token.error.column;

                printf("     ERROR | " RED("%.*s") ", [%.*s] at %llu:%llu\n",
                    pax_as(int, message.length), message.memory,
                    pax_as(int, content.length), content.memory,
                    line, column);

                token.type = JSON_TOKEN_COUNT;
            } break;

            default: break;
        }
    }

    buf8_write_str8_tail(&buffer, STRING_1);
    buf8_normalize(&buffer);

    printf("\n");

    printf(PURPLE("[chunk-start]") "\n%.*s" PURPLE("[chunk-stop]") "\n",
        pax_as(int, buffer.size), buffer.memory);

    printf("\n");

    token = {};

    while (token.type != JSON_TOKEN_COUNT) {
        token = json_scanner_token(&scanner, &arena);

        switch (token.type) {
            case JSON_TOKEN_OPEN_OBJ: {
                printf("  OPEN_OBJ | {\n");
            } break;

            case JSON_TOKEN_OPEN_ARR: {
                printf("  OPEN_ARR | [\n");
            } break;

            case JSON_TOKEN_CLOSE_OBJ: {
                printf(" CLOSE_OBJ | }\n");
            } break;

            case JSON_TOKEN_CLOSE_ARR: {
                printf(" CLOSE_ARR | ]\n");
            } break;

            case JSON_TOKEN_COLON: {
                printf("     COLON | :\n");
            } break;

            case JSON_TOKEN_COMMA: {
                printf("     COMMA | ,\n");
            } break;

            case JSON_TOKEN_NULL: {
                printf("      NULL | null\n");
            } break;

            case JSON_TOKEN_TRUE: {
                printf("      TRUE | null\n");
            } break;

            case JSON_TOKEN_FALSE: {
                printf("     FALSE | null\n");
            } break;

            case JSON_TOKEN_STRING: {
                printf("    STRING | %.*s\n",
                    pax_as(int, token.string.length), token.string.memory);
            } break;

            case JSON_TOKEN_ABSOLUTE: {
                printf("  ABSOLUTE | %llu\n", token.absolute);
            } break;

            case JSON_TOKEN_RELATIVE: {
                printf("  RELATIVE | %lli\n", token.relative);
            } break;

            case JSON_TOKEN_FLOATING: {
                printf("  FLOATING | %lf\n", token.floating);
            } break;

            case JSON_TOKEN_ERROR: {
                str8 message = token.error.message;
                str8 content = token.error.content;
                isiz line    = token.error.line;
                isiz column  = token.error.column;

                printf("     ERROR | " RED("%.*s") ", [%.*s] at %llu:%llu\n",
                    pax_as(int, message.length), message.memory,
                    pax_as(int, content.length), content.memory,
                    line, column);

                token.type = JSON_TOKEN_COUNT;
            } break;

            default: break;
        }
    }
}
