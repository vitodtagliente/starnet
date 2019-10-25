#include "http_server.h"

namespace starnet
{
	HTTPServer::HTTPServer(const Address& address, const unsigned int maxConnections)
		: m_socket(new Socket(address, Socket::TransportProtocol::TCP))
		, m_maxConnections(maxConnections)
	{

	}

	bool HTTPServer::listen()
	{
		return m_socket->bind() && m_socket->listen(m_maxConnections);
	}

	void HTTPServer::close()
	{
	}

}