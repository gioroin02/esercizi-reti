#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "import.h"

PxSocketUdp
udpClientStart(PxArena* arena, PxAddressType type);

void
udpClientStop(PxSocketUdp self);

pxb8
udpClientWrite(PxSocketUdp self, PxBuffer8* buffer, PxAddress address, pxu16 port);

pxb8
udpClientRead(PxSocketUdp self, PxBuffer8* buffer, PxAddress* address, pxu16* port);

#endif // UDP_CLIENT_H
