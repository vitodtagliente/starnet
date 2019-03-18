#include "../starnet/socket.h"

namespace starnet
{
	Socket::Socket(const Address& address, const TransportProtocol protocol)
		: m_address(address), m_protocol(protocol)
	{
		m_socket = ::socket(
			// address family / network layer protocol
			m_address.getNativeProtocol(),
			// type of socket
			getNativeType(),
			// if 0, OS pick the default implemented transport protocol for the given socket type
			getNativeProtocol()
		);
	}

	Socket::Socket(const native_socket_t socket, const Address& address, const TransportProtocol protocol)
		: m_socket(socket), m_address(address), m_protocol(protocol)
	{
		switch (protocol)
		{
		case TransportProtocol::UDP:
			m_type = Type::Datagram;
			break;
		case TransportProtocol::TCP:
			m_type = Type::Stream;
			break;
		case TransportProtocol::Unknown:
		default:
			m_type = Type::Unknown;
			break;
		}
	}

	Socket::~Socket()
	{

	}

	uint8_t Socket::getNativeType() const
	{
		switch (m_type)
		{
		case Type::Datagram:
			return SOCK_DGRAM;
			break;
		case Type::Stream:
			return SOCK_STREAM;
			break;
		case Type::Unknown:
		default:
			return 0;
			break;
		}
	}

	uint8_t Socket::getNativeProtocol() const
	{
		switch (m_protocol)
		{
		case TransportProtocol::TCP:
			return IPPROTO_TCP;
			break;
		case TransportProtocol::UDP:
			return IPPROTO_UDP;
			break;
		case TransportProtocol::Unknown:
		default:
			return 0;
			break;
		}
	}

	bool Socket::bind()
	{
		return ::bind(m_socket, &m_address.getNativeAddress(), m_address.getNativeSize()) == 0;
	}

	bool Socket::connect(const Address& address)
	{
		return ::connect(m_socket, &address.getNativeAddress(), address.getNativeSize()) == 0;
	}

	bool Socket::listen(unsigned int numOfMaxConnections)
	{
		return ::listen(m_socket, numOfMaxConnections) == 0;
	}

	Socket* Socket::accept() const
	{
		Address::native_addr_t address{};
#if PLATFORM_WINDOWS
		int size = sizeof(address);
#else 
		unsigned int size = sizeof(address);
#endif

		native_socket_t newSocket = ::accept(m_socket, &address, &size);
		if (newSocket != INVALID_SOCKET)
		{
			return new Socket(newSocket, { address, m_address.getNetworkProtocol() }, m_protocol);
		}
		return nullptr;
	}

	bool Socket::send(const uint8_t* data, const std::size_t count, int32_t& byteSent)
	{
		// note that a nonzero return value does not imply any data
		// was sent, just that data was queued to be sent.
		return ::send(m_socket, reinterpret_cast<const char*>(data), count, 0) >= 0;
	}

	bool Socket::sendTo(const Address& address, const uint8_t* data, const std::size_t count, int32_t& byteSent)
	{
		return ::sendto(
			m_socket,
			reinterpret_cast<const char*>(data),
			count,
			0,
			&address.getNativeAddress(),
			address.getNativeSize()
		) >= 0;
	}

	bool Socket::receive(uint8_t* data, std::size_t bufferSize, int32_t& bytesRead)
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

	bool Socket::receiveFrom(Address& address, uint8_t* data, std::size_t bufferSize, int32_t& bytesRead)
	{
		Address::native_addr_t native_address{};

#if PLATFORM_WINDOWS
		int size = sizeof(address);
#else 
		unsigned int size = sizeof(address);
#endif
	
		bytesRead = ::recvfrom(
			m_socket,
			reinterpret_cast<char*>(data),
			bufferSize,
			0,
			&native_address,
			&size
		);

		if (bytesRead >= 0)
		{
			// For Streaming sockets, 0 indicates a graceful failure
			return (m_type != Socket::Type::Stream) || (bytesRead > 0);
		}
		return false;
	}

	Socket::ConnectionState Socket::getConnectionState() const
	{
		return ConnectionState::NotConnected;
	}

	bool Socket::setNonBlockingMode(const bool isNonBlocking)
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

	bool Socket::setBroadcastMode(const bool isBroadcast)
	{
		int Param = isBroadcast ? 1 : 0;
		return setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&Param, sizeof(Param)) == 0;
	}

	bool Socket::setSendBufferSize(const std::size_t size)
	{
		return false;
	}

	bool Socket::setReceiveBufferSize(const std::size_t size)
	{
		return false;
	}

	bool Socket::shutdown(ShutdownMode mode)
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

	bool Socket::close()
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