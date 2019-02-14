#pragma once

#include "common.h"
#include "error.h"
#include "net_address.h"

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

		Socket(const NetAddress& address, const TransportProtocol protocol = TransportProtocol::UDP)
			: m_address{ address }, m_protocol{ protocol }
		{
			m_socket = ::socket(
				// address family / network layer protocol
				m_address.protocol,
				// type of socket
				(m_protocol == TransportProtocol::UDP) ? Type::Datagram : Type::Stream,
				// if 0, OS pick the default implemented transport protocol for the given socket type
				m_protocol
			);
		}

		Socket(const Socket&) = delete;
		Socket& operator= (const Socket&) = delete;

		virtual ~Socket() = default;

		inline NativeSocketType getNativeSocket() const { return m_socket; }
		inline TransportProtocol getTransportProtocol() const { return m_protocol; }
		inline const NetAddress& getAddress() const { return m_address; }

		inline bool isValid() const 
		{ 
#if WIN32
			return m_socket != INVALID_SOCKET;
#else
			return m_socket > 0;
#endif
		}

		bool operator== (const Socket& other) const { return m_socket == other.m_socket; }
		bool operator!= (const Socket& other) const { return !(*this == other); }
		
		inline bool bind()
		{
			struct sockaddr_in addr_in {};
			addr_in.sin_family = m_address.protocol;
			addr_in.sin_port = htons(m_address.port);
#if WIN32
			InetPton(m_address.protocol, 
				std::wstring{ m_address.address.begin(), m_address.address.end() }.c_str(),
				&addr_in.sin_addr);
#else
			inet_pton(m_address.protocol, m_address.address.c_str(), &addr_in.sin_addr);
#endif

			return ::bind(m_socket, (sockaddr*)&addr_in, sizeof(addr_in)) >= 0;
		}

		inline bool close() 
		{
			return ::closesocket(m_socket);
		}

		inline bool shutdown(ShutdownMode mode = ShutdownMode::Send)
		{
			return ::shutdown(m_socket, mode) == 0;
		}

	private:

		// native socket data
		NativeSocketType m_socket;
		// nework address 
		NetAddress m_address;
		// transport layer protocol
		TransportProtocol m_protocol;
	};
}