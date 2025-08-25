echo off

cls

call cmd\clean.bat

set "base=src\cpax\pax\base\export.c"
set "memory=src\cpax\pax\memory\export.c"
set "string=src\cpax\pax\string\export.c"
set "format=src\cpax\pax\format\export.c"
set "stream=src\cpax\pax\stream\export.c"
set "network=src\cpax\pax\network\export.c"

set "winsock=-lws2_32"

set "tcp=src\tcp\export.c"

set "src=%base% %memory% %string% %format% %stream% %network% %tcp%"
set "lib=%winsock%"
set "dir=src\tcp\test"

zig cc %src% "%dir%\tcp_server_first.c" %lib% -o tcp_server_first.exe
zig cc %src% "%dir%\tcp_client_first.c" %lib% -o tcp_client_first.exe

zig cc %src% "%dir%\tcp_server_add.c" %lib% -o tcp_server_add.exe
zig cc %src% "%dir%\tcp_client_add.c" %lib% -o tcp_client_add.exe
