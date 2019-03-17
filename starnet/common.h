#pragma once

#include "platform.h"

#ifdef PLATFORM_WINDOWS

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#endif

#ifdef PLATFORM_WINDOWS || PLATFORM_LINUX || PLATFORM_OSX
#define BERKELEY_SUBSYSTEM 1;
#else 
#define UNKNOWN_SUBSYSTEM 1;
#endif