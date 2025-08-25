#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "import.h"

PxSocketUdp
udpServerStart(PxArena* arena, PxAddress address, pxu16 port);

void
udpServerStop(PxSocketUdp self);

pxb8
udpServerWrite(PxSocketUdp self, PxBuffer8* buffer, PxAddress address, pxu16 port);

pxb8
udpServerRead(PxSocketUdp self, PxBuffer8* buffer, PxAddress* address, pxu16* port);

#endif // UDP_SERVER_H
