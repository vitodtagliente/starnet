#pragma once

#include <cstdint>
#include <string>
#include "common.h"

namespace starnet
{
	class Address
	{	
	public:
		
		typedef uint16_t PortType;

		enum class NetworkProtocol
		{
			Unknown,
			IPv4,
			IPv6
		};

		Address(const std::string& ip, 
			const PortType port, 
			const NetworkProtocol protocol = NetworkProtocol::IPv4)
			: m_ip(ip), m_port(port), m_protocol(protocol)
		{}
		virtual ~Address() {}

		inline const std::string& getIP() const { return m_ip; }
		inline PortType getPort() const { return m_port; }
		inline NetworkProtocol getNetworkProtocol() const { return m_protocol; }

		virtual std::size_t getNativeSize() const = 0;
		
		virtual bool isValid() const = 0;

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

		static const std::string loopbackAddress;
		static const PortType unusedPort;

	protected:

		// ip address
		std::string m_ip;
		// port 
		PortType m_port;
		// network protocol
		NetworkProtocol m_protocol;

	};

	const std::string Address::loopbackAddress{ "127.0.0.1" };
	const Address::PortType Address::unusedPort{ 0 };
}