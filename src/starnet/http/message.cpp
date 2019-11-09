#include "message.h"
/*
namespace starnet
{
	namespace http
	{
		Message::Message()
			: internet::Message()
			, m_version(Version::v1)
		{

		}

		Message::Message(const std::string& source)
			: internet::Message(source)
			, m_version(Version::v1)
		{

		}

		Message::Message(const Message& message)
			: internet::Message(message)
			, m_version(message.m_version)
		{

		}

		std::string Message::toString() const
		{
			return internet::Message::toString();
		}
		
		void Message::setConnection(const Connection connection)
		{
			if (connection == Connection::KeepAlive)
			{
				const auto& it = m_header.find("connection");
				if (it != m_header.end())
				{
					it->second = "keep-alive";
				}
				else
				{
					m_header.insert({ "connection", "keep-alive" });
				}
			}
			else
			{
				m_header.erase("connection");
			}
		}
		
		Message::Connection Message::getConnection() const
		{
			const auto& it = m_header.find("connection");
			if (it != m_header.end())
			{
				return it->second == "keep-alive" ? Connection::KeepAlive : Connection::Close;
			}
			return Connection::Close;
		}
		
		std::size_t Message::getContentLength() const
		{
			return m_body.size();
		}
	}
}
*/