#pragma once

#include "common.h"
#include "error.h"
#include "address.h"

namespace starnet
{
	// define a shared SocketType that match the platform specific type definition
#ifdef WIN32
	typedef SOCKET NativeSocketType;
#else
	typedef int NativeSocketType;
#endif

	// socket wrapper 
	class Socket
	{
	public:
		
		// transport layer protocol
		enum TransportProtocol
		{
			TCP = IPPROTO_TCP,
			UDP = IPPROTO_UDP
		};

		enum Type
		{
			// Raw = SOCK_RAW,
			Stream = SOCK_STREAM,
			Datagram = SOCK_DGRAM
		};

		enum ShutdownMode
		{
			Send = SD_SEND,
			Receive = SD_RECEIVE,
			Both = SD_BOTH
		};

		Socket(const Address& address, const TransportProtocol protocol = TransportProtocol::UDP)
			: m_address{ address }, m_protocol{ protocol }
		{
			m_socket = ::socket(
				// address family / network layer protocol
				m_address.getProtocol(),
				// type of socket
				(m_protocol == TransportProtocol::UDP) ? Type::Datagram : Type::Stream,
				// if 0, OS pick the default implemented transport protocol for the given socket type
				m_protocol
			);
		}

		Socket(const NativeSocketType socket, const Address& address, const TransportProtocol protocol = TransportProtocol::UDP)
			: m_socket{ socket }, m_address{ address }, m_protocol{ protocol }
		{

		}
		Socket(const Socket&) = delete;
		Socket& operator= (const Socket&) = delete;

		virtual ~Socket()
		{
			if (isValid())
				close();
		}

		inline NativeSocketType getNativeSocket() const { return m_socket; }
		inline TransportProtocol getTransportProtocol() const { return m_protocol; }
		inline const Address& getAddress() const { return m_address; }

		inline bool isValid() const 
		{ 
	#if PLATFORM_WINDOWS
				return m_socket != INVALID_SOCKET;
	#else
				return m_socket > 0;
	#endif
		}

		bool operator== (const Socket& other) const { return m_socket == other.m_socket; }
		bool operator!= (const Socket& other) const { return !(*this == other); }
		
		// Notify the operating system that a socket will use a specific address
		// and transport layer port.
		inline bool bind()
		{
			return ::bind(m_socket, &m_address.getNativeAddress(), m_address.getNativeSize()) >= 0;
		}

		// Close the socket
		inline bool close() 
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

		// Use to cease transmitting or receiving before closing the socket
		inline bool shutdown(ShutdownMode mode = ShutdownMode::Send)
		{
			return ::shutdown(m_socket, mode) == 0;
		}

		inline bool setNonBlockingMode(const bool active)
		{
#if PLATFORM_WINDOWS
			// Any nonzero value will enable non-blocking mode
			u_long arg = active ? 1 : 0;
			return ioctlsocket(m_socket, FIONBIO, &arg) != SOCKET_ERROR;
#else 
			// First need to fetch the flags currently associated with the socket,
			// bitwise them with the constant O_NONBLOCK and update the flags on the socket.
			int flags = fcntl(m_socket, F_GETFL, 0);
			flags = active ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
			return fcntl(m_socket, F_SETFL, flags) != SOCKET_ERROR;
#endif
		}
		
		inline static void select()
		{

		}

	protected:

		// native socket data
		NativeSocketType m_socket;
		// nework address 
		Address m_address;
		// transport layer protocol
		TransportProtocol m_protocol;
	};

	class UDPSocket final : public Socket
	{
	public:

		UDPSocket(const Address& address)
			: Socket(address, TransportProtocol::UDP)
		{

		}

		UDPSocket(const NativeSocketType socket, const Address& address)
			: Socket(socket, address, TransportProtocol::UDP)
		{

		}

		// Send data to a specific address
		inline bool send(const std::string& data, const Address& toAddress) const
		{
			return ::sendto(
				m_socket, 
				data.c_str(),
				data.length(), 
				0, 
				&toAddress.getNativeAddress(), 
				toAddress.getNativeSize()
			) >= 0;
		}

		// Receiving data from a specific address
		inline bool receive(std::string& data, Address& fromAddress) const
		{
			Address::NativeAddressType address{};
			int size = sizeof(address);

			// #todo: buffer size 
			char buffer[100];
			const int bytecount = ::recvfrom(
				m_socket,
				buffer,
				sizeof(buffer),
				0,
				&address,
				&size
			);
			if (bytecount >= 0)
			{
				data = { buffer, (unsigned int)bytecount };
				fromAddress = { address, m_address.getProtocol() };
				return true;
			}
			return false;
		}
	};

	class TCPSocket final : public Socket
	{
	public:

		TCPSocket(const Address& address)
			: Socket(address, TransportProtocol::TCP)
		{

		}

		TCPSocket(const NativeSocketType socket, const Address& address)
			: Socket(socket, address, TransportProtocol::TCP)
		{

		}

		// Calling connect initialized the TCP handshake by sending 
		// the initial SYN packet to a target host.
		// if the host has a listen socket bound to the appropriate port, 
		// it can proceed with the handshake by calling accept.
		inline bool connect(const Address& address)
		{
			return ::connect(m_socket, &address.getNativeAddress(), address.getNativeSize()) == 0;
		}

		// numOfMaxConnections is the maximum number of incoming 
		// connections that should be allowed to queue up.
		// Once the maximum number of handshakes are pending, 
		// any futher incoming connection is dropped.
		inline bool listen(unsigned int numOfMaxConnections = SOMAXCONN)
		{
			return ::listen(m_socket, numOfMaxConnections) == 0;
		}

		// accept an incoming connection and continue to the TCP handshake.
		inline TCPSocket* accept() const
		{
			Address::NativeAddressType address{};
			int size = sizeof(address);

			NativeSocketType newSocket = ::accept(
				m_socket,
				&address,
				&size
			);

			if (newSocket > 0)
			{
				return new TCPSocket(newSocket, { address, m_address.getProtocol() });
			}
			return nullptr;
		}

		// A connected TCP socket stores the remote host's address informaztion.
		// Because of this, a process does not need to pass an address. 
		inline bool send(const std::string& data)
		{
			// note that a nonzero return value does not imply any data
			// was sent, just that data was queued to be sent.
			return ::send(m_socket, data.c_str(), data.length(), 0) >= 0;
		}
		
		// Receive data con a connected TCP socket.
		inline bool receive(std::string& data) const
		{
			// #todo: buffer size 
			char buffer[100];
			const int bytecount = ::recv(
				m_socket,
				buffer,
				sizeof(buffer),
				0
			);
			if (bytecount >= 0)
			{
				data = { buffer, (unsigned int)bytecount };
				return true;
			}
			return false;
		}
	};
}