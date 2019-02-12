#pragma once

#include "common.h"
#include "net_address.h"

namespace starnet
{
	class NetStream
	{
	public:

		NetStream(const SOCKET& socket) 
		{
			m_socket = socket;
		}

		virtual ~NetStream() = default;

		virtual size_t send(const void* data, size_t size)
		{
			return 0;
		}

		virtual size_t receive(void* data, size_t size)
		{
			return 0;
		}

	protected:

		// stream socket
		SOCKET m_socket;

	};
}