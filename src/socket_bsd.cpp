#include "../starnet/socket_bsd.h"

namespace starnet
{
	bool SocketBSD::bind(const Address & address)
	{
		return ::bind(m_socket, &address.getNativeAddress(), address.getNativeSize()) == 0;
	}

	bool SocketBSD::connect(const Address & address)
	{
		return ::connect(m_socket, &address.getNativeAddress(), address.getNativeSize()) == 0;
	}

	bool SocketBSD::listen(unsigned int numOfMaxConnections)
	{
		return ::listen(m_socket, numOfMaxConnections) == 0;
	}

	Socket* SocketBSD::accept() const
	{
		return nullptr;
	}

	Socket* SocketBSD::accept(Address & outAddress) const
	{
		return nullptr;
	}

	bool SocketBSD::shutdown(ShutdownMode mode)
	{
		int platformMode = 0;
#if PLATFORM_WINDOWS
		switch (mode)
		{
		case ShutdownMode::Read:
			platformMode = SD_RECEIVE;
			break;
		case ShutdownMode::Write:
			platformMode = SD_SEND;
			break;
		case ShutdownMode::Both:
			platformMode = SD_BOTH;
			break;
		}
#else
		switch (mode)
		{
		case ShutdownMode::Read:
			platformMode = SHUT_RD;
			break;
		case ShutdownMode::Write:
			platformMode = SHUT_WR;
			break;
		case ShutdownMode::Both:
			platformMode = SHUT_RDWR;
			break;
		}
#endif
		return ::shutdown(m_socket, platformMode) == 0;
	}

	bool SocketBSD::close()
	{
#if PLATFORM_WINDOWS
		if (::closesocket(m_socket) == 0)
		{
			m_socket = INVALID_SOCKET;
			return true;
		}
#else
		if (::close(m_socket) == 0)
		{
			m_socket = 0;
			return true;
		}
#endif			
		return false;
	}
}