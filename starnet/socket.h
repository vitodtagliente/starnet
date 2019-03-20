#pragma once

#include "address.h"
#include "platform.h"

namespace starnet
{
	// transport protocol
	enum class TransportProtocol
	{
		Unknown,
		TCP,
		UDP
	};

	class Socket
	{
	public:

		// native socket type
		using native_socket_t =
#ifdef PLATFORM_WINDOWS
		SOCKET
#else 
		int
#endif
		;

		// indicates the type of socket being used
		enum class Type
		{
			Unknown,
			// UDP type socket
			Datagram,
			// TCP type socket 
			Stream
		};


		// indicates the connection state of the socket
		enum class ConnectionState
		{
			NotConnected,
			Connected,
			Error
		};

		enum class ShutdownMode
		{
			// disable reading on the socket
			Read,
			// disable writing on the socket
			Write,
			// disable reading and writing on the socket
			Both
		};

		Socket(const Address& address, const TransportProtocol protocol) 
			: m_address(address), m_protocol(protocol) 
		{}
		Socket(const native_socket_t socket, const Address& address, const TransportProtocol protocol) 
			: m_socket(socket), m_address(address), m_protocol(protocol) 
		{}
		virtual ~Socket() = default;

		inline TransportProtocol getProtocol() const { return m_protocol; }
		inline const Address& getAddress() const { return m_address; }

		bool bind()
		{
			return ::bind(m_socket, &m_address.getNativeAddress(), m_address.getNativeSize()) == 0;
		}

		bool setNonBlockingMode(const bool isNonBlocking = true)
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
		bool setBroadcastMode(const bool isBroadcast = true)
		{
			int Param = isBroadcast ? 1 : 0;
			return setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&Param, sizeof(Param)) == 0;
		}

		bool setSendBufferSize(const std::size_t size)
		{
			// to be implemented
			return false;
		}
		bool setReceiveBufferSize(const std::size_t size)
		{
			// to be implemented
			return false;
		}

		// shuts down the socket
		bool shutdown(ShutdownMode mode)
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
		// close the socket
		bool close()
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

		bool isValid() const
		{
			return m_socket != INVALID_SOCKET;
		}
		inline operator bool() const { return isValid(); }

	protected:

		// native socket type
		native_socket_t m_socket{};
		// socket address
		Address m_address;
		// transport protocol
		TransportProtocol m_protocol;
	};

	template<TransportProtocol protocol>
	class NetworkSocket : public Socket
	{
	public:

	private:
	};

	class Socket
	{
	public:

		// native socket type
		using native_socket_t =
#ifdef PLATFORM_WINDOWS
		SOCKET
#else 
		int
#endif
		;

		// indicates the type of socket being used
		enum class Type
		{
			Unknown,
			// UDP type socket
			Datagram,
			// TCP type socket 
			Stream
		};

		// indicates the connection state of the socket
		enum class ConnectionState
		{
			NotConnected,
			Connected,
			Error
		};

		enum class ShutdownMode
		{			
			// disable reading on the socket
			Read,
			// disable writing on the socket
			Write,
			// disable reading and writing on the socket
			Both
		};

		Socket(const Address& address, const TransportProtocol protocol);
		Socket(const native_socket_t socket, const Address& address, const TransportProtocol protocol);
		~Socket();

		inline Type getType() const { return m_type; }
		uint8_t getNativeType() const;
		inline TransportProtocol getProtocol() const { return m_protocol; }
		uint8_t getNativeProtocol() const;

		// Notify the operating system that a socket will use a specific address
		// and transport layer port.
		bool bind();
		// Calling connect initialized the TCP handshake by sending 
		// the initial SYN packet to a target host.
		// if the host has a listen socket bound to the appropriate port, 
		// it can proceed with the handshake by calling accept.
		bool connect(const Address& address);
		// numOfMaxConnections is the maximum number of incoming 
		// connections that should be allowed to queue up.
		// Once the maximum number of handshakes are pending, 
		// any futher incoming connection is dropped.
		bool listen(unsigned int numOfMaxConnections);
		// accept an incoming connection and continue to the handshake.
		class Socket* accept() const;

		// A connected socket stores the remote host's address information.
		// Because of this, a process does not need to pass an address. 
		// @param data The buffer to send
		// @param count The size of the data to send
		// @param byteSent Will indicate how much was sent
		bool send(const uint8_t* data, const std::size_t count, int32_t& byteSent);
		// Send data to a specific address
		bool sendTo(const Address& address, const uint8_t* data, const std::size_t count, int32_t& byteSent);

		bool receive(uint8_t* data, std::size_t bufferSize, int32_t& bytesRead);
		bool receiveFrom(Address& address, uint8_t* data, std::size_t bufferSize, int32_t& bytesRead);

		ConnectionState getConnectionState() const;

		const Address& getAddress() const { return m_address; }

		bool setNonBlockingMode(const bool isNonBlocking = true);
		bool setBroadcastMode(const bool isBroadcast = true);

		bool setSendBufferSize(const std::size_t size);
		bool setReceiveBufferSize(const std::size_t size);

		// shuts down the socket
		bool shutdown(ShutdownMode mode);
		// close the socket
		bool close();

		bool isValid() const;
		inline operator bool() const { return isValid(); }

	private:

		// native socket 
		native_socket_t m_socket;
		// socket address
		Address m_address;
		// indicates the socket type
		Type m_type;
		// indicates the transport protocol
		TransportProtocol m_protocol;
	};
}