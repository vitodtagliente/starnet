#pragma once

#include "common.h"
#include "net_address.h"

namespace starnet
{
#ifdef WIN32
	typedef SOCKET PlatformSocket;
#else
	typedef int PlatformSocket;
#endif

	// socket wrapper 
	class Socket
	{
	public:

		enum class Type
		{
			TCP,
			UDP
		};

		enum Shutdown
		{
			Send = SD_SEND,
			Receive = SD_RECEIVE,
			Both = SD_BOTH
		};

		Socket(const Type type = Type::UDP)
			: m_socket{ INVALID_SOCKET }, m_type{ type }
		{ 
		
		}

		Socket(const Socket& socket)
		{
			m_socket = socket.m_socket;
			m_type = socket.m_type;
		}

		virtual ~Socket() = default;

		inline PlatformSocket getSocket() const { return m_socket; }
		inline Type getType() const { return m_type; }

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

		inline bool initialize(const NetAddress::Family family)
		{
			m_socket = socket(
				// address family, network layer protocol
				family,
				// type of socket
				(m_type == Type::UDP) ? SOCK_DGRAM : SOCK_STREAM,
				// if 0, OS pick the default implemented transport protocol for the given socket type
				(m_type == Type::UDP) ? IPPROTO_UDP : IPPROTO_TCP
			);
			return isValid();
		}

		inline bool bind(const NetAddress& address)
		{
			if (::bind(m_socket, &address.getSocketAddress(), address.getSize()) != 0)
			{
				// #todo: error management
				return false;
			}
			return true;
		}

		inline bool close() 
		{
			return ::closesocket(m_socket);
		}

		inline bool shutdown(Shutdown mode = Shutdown::Send)
		{
			return ::shutdown(m_socket, mode) == 0;
		}

	private:

		// socket data
		PlatformSocket m_socket;
		// socket type
		Type m_type;
	};
}