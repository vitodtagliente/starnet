#pragma once

#include <cstdint>
#include "address.h"
#include "platform.h"

namespace starnet
{
	class Socket
	{
	public:

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

		Socket() : m_type(Type::Unknown) {}
		Socket(Type type) : m_type(type) {}
		virtual ~Socket() {}

		inline Type getType() const { return m_type; }

		// Notify the operating system that a socket will use a specific address
		// and transport layer port.
		virtual bool bind(const Address& address) = 0;
		// Calling connect initialized the TCP handshake by sending 
		// the initial SYN packet to a target host.
		// if the host has a listen socket bound to the appropriate port, 
		// it can proceed with the handshake by calling accept.
		virtual bool connect(const Address& address) = 0;
		// numOfMaxConnections is the maximum number of incoming 
		// connections that should be allowed to queue up.
		// Once the maximum number of handshakes are pending, 
		// any futher incoming connection is dropped.
		virtual bool listen(unsigned int numOfMaxConnections) = 0;
		// accept an incoming connection and continue to the handshake.
		virtual class Socket* accept() const = 0;
		virtual class Socket* accept(Address& outAddress) const = 0;

		// A connected socket stores the remote host's address information.
		// Because of this, a process does not need to pass an address. 
		// @param data The buffer to send
		// @param count The size of the data to send
		// @param byteSent Will indicate how much was sent
		virtual bool send(const uint8_t* data, const std::size_t count, int32_t& byteSent) = 0;
		// Send data to a specific address
		virtual bool sendTo(const Address& address, const uint8_t* data, const std::size_t count, int32_t& byteSent) = 0;

		virtual bool receive(uint8_t* data, std::size_t bufferSize, int32_t& bytesRead) = 0;
		virtual bool receiveFrom(Address& address, uint8_t* data, std::size_t bufferSize, int32_t& bytesRead) = 0;

		virtual ConnectionState getConnectionState() const = 0;
		virtual Address& getAddress() const = 0;

		virtual bool setNonBlockingMode(const bool isNonBlocking = true) = 0;
		virtual bool setBroadcastMode(const bool isBroadcast = true) = 0;

		virtual bool setSendBufferSize(const std::size_t size) = 0;
		virtual bool setReceiveBufferSize(const std::size_t size) = 0;

		// shuts down the socket
		virtual bool shutdown(ShutdownMode mode) = 0;
		// close the socket
		virtual bool close() = 0;

		virtual bool isValid() const = 0;
		inline operator bool() const { return isValid(); }

	protected:

		// indicates the socket type
		const Type m_type;
		// indicates the transport protocol
		TransportProtocol m_protocol;
	};
}