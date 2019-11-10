#include "headers.h"

namespace starnet
{
	namespace http
	{
		Headers::Connection Headers::getConnection() const
		{
			const auto it = find("Connection");
			if (it != end())
			{
				
			}
			return Connection::Close;
		}

		void Headers::setConnection(const Connection connection)
		{
		}
	}
}