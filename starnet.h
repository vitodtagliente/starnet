#pragma once

#include "common.h"
#include "error.h"
#include "net_address.h"
#include "net_stream.h"
#include "socket.h"

namespace starnet
{
	bool startup()
	{
#if WIN32
		WSADATA wsaData;
		WORD dllVersion = MAKEWORD(2, 2);
		return WSAStartup(dllVersion, &wsaData) == 0;
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