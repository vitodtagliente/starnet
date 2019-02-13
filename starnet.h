#pragma once

#include <functional>
#include <iostream>
#include "common.h"
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

	// override this function to define custom log behaviour
	std::function<void(const std::string&)> log = [](const std::string& text) 
	{
		std::cout << text << std::endl;
	};

	bool shutdown()
	{
#if WIN32 
		return WSACleanup() == 0;
#else 
		// Unix
#endif
	}
}