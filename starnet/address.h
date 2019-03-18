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

		Address(const std::string& ip,
			const port_t port,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		// @param address in format like 127.0.0.1:80
		Address(const std::string& address,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		Address(const native_addr_t& address,
			const NetworkProtocol protocol = NetworkProtocol::IPv4);
		~Address() = default;

		inline const std::string& getIP() const { return m_ip; }
		inline port_t getPort() const { return m_port; }
		inline NetworkProtocol getNetworkProtocol() const { return m_protocol; }
		
		inline const native_addr_t& getNativeAddress() const { return m_address; }
		inline std::size_t getNativeSize() const { return sizeof(m_address); }
		uint8_t getNativeProtocol() const;

		bool isValid() const;
		inline operator bool() const { return isValid(); }

		inline bool operator== (const Address& other) const
		{
			return m_ip == other.m_ip &&
				m_port == other.m_port &&
				m_protocol == other.m_protocol;
		}

		inline bool operator!= (const Address& other) const
		{
			return !(*this == other);
		}

	private:
		
		// initialize the native data 
		void nativeInit();

		// ip address
		std::string m_ip;
		// port 
		port_t m_port;
		// network protocol
		NetworkProtocol m_protocol;

		// native address type
		native_addr_t m_address;
	};
}