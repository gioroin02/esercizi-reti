#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

static u8 memory[MEMORY_KIB] = {};

int
main()
{
    Arena arena  = arena_make(memory, MEMORY_KIB);
    buf8  buffer = buf8_reserve(&arena, 4);

    buffer.head = 2;
    buffer.tail = 2;

    buf8_write_utf8_tail(&buffer, 0x1f600);

    printf("%.*s\n", pax_as(int, buffer.size),
        buffer.memory);

    u32 value = 0;

    buf8_read_utf8_head(&buffer, &value);

    printf("%x\n", value);
}
