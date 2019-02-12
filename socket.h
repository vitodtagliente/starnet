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

		Socket(const NetAddress& address, const Type type = Type::UDP)
			: m_address{ address }, m_type{ type }
		{
			m_socket = socket(
				address.getFamily(),
				(m_type == Type::UDP) ? SOCK_DGRAM : SOCK_STREAM,
				(m_type == Type::UDP) ? IPPROTO_UDP : IPPROTO_TCP
			);
		}

		Socket(const Socket& socket)
		{
			m_socket = socket.m_socket;
			m_address = socket.m_address;
			m_type = socket.m_type;
		}

		virtual ~Socket() = default;

		inline const SOCKET& getSocket() const { return m_socket; }
		inline const NetAddress& getAddress() const { return m_address; }
		inline Type getType() const { return m_type; }

		inline bool isValid() const { return m_socket != INVALID_SOCKET; }

		bool operator== (const Socket& other) const = delete;
		bool operator!= (const Socket& other) const = delete;

	private:

		/*
		inline bool bind()
		{
			if (::bind(0, &m_address.getSocketAddress(), m_address.getSize()) != BindSuccess)
			{
				// #todo: error management
				return false;
			}
			return true;
		}
		*/

		// socket data
		SOCKET m_socket;
		// socket address
		NetAddress m_address;
		// socket type
		Type m_type;

		//static const int BindSuccess;
	};

	//const int Socket::BindSuccess{ 0 };
}