#include "message.h"

namespace starnet
{
	namespace http
	{
		Message::Message(const std::string& source)
		{

		}

		std::string Message::toString() const
		{
			return std::string{};
		}
		
		void Message::setConnection(const Connection connection)
		{
			if (connection == Connection::KeepAlive)
			{
				const auto& it = header.find("connection");
				if (it != header.end())
				{
					it->second = "keep-alive";
				}
				else
				{
					header.insert({ "connection", "keep-alive" });
				}
			}
			else
			{
				header.erase("connection");
			}
		}
		
		Message::Connection Message::getConnection() const
		{
			const auto& it = header.find("connection");
			if (it != header.end())
			{
				return it->second == "keep-alive" ? Connection::KeepAlive : Connection::Close;
			}
			return Connection::Close;
		}
	}
}