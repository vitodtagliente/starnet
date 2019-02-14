#pragma once

#include <cstdint>
#include <string>

namespace starnet
{
	struct NetAddress
	{		
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
		
		NetAddress(const std::string& in_address = localAddress, 
			const PortType in_port = unusedPort,
			const NetworkProtocol in_protocol = NetworkProtocol::IPv4)
			: address{ in_address }, port{ in_port }, protocol{ in_protocol }
		{

		}

		NetAddress(const NetAddress& other)
		{
			address = other.address;
			port = other.port;
			protocol = other.protocol;
		}

		inline bool operator== (const NetAddress& other) const
		{
			return address == other.address &&
				port == other.port &&
				protocol == other.protocol;
		}

		inline bool operator!= (const NetAddress& other) const 
		{
			return !(*this == other);
		}

		inline NativeAddressType getNativeAddress() const
		{
			NativeAddressType addr {};
			NativeAddresInType* addr_in = reinterpret_cast<NativeAddresInType*>(&addr);
			addr_in->sin_family = protocol;
			addr_in->sin_port = htons(port);
#if WIN32
			InetPton(protocol,
				std::wstring{ address.begin(), address.end() }.c_str(),
				&addr_in->sin_addr);
#else
			inet_pton(protocol, address.c_str(), &addr_in->sin_addr);
#endif
			return addr;
		}

		std::string address;
		uint16_t port;
		NetworkProtocol protocol;

		static const std::string localAddress;
		static const PortType unusedPort;
	};

	const std::string NetAddress::localAddress{ "127.0.0.1" };
	const uint16_t NetAddress::unusedPort{ 0 };
}