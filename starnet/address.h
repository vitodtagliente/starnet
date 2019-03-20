#pragma once

#include <cassert>
#include <cstdint>
#include <string>
#include "common.h"

namespace starnet
{
	// identify the network protocol
	enum class NetworkProtocol
	{
		Unknown,
		IPv4,
		IPv6
	};

	class Address
	{
	public:

		// native address type
		using native_addr_t = sockaddr;

		Address() : m_protocol(NetworkProtocol::Unknown) {} 
		Address(const NetworkProtocol protocol) : m_protocol(protocol) {}
		Address(const native_addr_t& address) : m_address(address)
		{
			// to be implemented
			// retrieve the protocol
		}
		virtual ~Address() = default;

		inline const native_addr_t& getNativeAddress() const { return m_address; }
		inline std::size_t getNativeSize() const { return sizeof(m_address); }
		inline NetworkProtocol getProtocol() const { return m_protocol; }

		virtual bool isValid() const
		{
			return m_protocol != NetworkProtocol::Unknown;
		}

		inline operator bool() const { return isValid(); }

		bool operator== (const Address& other) const
		{
			// to be implemented
			return m_protocol == other.m_protocol;
		}

		inline bool operator!= (const Address& other) const
		{
			return !(*this == other);
		}

	protected:

		// native address type
		native_addr_t m_address{};
		// network protocol
		NetworkProtocol m_protocol;
	};

	template<NetworkProtocol protocol>
	class NetworkAddress : public Address
	{
	public:

		// port type 
		using port_t = uint16_t;

		NetworkAddress(const std::string& ip, const port_t port) : Address(protocol)
		{
			static_assert(protocol != NetworkProtocol::Unknown, "Unknown NetworkProtocol");

			initialize(ip, port);
		}
		// @param address in format like 127.0.0.1:8080 -> ip_address:port_number
		NetworkAddress(const std::string& address) : Address(protocol)
		{
			static_assert(protocol != NetworkProtocol::Unknown, "Unknown NetworkProtocol");

			const auto separator = address.find_last_of(':');

			assert(separator != std::string::npos && "address is not of address:port form");
			assert(separator != address.size() - 1 && "address has ':' as last character. Expected port number here");

			// isolate address
			const std::string& ip = address.substr(0, separator);

			// std::stoul converts string to unsigned integer
			const auto parsed_port = std::stoul(address.substr(separator + 1).c_str(), nullptr, 10);
			// check if it is a valid port, (0, 65535) range
			assert(parsed_port < (1 << 16) && "invalid port number");

			const port_t port = static_cast<port_t>(parsed_port);

			initialize(ip, port);
		}

		virtual ~NetworkAddress() override {};

		inline std::string getIP() const
		{
			return {};
		}

		inline port_t getPort() const
		{
			if constexpr (protocol == NetworkProtocol::IPv4)
			{
				sockaddr_in* addr_in = reinterpret_cast<sockaddr_in*>(&m_address);
				return ntohs(addr_in->sin_port);
			}
			else // IPv6
			{
				// to be implemented
				sockaddr_in6* addr_in = reinterpret_cast<sockaddr_in6*>(&m_address);
				return ntohs(addr_in->sin6_port);
			}
		}

	private:

		void initialize(const std::string& ip, const port_t port)
		{			
			if constexpr (protocol == NetworkProtocol::IPv4)
			{
				sockaddr_in* addr_in = reinterpret_cast<sockaddr_in*>(&m_address);
				addr_in->sin_port = htons(port);
#if PLATFORM_WINDOWS
				InetPton(AF_INET, ip.c_str(), &addr_in->sin_addr);
#else
				inet_pton(AF_INET, ip.c_str(), &addr_in->sin_addr);
#endif
			}
			else // IPv6
			{
				// to be implemented
			}
		}
	};
}