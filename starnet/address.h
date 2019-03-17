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

		enum class NetworkProtocol
		{
			Unknown,
			IPv4,
			IPv6
		};

		Address(const std::string& ip, 
			const port_t port, 
			const NetworkProtocol protocol = NetworkProtocol::IPv4)
			: m_ip(ip), m_port(port), m_protocol(protocol)
		{}
		virtual ~Address() {}

		inline const std::string& getIP() const { return m_ip; }
		inline port_t getPort() const { return m_port; }
		inline NetworkProtocol getNetworkProtocol() const { return m_protocol; }
		
		virtual bool isValid() const { return m_protocol != NetworkProtocol::Unknown; }
		inline operator bool() const { return isValid(); }

		virtual bool operator== (const Address& other) const
		{
			return m_ip == other.m_ip &&
				m_port == other.m_port &&
				m_protocol == other.m_protocol;
		}

		bool operator!= (const Address& other) const
		{
			return !(*this == other);
		}

	protected:

		// ip address
		std::string m_ip;
		// port 
		port_t m_port;
		// network protocol
		NetworkProtocol m_protocol;

	};
}