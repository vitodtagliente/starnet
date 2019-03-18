#include "..\starnet\address.h"
#include <cassert>

// #todo: implements IPv6

namespace starnet
{
	Address::Address(const std::string& ip, const port_t port, const NetworkProtocol protocol)
		: m_ip(ip), m_port(port), m_protocol(protocol)
	{
		nativeInit();
	}

	Address::Address(const std::string& address, const NetworkProtocol protocol)
		: m_protocol(protocol)
	{
		const auto separator = address.find_last_of(':');

		assert(separator != std::string::npos && "address is not of address:port form");
		assert(separator != address.size() - 1 && "address has ':' as last character. Expected port number here");

		// isolate address
		m_ip = address.substr(0, separator);

		// std::stoul converts string to unsigned integer
		const auto parsed_port = std::stoul(address.substr(separator + 1).c_str(), nullptr, 10);
		// check if it is a valid port, (0, 65535) range
		assert(parsed_port < (1 << 16) && "invalid port number");

		m_port = static_cast<port_t>(parsed_port);

		nativeInit();
	}

	Address::Address(const native_addr_t & address, const NetworkProtocol protocol)
		: m_protocol(protocol), m_address(address)
	{
	}

	bool Address::isValid() const
	{
		return m_protocol != NetworkProtocol::Unknown;
	}

	uint8_t Address::getNativeProtocol() const
	{
		switch (m_protocol)
		{
		case NetworkProtocol::IPv4:
			return (uint8_t)AF_INET;
			break;
		case NetworkProtocol::IPv6:
			return (uint8_t)AF_INET6;
			break;
		case NetworkProtocol::Unknown:
		default:
			return (uint8_t)AF_UNSPEC;
			break;
		}
	}

	void Address::nativeInit()
	{
		const uint8_t native_protocol = getNativeProtocol();
		// #todo: this is IPv4 only implementation
		sockaddr_in* addr_in = reinterpret_cast<sockaddr_in*>(&m_address);
		addr_in->sin_family = native_protocol;
		addr_in->sin_port = htons(m_port);
#if PLATFORM_WINDOWS
		InetPton(native_protocol, m_ip.c_str(), &addr_in->sin_addr);
#else
		inet_pton(native_protocol, m_ip.c_str(), &addr_in->sin_addr);
#endif
	}

}