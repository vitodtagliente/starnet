#include "header.h"

namespace starnet
{
	namespace http
	{
		Header::Connection Header::getConnection() const
		{
			const auto it = find("Connection");
			if (it != end())
			{
				
			}
			return Connection::Close;
		}

		void Header::setConnection(const Connection connection)
		{
		}
	}
}