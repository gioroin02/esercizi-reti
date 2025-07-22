echo off

cls

set "core=src\pax\core\exports.cpp"
set "string=src\pax\string\exports.cpp"
set "format=src\pax\format\exports.cpp"
set "memory=src\pax\memory\exports.cpp"
set "storage=src\pax\storage\exports.cpp"
set "network=src\pax\network\exports.cpp"

set "winsock=-lws2_32"

set "tcp=src\tcp\exports.cpp"

set "src=%core% %string% %format% %memory% %storage% %network% %tcp%"
set "lib=%winsock%"
set "dir=src\tcp\test"

zig c++ %src% "%dir%\tcp_server_first.cpp" %lib% -o tcp_server_first.exe
zig c++ %src% "%dir%\tcp_client_first.cpp" %lib% -o tcp_client_first.exe

zig c++ %src% "%dir%\tcp_server_add.cpp" %lib% -o tcp_server_add.exe
zig c++ %src% "%dir%\tcp_client_add.cpp" %lib% -o tcp_client_add.exe

zig c++ %src% "%dir%\tcp_server_file.cpp" %lib% -o tcp_server_file.exe
zig c++ %src% "%dir%\tcp_client_file.cpp" %lib% -o tcp_client_file.exe
