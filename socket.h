#pragma once

#include "common.h"
#include "error.h"
#include "address.h"

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

		Socket(const Address& address, const TransportProtocol protocol = TransportProtocol::UDP)
			: m_address{ address }, m_protocol{ protocol }
		{
			m_socket = ::socket(
				// address family / network layer protocol
				m_address.getProtocol(),
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
		inline const Address& getAddress() const { return m_address; }

		inline bool isValid() const 
		{ 
#if PLATFORM_WINDOWS
			return m_socket != INVALID_SOCKET;
#else
			return m_socket > 0;
#endif
		}

		bool operator== (const Socket& other) const { return m_socket == other.m_socket; }
		bool operator!= (const Socket& other) const { return !(*this == other); }
		
		inline bool bind()
		{
			return ::bind(m_socket, &m_address.getAddress(), m_address.getSize()) >= 0;
		}

		inline bool close() 
		{
#if PLATFORM_WINDOWS
			return ::closesocket(m_socket);
#else
			return ::close(m_socket);
#endif			
		}

		inline bool shutdown(ShutdownMode mode = ShutdownMode::Send)
		{
			return ::shutdown(m_socket, mode) == 0;
		}

	protected:

		// native socket data
		NativeSocketType m_socket;
		// nework address 
		Address m_address;
		// transport layer protocol
		TransportProtocol m_protocol;
	};

	class UDPSocket : public Socket
	{
	public:

		UDPSocket(const Address& address)
			: Socket(address, TransportProtocol::UDP)
		{

		}

		inline bool send(const std::string& data, const Address& toAddress) const
		{
			return ::sendto(
				m_socket, 
				data.c_str(),
				data.length(), 
				0, 
				&toAddress.getAddress(), 
				toAddress.getSize()
			);
		}

		inline bool receive(std::string& message, Address& fromAddress) const 
		{
			Address::NativeAddressType address{};
			int size = sizeof(address);

			// #todo: buffer size 
			char buffer[100];
			if (const int bytecount = ::recvfrom(
				m_socket,
				buffer,
				sizeof(buffer),
				0,
				&address,
				&size
			))
			{
				message = { buffer, (unsigned int)bytecount };
				fromAddress = { address, m_address.getProtocol() };
				return true;
			}
			// error
			return false;
		}

	};

	class TCPSocket : public Socket
	{
		TCPSocket(const Address& address)
			: Socket(address, TransportProtocol::TCP)
		{

		}


	};
}