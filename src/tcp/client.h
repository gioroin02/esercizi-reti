#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "import.h"

PxSocketTcp
tcpClientStart(PxArena* arena, PxAddressType type);

void
tcpClientStop(PxSocketTcp self);

pxb8
tcpClientConnect(PxSocketTcp self, PxAddress address, pxu16 port);

pxb8
tcpClientWrite(PxSocketTcp self, PxBuffer8* buffer);

pxb8
tcpClientRead(PxSocketTcp self, PxBuffer8* buffer);

#endif // TCP_CLIENT_H
