#include "headers.h"

namespace starnet
{
	namespace http
	{
		Header::Connection Headers::getConnection() const
		{
			const auto it = find(Header::name<Header::Connection>());
			if (it != end())
			{
				
			}
			return Header::Connection::Close;
		}

		void Headers::setConnection(const Header::Connection connection)
		{
		}
	}
}