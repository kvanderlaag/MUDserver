#ifndef __WSINET_H__
#define __WSINET_H__


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>

int inet_pton(int af, const char *src, void *dst);

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);

#endif // __WSINET_H__
