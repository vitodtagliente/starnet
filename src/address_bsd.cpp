#include "..\starnet\address_bsd.h"

namespace starnet
{
	AddressBSD::AddressBSD(const std::string & ip, const PortType port, const NetworkProtocol protocol)
		: Address(ip, port, protocol)
	{
		uint8_t native_protocol;
		switch (protocol)
		{
		case NetworkProtocol::IPv4:	native_protocol = (uint8_t)AF_INET;	break;
		case NetworkProtocol::IPv6:	native_protocol = (uint8_t)AF_INET6; break;
		default: native_protocol = (uint8_t)AF_UNSPEC; break;
		}

		// #todo: this is IPv4 only implementation
		sockaddr_in* addr_in = reinterpret_cast<sockaddr_in*>(&m_address);
		addr_in->sin_family = native_protocol;
		addr_in->sin_port = htons(port);
#if PLATFORM_WINDOWS
		InetPton(native_protocol, ip.c_str(), &addr_in->sin_addr);
#else
		inet_pton(native_protocol, ip.c_str(), &addr_in->sin_addr);
#endif
	}

	AddressBSD::~AddressBSD()
	{
		m_address = NativeAddressType{};
		m_protocol = NetworkProtocol::Unknown;
	}

	std::size_t AddressBSD::getNativeSize() const
	{
		return sizeof(m_address);
	}

	bool AddressBSD::isValid() const
	{
		return m_protocol != NetworkProtocol::Unknown;
	}
}
