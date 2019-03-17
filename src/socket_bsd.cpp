#include "../starnet/socket_bsd.h"
#include "../starnet/address_bsd.h"

namespace starnet
{
	bool SocketBSD::bind(const Address& address)
	{
		const AddressBSD& addressBSD = static_cast<const AddressBSD&>(address);
		return ::bind(m_socket, &addressBSD.getNativeAddress(), addressBSD.getNativeSize()) == 0;
	}

	bool SocketBSD::connect(const Address& address)
	{
		const AddressBSD& addressBSD = static_cast<const AddressBSD&>(address);
		return ::connect(m_socket, &addressBSD.getNativeAddress(), addressBSD.getNativeSize()) == 0;
	}

	bool SocketBSD::listen(unsigned int numOfMaxConnections)
	{
		return ::listen(m_socket, numOfMaxConnections) == 0;
	}

	Socket* SocketBSD::accept() const
	{
		native_socket_t newSocket = ::accept(m_socket, NULL, NULL);
		if (newSocket != INVALID_SOCKET)
		{
			return new SocketBSD(newSocket, m_type);
		}
		return nullptr;
	}

	Socket* SocketBSD::accept(Address & outAddress) const
	{
		AddressBSD::NativeAddressType address{};
#if PLATFORM_WINDOWS
		int size = sizeof(address);
#else 
		unsigned int size = sizeof(address);
#endif

		native_socket_t newSocket = ::accept(
			m_socket,
			&address,
			&size
		);

		if (newSocket != INVALID_SOCKET)
		{
			//return new SocketBSD(newSocket, { address, m_address.getProtocol() });
		}
		return nullptr;
	}

	bool SocketBSD::send(const uint8_t * data, const std::size_t count, int32_t & byteSent)
	{
		// note that a nonzero return value does not imply any data
		// was sent, just that data was queued to be sent.
		return ::send(m_socket, reinterpret_cast<const char*>(data), count, 0) >= 0;
	}

	bool SocketBSD::sendTo(const Address & address, const uint8_t * data, const std::size_t count, int32_t & byteSent)
	{
		const AddressBSD& addressBSD = static_cast<const AddressBSD&>(address);
		return ::sendto(
			m_socket,
			reinterpret_cast<const char*>(data),
			count,
			0,
			&addressBSD.getNativeAddress(),
			addressBSD.getNativeSize()
		) >= 0;
	}

	bool SocketBSD::receive(uint8_t * data, std::size_t bufferSize, int32_t & bytesRead)
	{
		const int bytecount = ::recv(
			m_socket,
			reinterpret_cast<char*>(data),
			bufferSize,
			0
		);

		if (bytesRead >= 0)
		{
			// For Streaming sockets, 0 indicates a graceful failure
			return (m_type != Socket::Type::Stream) || (bytesRead > 0);
		}
		return false;
	}

	bool SocketBSD::receiveFrom(Address& address, uint8_t* data, std::size_t bufferSize, int32_t& bytesRead)
	{
#if PLATFORM_WINDOWS
		int size = sizeof(address);
#else 
		unsigned int size = sizeof(address);
#endif

		// #todo: buffer size 
		char buffer[100];

		/*
		bytesRead = ::recvfrom(
			m_socket,
			reinterpret_cast<char*>(data),
			bufferSize,
			0,
			&address,
			&size
		);
		*/

		if (bytesRead >= 0)
		{
			// For Streaming sockets, 0 indicates a graceful failure
			return (m_type != Socket::Type::Stream) || (bytesRead > 0);
		}
		return false;
	}

	Socket::ConnectionState SocketBSD::getConnectionState() const
	{
		return ConnectionState::NotConnected;
	}

	Address & SocketBSD::getAddress() const
	{
		// TODO: inserire l'istruzione return qui
	}

	bool SocketBSD::setNonBlockingMode(const bool isNonBlocking)
	{
#if PLATFORM_WINDOWS
		// Any nonzero value will enable non-blocking mode
		u_long arg = isNonBlocking ? 1 : 0;
		return ioctlsocket(m_socket, FIONBIO, &arg) != SOCKET_ERROR;
#else 
		// First need to fetch the flags currently associated with the socket,
		// bitwise them with the constant O_NONBLOCK and update the flags on the socket.
		int flags = fcntl(m_socket, F_GETFL, 0);
		flags = active ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
		return fcntl(m_socket, F_SETFL, flags) != -1;
#endif
	}

	bool SocketBSD::setBroadcastMode(const bool isBroadcast)
	{
		int Param = isBroadcast ? 1 : 0;
		return setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&Param, sizeof(Param)) == 0;
	}

	bool SocketBSD::setSendBufferSize(const std::size_t size)
	{
		return false;
	}

	bool SocketBSD::setReceiveBufferSize(const std::size_t size)
	{
		return false;
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