#ifndef HTTP_HELPERS_CPP
#define HTTP_HELPERS_CPP

#include "helpers.hpp"

uptr
http_hash_str8(str8 key)
{
    uptr prime  = 31;
    uptr power  = 1;
    uptr modulo = 1e9 + 1;
    uptr result = 0;

    for (uptr i = 0; i < key.length; i += 1) {
        uptr temp =
            (key.memory[i] - ASCII_LOWER_A + 1) * power;

        result = (result + temp)  % modulo;
        power  = (power  * prime) % modulo;
    }

    return result;
}

#endif // HTTP_HELPERS_CPP
