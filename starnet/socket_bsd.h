#pragma once

#include "platform.h"
#include "socket.h"

namespace starnet
{
	// define a shared SocketType that match the platform specific type definition
#ifdef WIN32
	typedef SOCKET NativeSocketType;
#else
	typedef int NativeSocketType;
#endif

	class SocketBSD final : public Socket
	{
	public:

		SocketBSD(Socket::Type type) : Socket(type), m_socket() {}
		virtual ~SocketBSD() { close(); }

		inline NativeSocketType getNativeSocket() const { return m_socket; }



	private:

		// native socket type
		NativeSocketType m_socket;
	};
}