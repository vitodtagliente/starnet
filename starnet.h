#pragma once

#include "net_address.h"
#include "net_stream.h"
#include "socket.h"

namespace starnet
{
	bool startup()
	{
#if WIN32
		LPWSADATA WSAData;
		return WSAStartup(MAKEWORD(2, 2), WSAData) == 0;
#else
		// Unix
#endif
	}

	bool shutdown()
	{
#if WIN32 
		return WSACleanup() == 0;
#else 
		// Unix
#endif
	}
}