#pragma once

#include <cstdint>
#include "address.h"
#include "platform.h"

namespace starnet
{
	class Socket
	{
	public:

		// native socket type
		using native_socket_t =
#ifdef PLATFORM_WINDOWS
		SOCKET
#else 
		int
#endif
		;

		// transport protocol
		enum class TransportProtocol
		{
			Unknown,
			TCP,
			UDP
		};

		// indicates the type of socket being used
		enum class Type
		{
			Unknown,
			// UDP type socket
			Datagram,
			// TCP type socket 
			Stream
		};

		// indicates the connection state of the socket
		enum class ConnectionState
		{
			NotConnected,
			Connected,
			Error
		};

		enum class ShutdownMode
		{			
			// disable reading on the socket
			Read,
			// disable writing on the socket
			Write,
			// disable reading and writing on the socket
			Both
		};

		Socket(const Address& address, const Type type, const TransportProtocol protocol);
		Socket(const native_socket_t socket, const Type type);
		~Socket() = default;

		inline Type getType() const { return m_type; }
		uint8_t getNativeType() const;
		inline TransportProtocol getProtocol() const { return m_protocol; }
		uint8_t getNativeProtocol() const;

		// Notify the operating system that a socket will use a specific address
		// and transport layer port.
		bool bind(const Address& address);
		// Calling connect initialized the TCP handshake by sending 
		// the initial SYN packet to a target host.
		// if the host has a listen socket bound to the appropriate port, 
		// it can proceed with the handshake by calling accept.
		bool connect(const Address& address);
		// numOfMaxConnections is the maximum number of incoming 
		// connections that should be allowed to queue up.
		// Once the maximum number of handshakes are pending, 
		// any futher incoming connection is dropped.
		bool listen(unsigned int numOfMaxConnections);
		// accept an incoming connection and continue to the handshake.
		class Socket* accept() const;
		class Socket* accept(Address& outAddress) const;

		// A connected socket stores the remote host's address information.
		// Because of this, a process does not need to pass an address. 
		// @param data The buffer to send
		// @param count The size of the data to send
		// @param byteSent Will indicate how much was sent
		bool send(const uint8_t* data, const std::size_t count, int32_t& byteSent);
		// Send data to a specific address
		bool sendTo(const Address& address, const uint8_t* data, const std::size_t count, int32_t& byteSent);

		bool receive(uint8_t* data, std::size_t bufferSize, int32_t& bytesRead);
		bool receiveFrom(Address& address, uint8_t* data, std::size_t bufferSize, int32_t& bytesRead);

		ConnectionState getConnectionState() const;

		const Address& getAddress() const { return m_address; }

		bool setNonBlockingMode(const bool isNonBlocking = true);
		bool setBroadcastMode(const bool isBroadcast = true);

		bool setSendBufferSize(const std::size_t size);
		bool setReceiveBufferSize(const std::size_t size);

		// shuts down the socket
		bool shutdown(ShutdownMode mode);
		// close the socket
		bool close();

		bool isValid() const;
		inline operator bool() const { return isValid(); }

	private:

		// native socket 
		native_socket_t m_socket;
		// socket address
		Address m_address;
		// indicates the socket type
		const Type m_type;
		// indicates the transport protocol
		TransportProtocol m_protocol;
	};
}