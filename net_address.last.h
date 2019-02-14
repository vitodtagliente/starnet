#pragma once

#include "common.h"
#include <string>

/*
	Define a friendly class to manage socket addresses
*/

namespace starnet
{
	class NetAddress
	{
	public:

		enum Family
		{
			IPv4 = AF_INET,
			IPv6 = AF_INET6
		};

		enum class State
		{
			Error,
			Malformed,
			Valid,
		};

		static const std::string localAddress;
		// bind will return an error if you try to bind to an address and 
		// port already in use. In that case, you can specify 0 for the port.
		// This tells the library to find an unused port and bind that.
		static const uint16_t UnusedPort;

		NetAddress(uint16_t port, Family address_family = Family::IPv4)
			: NetAddress(localAddress, port, address_family)
		{

		}

		NetAddress(const std::string& ip_address, uint16_t port, Family address_family = Family::IPv4)
		{
			sockaddr_in* sock_in = getAsSocketAddressIn();
			sock_in->sin_family = address_family;
			sock_in->sin_port = htons(port);

			int success = 0;
#if WIN32
			success = InetPton(address_family, std::wstring(ip_address.begin(), ip_address.end()).c_str(), sock_in);
#else
			success = inet_pton(address_family, ip_address.c_str(), sock_in);
#endif
			switch (success)
			{
			case -1:
				state = State::Error; 
				break;
			case 0:
				state = State::Malformed;
				break;
			default:
				state = State::Valid;
				break;
			}
		}

		NetAddress(const NetAddress& other)
		{
			m_socketAddress = other.m_socketAddress;
		}

		inline bool isValid() const { return state == State::Valid; }
		inline State getState() const { return state; }

		inline const sockaddr& getSocketAddress() const { return m_socketAddress; }
		inline const size_t getSize() const { return sizeof(m_socketAddress); }

		inline sockaddr_in* getAsSocketAddressIn() {
			return reinterpret_cast<sockaddr_in*>(&m_socketAddress);
		}

	private:

		// socket address native data structure
		sockaddr m_socketAddress;
		// address conversion state
		State state;

	};

	const std::string NetAddress::localAddress{ "127.0.0.1" };
	const uint16_t NetAddress::UnusedPort{ 0 };
}
