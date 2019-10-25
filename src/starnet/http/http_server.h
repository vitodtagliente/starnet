#pragma once

#include <thread>
#include "../socket.h"

namespace starnet
{
	class HTTPServer
	{
	public:

		HTTPServer(const Address& address, const unsigned int maxConnections);

		// retrieve the socket
		Socket* const getSocket() const { return m_socket; }

		bool listen();
		void close();

	private:

		// server socket
		Socket* m_socket;
		// max connections the server can manage
		unsigned int m_maxConnections;
	};
}