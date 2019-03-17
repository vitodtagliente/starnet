#pragma once

#include "platform.h"
#include "socket.h"

namespace starnet
{
	// define a shared SocketType that match the platform specific type definition
	using native_socket_t = 
#ifdef PLATFORM_WINDOWS
		SOCKET
#else 
		int
#endif
		;

	class SocketBSD final : public Socket
	{
	public:

		SocketBSD(Socket::Type type) : Socket(type), m_socket() {}
		SocketBSD(native_socket_t socket, Socket::Type type) : Socket(type), m_socket(socket) {}
		virtual ~SocketBSD() override { close(); }

		inline native_socket_t getNativeSocket() const { return m_socket; }

		virtual bool bind(const Address& address) override;
		virtual bool connect(const Address& address) override;
		virtual bool listen(unsigned int numOfMaxConnections) override;
		virtual class Socket* accept() const override;
		virtual class Socket* accept(Address& outAddress) const override;

		virtual bool send(const uint8_t* data, const std::size_t count, int32_t& byteSent) override;
		virtual bool sendTo(const Address& address, const uint8_t* data, const std::size_t count, int32_t& byteSent) override;


		virtual bool receive(uint8_t* data, std::size_t bufferSize, int32_t& bytesRead) override;
		virtual bool receiveFrom(Address& address, uint8_t* data, std::size_t bufferSize, int32_t& bytesRead) override;

		virtual ConnectionState getConnectionState() const override;
		virtual Address& getAddress() const override;

		virtual bool setNonBlockingMode(const bool isNonBlocking = true) override;
		virtual bool setBroadcastMode(const bool isBroadcast = true) override;

		virtual bool setSendBufferSize(const std::size_t size) override;
		virtual bool setReceiveBufferSize(const std::size_t size) override;

		virtual bool shutdown(ShutdownMode mode) override;
		virtual bool close() override;

	private:

		// native socket type
		native_socket_t m_socket;
	};
}