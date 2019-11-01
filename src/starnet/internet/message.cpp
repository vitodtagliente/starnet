#include "message.h"

#include <sstream>

namespace starnet
{
	namespace internet
	{
		std::string Message::Header::toString() const
		{
			std::string result;
			for (auto it = begin(); it != end(); ++it)
			{
				result += it->first + "=" + it->second;
			}
			return result;
		}

		Message::Header Message::Header::parse(const std::string& str)
		{
			Header header;
			


			return header;
		}

		Message::Message()
			: header()
			, body()
		{
		}

		std::string Message::toString() const
		{
			return header.toString() + "\n" + body;
		}
	}
}