#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "import.h"

PxSocketTcp
tcpServerStart(PxArena* arena, PxAddress address, pxu16 port);

void
tcpServerStop(PxSocketTcp self);

PxSocketTcp
tcpSessionOpen(PxSocketTcp server, PxArena* arena);

void
tcpSessionClose(PxSocketTcp self);

pxb8
tcpSessionWrite(PxSocketTcp self, PxBuffer8* buffer);

pxb8
tcpSessionRead(PxSocketTcp self, PxBuffer8* buffer);

#endif // TCP_SERVER_H
