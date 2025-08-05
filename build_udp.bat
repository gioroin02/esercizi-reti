echo off

cls

set "base=src\pax\base\exports.cpp"
set "string=src\pax\string\exports.cpp"
set "format=src\pax\format\exports.cpp"
set "memory=src\pax\memory\exports.cpp"
set "network=src\pax\network\exports.cpp"

set "winsock=-lws2_32"

set "udp=src\udp\exports.cpp"

set "src=%base% %string% %format% %memory% %network% %udp%"
set "lib=%winsock%"
set "dir=src\udp\test"

zig c++ %src% "%dir%\udp_server_first.cpp" %lib% -o udp_server_first.exe
zig c++ %src% "%dir%\udp_client_first.cpp" %lib% -o udp_client_first.exe

zig c++ %src% "%dir%\udp_server_add.cpp" %lib% -o udp_server_add.exe
zig c++ %src% "%dir%\udp_client_add.cpp" %lib% -o udp_client_add.exe
