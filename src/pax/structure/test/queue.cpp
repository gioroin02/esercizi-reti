#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main()
{
    Arena arena = system_reserve(2 * MEMORY_KIB);
    Queue queue = queue_reserve<u32>(&arena, 10);

    for (isiz i = 0; i < queue.length; i += 1)
        queue_insert_tail<u32>(&queue, i);

    for (isiz i = 0; i < queue.length / 2; i += 1)
        queue_drop_head(&queue);

    for (isiz i = 0; i < queue.length / 2; i += 1)
        queue_insert_tail<u32>(&queue, i);

    u32 temp = 0;

    printf("head = %llu, tail = %llu\n", queue.head, queue.tail);

    for (isiz i = 0; i < queue.size; i += 1) {
        u32 value = queue_get_or<u32>(&queue, i, 0);
        u32 other = 0;

        mem8_copy(&other, queue.memory + (i * queue.stride),
            queue.stride);

        printf("%llu: [%u] %u\n", i, other, value);
    }

    Queue copy = queue_copy(&arena, &queue);

    printf("head = %llu, tail = %llu\n", copy.head, copy.tail);

    for (isiz i = 0; i < copy.size; i += 1) {
        u32 value = queue_get_or<u32>(&copy, i, 0);
        u32 other = 0;

        mem8_copy(&other, copy.memory + (i * copy.stride),
            copy.stride);

        printf("%llu: [%u] %u\n", i, other, value);
    }

    queue = queue_copy(&arena, &copy);

    printf("head = %llu, tail = %llu\n", queue.head, queue.tail);

    for (isiz i = 0; i < queue.size; i += 1) {
        u32 value = queue_get_or<u32>(&queue, i, 0);
        u32 other = 0;

        mem8_copy(&other, queue.memory + (i * queue.stride),
            queue.stride);

        printf("%llu: [%u] %u\n", i, other, value);
    }
}
