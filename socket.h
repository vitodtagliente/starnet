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

		virtual ~Socket() = default;

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
		
		inline bool bind()
		{
			return ::bind(m_socket, &m_address.getNativeAddress(), m_address.getNativeSize()) >= 0;
		}

		inline bool close() 
		{
#if PLATFORM_WINDOWS
			return ::closesocket(m_socket);
#else
			return ::close(m_socket);
#endif			
		}

		inline bool shutdown(ShutdownMode mode = ShutdownMode::Send)
		{
			return ::shutdown(m_socket, mode) == 0;
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

		inline bool receive(std::string& message, Address& fromAddress) const 
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
				message = { buffer, (unsigned int)bytecount };
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

		// calling connect initialized the TCP handshake by sending 
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

		inline bool send(const std::string& message)
		{
			// note that a nonzero return value does not imply any data
			// was sent, just that data was queued to be sent.
			return ::send(m_socket, message.c_str(), message.length(), 0) >= 0;
		}
		
		inline bool receive(std::string& message) const
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
				message = { buffer, (unsigned int)bytecount };
				return true;
			}
			return false;
		}
	};
}