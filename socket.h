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
			m_socket = socket(address.getFamily(), SOCK_DGRAM, IPPROTO_UDP);
		}

		virtual ~Socket() = default;

		inline const SOCKET& getSocket() const { return m_socket; }
		inline const NetAddress& getAddress() const { return m_address; }
		inline Type getType() const { return m_type; }

		inline bool isValid() const { return m_socket != INVALID_SOCKET; }

		inline bool bind()
		{
			if (::bind(0, &m_address.getSocketAddress(), m_address.getSize()) != BindSuccess)
			{
				// #todo: error management
				return false;
			}
			return true;
		}

	private:

		// socket data
		SOCKET m_socket;
		// socket address
		NetAddress m_address;
		// socket type
		Type m_type;

		static const int BindSuccess;
	};

	const int Socket::BindSuccess{ 0 };
}