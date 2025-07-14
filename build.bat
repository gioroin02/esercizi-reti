echo off

cls

set "core=src\pax\core\exports.cpp"
set "string=src\pax\string\exports.cpp"
set "format=src\pax\format\exports.cpp"
set "memory=src\pax\memory\exports.cpp"
set "storage=src\pax\storage\exports.cpp"
set "network=src\pax\network\exports.cpp"
set "container=src\pax\container\exports.cpp"

set "winsock=-lws2_32"

set "udp=src\udp\exports.cpp"
set "tcp=src\tcp\exports.cpp"
set "http=src\http\exports.cpp"

set "src=%core% %string% %format% %memory% %storage% %network% %container% %udp% %tcp% %http%"
set "lib=%winsock%"
set "dir=src"

rem UDP

rem zig c++ %src% "%dir%\udp_server_first.cpp" %lib% -o udp_server_first.exe
rem zig c++ %src% "%dir%\udp_client_first.cpp" %lib% -o udp_client_first.exe
rem
rem zig c++ %src% "%dir%\udp_server_add.cpp" %lib% -o udp_server_add.exe
rem zig c++ %src% "%dir%\udp_client_add.cpp" %lib% -o udp_client_add.exe

rem TCP

rem zig c++ %src% "%dir%\tcp_server_first.cpp" %lib% -o tcp_server_first.exe
rem zig c++ %src% "%dir%\tcp_client_first.cpp" %lib% -o tcp_client_first.exe
rem
rem zig c++ %src% "%dir%\tcp_server_add.cpp" %lib% -o tcp_server_add.exe
rem zig c++ %src% "%dir%\tcp_client_add.cpp" %lib% -o tcp_client_add.exe
rem
rem zig c++ %src% "%dir%\tcp_server_file.cpp" %lib% -o tcp_server_file.exe
rem zig c++ %src% "%dir%\tcp_client_file.cpp" %lib% -o tcp_client_file.exe

rem HTTP

zig c++ %src% "%dir%\http_server.cpp"     %lib% -o http_server.exe
zig c++ %src% "%dir%\http_server_cgi.cpp" %lib% -o http_server_cgi.exe
