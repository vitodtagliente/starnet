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

namespace starnet
{
	enum class NativeSocketSystem : uint8_t
	{
		Unknown,
		Berkeley,
		// ... future supports (es. PS4, XBoxLive, ...)
		Count
	};

	inline NativeSocketSystem getNativeSocketSystem()
	{
#if PLATFORM_WINDOWS || PLATFORM_LINUX || PLATFORM_MAC
		return NativeSocketSystem::Berkeley;
#endif
		return NativeSocketSystem::Unknown;
	}
}