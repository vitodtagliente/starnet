#pragma once

#include "common.h"
#include "error.h"
#include "net_address.h"

namespace starnet
{
	// define a shared SocketType that match the platform specific type definition
#ifdef WIN32
	typedef SOCKET NativeSocketType;
#else
	typedef int NativeSocketType;
#endif

	// socket wrapper 
	class Socket
	{
	public:
		
		// transport layer protocol
		enum TransportProtocol
		{
			TCP = IPPROTO_TCP,
			UDP = IPPROTO_UDP
		};

		enum Type
		{
			// Raw = SOCK_RAW,
			Stream = SOCK_STREAM,
			Datagram = SOCK_DGRAM
		};

		enum ShutdownMode
		{
			Send = SD_SEND,
			Receive = SD_RECEIVE,
			Both = SD_BOTH
		};

		Socket(const NetAddress& address, const TransportProtocol protocol = TransportProtocol::UDP)
			: m_address{ address }, m_protocol{ protocol }
		{
			m_socket = ::socket(
				// address family / network layer protocol
				m_address.protocol,
				// type of socket
				(m_protocol == TransportProtocol::UDP) ? Type::Datagram : Type::Stream,
				// if 0, OS pick the default implemented transport protocol for the given socket type
				m_protocol
			);
		}

		Socket(const Socket&) = delete;
		Socket& operator= (const Socket&) = delete;

		virtual ~Socket() = default;

		inline NativeSocketType getNativeSocket() const { return m_socket; }
		inline TransportProtocol getTransportProtocol() const { return m_protocol; }
		inline const NetAddress& getAddress() const { return m_address; }

		inline bool isValid() const 
		{ 
#if WIN32
			return m_socket != INVALID_SOCKET;
#else
			return m_socket > 0;
#endif
		}

		bool operator== (const Socket& other) const { return m_socket == other.m_socket; }
		bool operator!= (const Socket& other) const { return !(*this == other); }
		
		inline bool bind()
		{
			const NetAddress::NativeAddressType& sock_address = m_address.getNativeAddress();
			return ::bind(m_socket, &sock_address, sizeof(sock_address)) >= 0;
		}

		inline bool close() 
		{
			return ::closesocket(m_socket);
		}

		inline bool shutdown(ShutdownMode mode = ShutdownMode::Send)
		{
			return ::shutdown(m_socket, mode) == 0;
		}

	private:

		// native socket data
		NativeSocketType m_socket;
		// nework address 
		NetAddress m_address;
		// transport layer protocol
		TransportProtocol m_protocol;
	};

	class UDPSocket : public Socket
	{
	public:

		UDPSocket(const NetAddress& address)
			: Socket(address, TransportProtocol::UDP)
		{

		}

		inline bool send(const std::string& data, const NetAddress& other) const
		{
			const NetAddress::NativeAddressType& addr_out = other.getNativeAddress();
			return ::sendto(getNativeSocket(), data.c_str(), data.length(), 0, &addr_out, sizeof(addr_out));
		}

		inline bool receive(std::string& out, const NetAddress& other) const 
		{
			NetAddress::NativeAddressType addr_out = other.getNativeAddress();
			int size = sizeof(addr_out);
			char buffer[100];
			int bytecount = ::recvfrom(
				getNativeSocket(),
				buffer,
				sizeof(buffer),
				0,
				&(addr_out),
				&size
			);
			out = std::string{ buffer };
			return bytecount >= 0;
		}

	};

	class TCPSocket : public Socket
	{
		TCPSocket(const NetAddress& address)
			: Socket(address, TransportProtocol::TCP)
		{

		}


	};
}