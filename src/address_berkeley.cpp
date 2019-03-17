#include "..\starnet\address.h"

#ifdef BERKELEY_SUBSYSTEM

// #todo: implements IPv6

namespace starnet
{
	Address::Address(const std::string & ip, const port_t port, const NetworkProtocol protocol)
		: m_ip(ip), m_port(port), m_protocol(protocol)
	{
		uint8_t native_protocol{};
		switch (protocol)
		{
		case NetworkProtocol::IPv4:	
			native_protocol = (uint8_t)AF_INET;	
			break;
		case NetworkProtocol::IPv6:	
			native_protocol = (uint8_t)AF_INET6; 
			break;
		case NetworkProtocol::Unknown:
		default: 
			native_protocol = (uint8_t)AF_UNSPEC; 
			break;
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
	
}

#endif