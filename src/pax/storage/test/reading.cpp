#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

static u8 memory[8 * MEMORY_KIB] = {};

int
main(int argc, char** argv)
{
    Arena arena   = arena_make(memory, 8 * MEMORY_KIB);
    buf8  reading = buf8_reserve(&arena, 4 * MEMORY_KIB);

    if (argc != 2) {
        printf("usage: <program-name> <file-name>\n");

        return 1;
    }

    str8 name = pax_str8_max(argv[1], 128);
    File file = file_open(&arena, pax_str8("."), name, FILE_PERM_READ);

    if (file == 0) return 1;

    file_read(file, &reading);

    printf("\x1b[32m%.*s\x1b[0m (%llu)\n", pax_as(int, reading.size),
        reading.memory, file_offset(file));

    file_rewind(file, 0);

    buf8_clear(&reading);

    file_read(file, &reading);

    printf("\x1b[34m%.*s\x1b[0m (%llu)\n", pax_as(int, reading.size),
        reading.memory, file_offset(file));

    file_close(file);
}
