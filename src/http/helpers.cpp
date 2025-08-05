#ifndef HTTP_HELPERS_CPP
#define HTTP_HELPERS_CPP

#include "helpers.hpp"

usiz
http_hash_str8(str8 key)
{
    usiz prime  = 31;
    usiz power  = 1;
    usiz modulo = 1e9 + 1;
    usiz result = 0;

    for (usiz i = 0; i < key.length; i += 1) {
        usiz temp =
            (key.memory[i] - ASCII_LOWER_A + 1) * power;

        result = (result + temp)  % modulo;
        power  = (power  * prime) % modulo;
    }

    return result;
}

#endif // HTTP_HELPERS_CPP
