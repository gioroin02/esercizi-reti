#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main(int argc, const char* argv[])
{
    u8 memory[MEMORY_KIB] = {};

    Arena arena = pax_arena(memory);

    Buffer buffer = buffer_reserve(&arena, 10);

    buffer_write_mem8_tail(&buffer, pax_cast(u8*, "coda"), 4);
    buffer_write_mem8_head(&buffer, pax_cast(u8*, "testa"), 5);

    u8 temp[3] = {};

    buffer_read_mem8_head(&buffer, temp, pax_array_bytes(temp));

    printf("temp:\n");

    for (uptr i = 0; i < pax_array_bytes(temp); i += 1)
        printf("%llu. %c\n", i, temp[i]);

    printf("buffer:\n");

    for (uptr i = 0; i < buffer.length; i += 1) {
        b32 line = (buffer.head <= buffer.tail) &&
            (buffer.head <= i && i < buffer.tail);

        b32 circ = (buffer.head >= buffer.tail) &&
            (buffer.head <= i || i < buffer.tail);

        if (line != 0 || circ != 0)
            printf("[%c]", buffer.memory[i]);
        else
            printf("[_]");
    }

    printf("\n");

    for (uptr i = 0; i < buffer.size; i += 1) {
        uptr idx = (buffer.head + i) % buffer.length;
        u8   chr = buffer.memory[idx];

        printf("%llu. %c\n", idx, chr);
    }

    buffer_normalize(&buffer);

    printf("buffer:\n");

    for (uptr i = 0; i < buffer.length; i += 1)
        printf("[%c]", buffer.memory[i]);
    printf("\n");

    for (uptr i = 0; i < buffer.size; i += 1) {
        uptr idx = (buffer.head + i) % buffer.length;
        u8   chr = buffer.memory[idx];

        printf("%llu. %c\n", idx, chr);
    }
}
