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

		enum AddressFamily
		{
			IPv4 = AF_INET,
			IPv6 = AF_INET6
		};

		static const std::string localhostAddress;
		static const uint16_t UnusedPort;

		NetAddress(uint16_t port, AddressFamily address_family = AddressFamily::IPv4)
			: NetAddress(localhostAddress, port, address_family)
		{

		}

		NetAddress(const std::string& ip_address, uint16_t port, AddressFamily address_family = AddressFamily::IPv4)
		{
			m_address = ip_address;
			m_port = port;
			m_family = address_family;

			sockaddr_in* sock_in = getAsSocketAddressIn();
			sock_in->sin_family = address_family;
			sock_in->sin_port = htons(port);
			// #todo: on Unix use inet_pton
			InetPton(address_family, (PCWSTR)ip_address.c_str(), sock_in);
		}

		NetAddress(const NetAddress& other)
		{
			m_socketAddress = other.getSocketAddress();
		}

		inline const sockaddr& getSocketAddress() const { return m_socketAddress; }
		inline const size_t getSize() const { return sizeof(m_socketAddress); }

		inline const std::string& getAddress() const { return m_address; }
		inline const int getPort() const { return m_port; }
		inline const AddressFamily getFamily() const { return m_family; }

		inline sockaddr_in* getAsSocketAddressIn() {
			return reinterpret_cast<sockaddr_in*>(&m_socketAddress);
		}

	private:

		// address ip
		std::string m_address;
		// address port
		int m_port;
		// address family
		AddressFamily m_family;
		// socket address native data structure
		sockaddr m_socketAddress;

	};

	const std::string NetAddress::localhostAddress{ "127.0.0.1" };
	const uint16_t NetAddress::UnusedPort{ 0 };
}
