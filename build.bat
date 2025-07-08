echo off

cls

set "core=deps/pax/core/exports.cpp"
set "string=deps/pax/string/exports.cpp"
set "format=deps/pax/format/exports.cpp"
set "memory=deps/pax/memory/exports.cpp"
set "storage=deps/pax/storage/exports.cpp"
set "network=deps/pax/network/exports.cpp"
set "container=deps/pax/container/exports.cpp"

set "winsock=-lws2_32"

set "tcp=tcp\exports.cpp"
set "http=http\exports.cpp"

set "src=%core% %string% %format% %memory% %storage% %network% %container% %tcp% %http%"
set "lib=%winsock%"
set "dir=."

zig c++ %src% "%dir%\http_server.cpp" %lib% -o http_server.exe

zig c++ %src% "%dir%\tcp_server_first.cpp" %lib% -o tcp_server_first.exe
zig c++ %src% "%dir%\tcp_client_first.cpp" %lib% -o tcp_client_first.exe
