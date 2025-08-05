#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

#define RED(str) "\x1b[31m" str "\x1b[0m"
#define GRN(str) "\x1b[32m" str "\x1b[0m"
#define YLW(str) "\x1b[33m" str "\x1b[0m"
#define BLU(str) "\x1b[34m" str "\x1b[0m"
#define PRP(str) "\x1b[35m" str "\x1b[0m"
#define AZR(str) "\x1b[36m" str "\x1b[0m"

static u8 memory[8 * MEMORY_KIB] = {};

int
main(int argc, char** argv)
{
    Arena arena = arena_make(memory, 8 * MEMORY_KIB);

    if (argc != 2) {
        printf("usage: <program-name> <path>\n");

        return 1;
    }

    str8 path = pax_str8_max(argv[1], 128);

    File_Attribs attribs = {};
    Directory    directory = directory_open(&arena, path);

    isiz offset = arena_offset(&arena);

    while (directory_next(directory, &arena, &attribs) != 0) {
        str8 type = pax_str8(RED("ERR"));

        switch (attribs.type) {
            case FILE_TYPE_SIMPLE:    { type = pax_str8(GRN("file")); } break;
            case FILE_TYPE_DIRECTORY: { type = pax_str8(BLU("dir")); } break;

            default: break;
        }

        str8 perm = pax_str8(RED("ERR"));

        switch (attribs.perm) {
            case FILE_PERM_NONE:       { perm = pax_str8("--:--:--"); } break;
            case FILE_PERM_READ:       { perm = pax_str8(GRN("rd") ":__:__"); } break;
            case FILE_PERM_WRITE:      { perm = pax_str8("__:" BLU("wr") ":__"); } break;
            case FILE_PERM_READ_WRITE: { perm = pax_str8(GRN("rd") ":" BLU("wr") ":__"); } break;
            case FILE_PERM_EXEC:       { perm = pax_str8("__:__:" YLW("ex")); } break;
            case FILE_PERM_READ_EXEC:  { perm = pax_str8(GRN("rd") ":__:" YLW("ex")); } break;
            case FILE_PERM_WRITE_EXEC: { perm = pax_str8("__:" BLU("wr") ":" YLW("ex")); } break;
            case FILE_PERM_FULL:       { perm = pax_str8(GRN("rd") ":" BLU("wr") ":" YLW("ex")); } break;

            default: break;
        }

        printf("{ ");
        printf("path: " PRP("'%.*s'") ", ", pax_as(int, attribs.path.length), attribs.path.memory);
        printf("name: " PRP("'%32.*s'") ", ", pax_as(int, attribs.name.length), attribs.name.memory);
        printf("type: %s, ", type.memory);
        printf("perm: %s, ", perm.memory);
        printf("size: " YLW("%llu") " ", attribs.size);
        printf("}\n");

        arena_rewind(&arena, offset);
    }

    directory_close(directory);
}
