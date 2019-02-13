#pragma once

#include "common.h"
#include "net_address.h"

namespace starnet
{
	// socket wrapper 
	class Socket
	{
	public:

		enum class Type
		{
			TCP,
			UDP
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

		inline const SOCKET& getSocket() const { return m_socket; }
		inline Type getType() const { return m_type; }

		inline bool isValid() const { return m_socket != INVALID_SOCKET; }

		bool operator== (const Socket& other) const { return m_socket == other.m_socket; }
		bool operator!= (const Socket& other) const { return !(*this == other); }

		inline bool bind(const NetAddress& address)
		{
			if (::bind(0, &address.getSocketAddress(), address.getSize()) != BindSuccess)
			{
				// #todo: error management
				return false;
			}
			return true;
		}

	private:

		inline void initialize(const NetAddress::AddressFamily family)
		{
			m_socket = socket(
				family,
				(m_type == Type::UDP) ? SOCK_DGRAM : SOCK_STREAM,
				(m_type == Type::UDP) ? IPPROTO_UDP : IPPROTO_TCP
			);
		}

		// socket data
		SOCKET m_socket;
		// socket type
		Type m_type;

		static const int BindSuccess;
	};

	const int Socket::BindSuccess{ 0 };
}