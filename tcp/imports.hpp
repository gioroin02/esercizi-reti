#ifndef TCP_IMPORTS_HPP
#define TCP_IMPORTS_HPP

#include "../deps/pax/network/exports.hpp"

using namespace pax;

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

#endif // TCP_IMPORTS_HPP
