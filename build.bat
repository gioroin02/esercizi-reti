echo off

cls

set "core=dep\pax\core\exports.cpp"
set "string=dep\pax\string\exports.cpp"
set "format=dep\pax\format\exports.cpp"
set "memory=dep\pax\memory\exports.cpp"
set "storage=dep\pax\storage\exports.cpp"
set "network=dep\pax\network\exports.cpp"
set "container=dep\pax\container\exports.cpp"

set "winsock=-lws2_32"

set "udp=src\udp\exports.cpp"
set "tcp=src\tcp\exports.cpp"
set "http=src\http\exports.cpp"

set "src=%core% %string% %format% %memory% %storage% %network% %container% %udp% %tcp% %http%"
set "lib=%winsock%"
set "dir=src"

rem UDP

zig c++ %src% "%dir%\udp_server_first.cpp" %lib% -o udp_server_first.exe
zig c++ %src% "%dir%\udp_client_first.cpp" %lib% -o udp_client_first.exe

zig c++ %src% "%dir%\udp_server_add.cpp" %lib% -o udp_server_add.exe
zig c++ %src% "%dir%\udp_client_add.cpp" %lib% -o udp_client_add.exe

rem TCP

zig c++ %src% "%dir%\tcp_server_first.cpp" %lib% -o tcp_server_first.exe
zig c++ %src% "%dir%\tcp_client_first.cpp" %lib% -o tcp_client_first.exe

zig c++ %src% "%dir%\tcp_server_add.cpp" %lib% -o tcp_server_add.exe
zig c++ %src% "%dir%\tcp_client_add.cpp" %lib% -o tcp_client_add.exe

rem HTTP

rem zig c++ %src% "%dir%\http_server.cpp" %lib% -o http_server.exe
