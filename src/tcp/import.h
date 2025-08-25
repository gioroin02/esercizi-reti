#ifndef TCP_IMPORT_H
#define TCP_IMPORT_H

#include "../cpax/pax/network/export.h"

#ifndef COLORS
#define COLORS

    #define RED(str) "\x1b[31m" str "\x1b[0m"
    #define GRN(str) "\x1b[32m" str "\x1b[0m"
    #define YLW(str) "\x1b[33m" str "\x1b[0m"
    #define BLU(str) "\x1b[34m" str "\x1b[0m"
    #define PRP(str) "\x1b[35m" str "\x1b[0m"

    #define SUCC GRN("SUCCESSO")
    #define FAIL RED("FALLIMENTO")

    #define FATAL "[" PRP("FATAL") "]"
    #define ERROR "[" RED("ERROR") "]"
    #define WARN  "[" YLW("WARN")  "]"
    #define INFO  "[" BLU("INFO")  "]"
    #define DEBUG "[" GRN("DEBUG") "]"
    #define TRACE "[" PRP("TRACE") "]"

#endif // COLORS

#endif // TCP_IMPORT_H
