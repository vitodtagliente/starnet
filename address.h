#pragma once

#include <cstdint>
#include <string>
#include "common.h"

namespace starnet
{
	class Address
	{	
	public:

		typedef sockaddr NativeAddressType;
		typedef sockaddr_in NativeAddresInType;
		typedef uint16_t PortType;

		// defined as address family in socket terminology, 
		// indicates the network layer protocol which the socket should employ.
		enum NetworkProtocol
		{
			IPv4 = AF_INET,
			IPv6 = AF_INET6
		};
		
		Address(const std::string& address = localAddress, 
			const PortType port = unusedPort,
			const NetworkProtocol protocol = NetworkProtocol::IPv4)
			: m_protocol{ protocol }, m_address{}
		{
			// #todo: this is IPv4 only implementation
			NativeAddresInType* addr_in = reinterpret_cast<NativeAddresInType*>(&m_address);
			addr_in->sin_family = protocol;
			addr_in->sin_port = htons(port);
#if PLATFORM_WINDOWS
			InetPton(protocol,
				std::wstring{ address.begin(), address.end() }.c_str(),
				&addr_in->sin_addr);
#else
			inet_pton(protocol, address.c_str(), &addr_in->sin_addr);
#endif
		}

		Address(const NativeAddressType& address, const NetworkProtocol protocol)
			: m_address{ address }, m_protocol{ protocol }
		{

		}

		Address(const Address& other)
		{
			m_address = other.m_address;
			m_protocol = other.m_protocol;
		}
		
		inline NetworkProtocol getProtocol() const { return m_protocol; }
		inline const NativeAddressType& getNativeAddress() const { return m_address; }
		inline size_t getNativeSize() const { return sizeof(m_address); }

		static const std::string localAddress;
		static const PortType unusedPort;

	private:

		NetworkProtocol m_protocol;
		NativeAddressType m_address;

	};

	const std::string Address::localAddress{ "127.0.0.1" };
	const Address::PortType Address::unusedPort{ 0 };
}