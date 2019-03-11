#pragma once

#include "address.h"

namespace starnet
{
	class AddressBSD final : public Address
	{
	public:

		typedef sockaddr NativeAddressType;

		AddressBSD(const std::string& ip,
			const PortType port,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		virtual ~AddressBSD() override;

		inline const NativeAddressType& getNativeAddress() const { return m_address; }
		virtual std::size_t getNativeSize() const override;
		
		virtual bool isValid() const override;

	private:

		// native address type
		NativeAddressType m_address;

	};
}