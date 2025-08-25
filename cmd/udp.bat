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

set "udp=src\udp\export.c"

set "src=%base% %memory% %string% %format% %stream% %network% %udp%"
set "lib=%winsock%"
set "dir=src\udp\test"

zig cc %src% "%dir%\udp_server_first.c" %lib% -o udp_server_first.exe
zig cc %src% "%dir%\udp_client_first.c" %lib% -o udp_client_first.exe

zig cc %src% "%dir%\udp_server_add.c" %lib% -o udp_server_add.exe
zig cc %src% "%dir%\udp_client_add.c" %lib% -o udp_client_add.exe
