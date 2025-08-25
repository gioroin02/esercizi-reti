#ifndef UDP_IMPORT_H
#define UDP_IMPORT_H

#include "../cpax/pax/network/export.h"

#ifndef COLORS
#define COLORS

    #define RED(x) "\x1b[31m" x "\x1b[0m"
    #define GRN(x) "\x1b[32m" x "\x1b[0m"
    #define YLW(x) "\x1b[33m" x "\x1b[0m"
    #define BLU(x) "\x1b[34m" x "\x1b[0m"
    #define PRP(x) "\x1b[35m" x "\x1b[0m"

    #define SUCC GRN("SUCCESSO")
    #define FAIL RED("FALLIMENTO")

    #define FATAL "[" PRP("FATAL") "]"
    #define ERROR "[" RED("ERROR") "]"
    #define WARN  "[" YLW("WARN")  "]"
    #define INFO  "[" BLU("INFO")  "]"
    #define DEBUG "[" GRN("DEBUG") "]"
    #define TRACE "[" PRP("TRACE") "]"

#endif // COLORS

#endif // UDP_IMPORT_H
