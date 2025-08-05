#include "../exports.hpp"

using namespace pax;

#include <stdio.h>

int
main()
{
    Arena arena = system_reserve(2 * MEMORY_KIB);
    Array array = array_reserve<u32>(&arena, 5);

    for (isiz i = 0; i < array.length; i += 1)
        array_insert_tail<u32>(&array, i);

    printf("swap (tail, 0) = %u\n", array_swap_tail(&array, 0));
    printf("\n");

    for (isiz i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or<u32>(&array, i, 0));

    printf("\n");
    printf("drop (1) = %u\n", array_drop(&array, 1));
    printf("\n");

    for (isiz i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or<u32>(&array, i, 0));

    printf("\n");
    printf("insert (head, 1200) = %u\n", array_insert_head<u32>(&array, 1200));
    printf("\n");

    for (isiz i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or<u32>(&array, i, 0));

    printf("\n");
    printf("remove (4) = %u\n", array_remove_or<u32>(&array, 4, 0));
    printf("\n");

    for (isiz i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or<u32>(&array, i, 0));

    printf("\n");
    printf("insert (2, 250) = %u\n", array_insert<u32>(&array, 2, 250));
    printf("\n");

    for (isiz i = 0; i < array.size; i += 1)
        printf("%llu: %u\n", i, array_get_or<u32>(&array, i, 0));
}
