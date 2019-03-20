#pragma once

#include <cstdint>
#include <string>
#include "common.h"

/*
	#todo: add support for the "127.0.0.1:8080" address resolving
		   and the www.google.com resolving (DNS)
*/

namespace starnet
{
	class Address
	{	
	public:
		
		// port type 
		using port_t = uint16_t;
		// native address type
		using native_addr_t = sockaddr;

		// identify the network protocol
		enum class NetworkProtocol
		{
			Unknown,
			IPv4,
			IPv6
		};

		Address(const NetworkProtocol protocol = NetworkProtocol::IPv4);
		Address(const std::string& ip,
			const port_t port,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		// @param address in format like 127.0.0.1:80
		Address(const std::string& address,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		Address(const native_addr_t& address,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		~Address() = default;

		void setIP(const std::string& ip);
		inline const std::string& getIP() const;
		void setPort(const port_t port);
		inline port_t getPort() const;

		inline NetworkProtocol getNetworkProtocol() const { return m_protocol; }
		
		inline const native_addr_t& getNativeAddress() const { return m_address; }
		inline std::size_t getNativeSize() const { return sizeof(m_address); }

		bool isValid() const;
		inline operator bool() const { return isValid(); }

		bool operator== (const Address& other) const;

		inline bool operator!= (const Address& other) const
		{
			return !(*this == other);
		}

		static uint8_t getNativeProtocol(const NetworkProtocol protocol);

	private:
		
		// native address type
		native_addr_t m_address{};
		// network protocol
		NetworkProtocol m_protocol;
	};
}