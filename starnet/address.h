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

		enum class NetworkProtocol : uint8_t
		{
			IPv4,
			IPv6
		};

		Address(const std::string& ip, const PortType port){}
		virtual ~Address() {}

		virtual void setIp(const std::string& ip) = 0;
		virtual void setPort(const PortType port) = 0;

		virtual void setAnyAddress() = 0;
		virtual void setBroadcastAddress() = 0;
		virtual void setLoopbackAddress() = 0;

		virtual bool operator== (const Address& other) const
		{
			return false;
		}

		bool operator!= (const Address& other) const
		{
			return !(*this == other);
		}

	protected:



	};
}