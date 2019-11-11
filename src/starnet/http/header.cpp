#include "header.h"

namespace starnet
{
	namespace http
	{
		std::string Header::to_string(const Connection connection)
		{
			if (connection == Connection::KeepAlive)
				return "keep-alive";
			return "close";
		}

		void Header::value(const std::string& str, Connection& connection)
		{
			connection = (str == "keep-alive") ? Connection::KeepAlive : Connection::Close;
		}
	}
}