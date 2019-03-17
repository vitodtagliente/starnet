#pragma once

#include "address.h"

/*
	Network address implementation for Berkeley sockets.
*/

namespace starnet
{
	class AddressBSD final : public Address
	{
	public:

		using native_addr_t = sockaddr;

		AddressBSD(const std::string& ip,
			const port_t port,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		virtual ~AddressBSD() override;

		inline const native_addr_t& getNativeAddress() const { return m_address; }
		inline std::size_t getNativeSize() const { return sizeof(m_address); }

	private:

		// native address type
		native_addr_t m_address;

	};
}