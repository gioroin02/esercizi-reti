echo off

cls

set "base=src\pax\base\exports.cpp"
set "string=src\pax\string\exports.cpp"
set "format=src\pax\format\exports.cpp"
set "memory=src\pax\memory\exports.cpp"
set "storage=src\pax\storage\exports.cpp"
set "network=src\pax\network\exports.cpp"
set "structure=src\pax\structure\exports.cpp"

set "winsock=-lws2_32"

set "tcp=src\tcp\exports.cpp"
set "http=src\http\exports.cpp"

set "src=%base% %string% %format% %memory% %storage% %network% %structure% %tcp% %http%"
set "lib=%winsock%"
set "dir=src\http\test"

zig c++ %src% "%dir%\http_server.cpp"      %lib% -o http_server.exe
zig c++ %src% "%dir%\http_server_cgi.cpp"  %lib% -o http_server_cgi.exe
zig c++ %src% "%dir%\http_server_rest.cpp" %lib% -o http_server_rest.exe
