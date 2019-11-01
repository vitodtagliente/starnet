#pragma once

#include "../internet/message.h"

namespace starnet
{
	namespace http
	{
		class Message : public internet::Message
		{
		public:

			Message()
				: internet::Message()
			{

			}

			Message(const std::string& source)
				: internet::Message(source)
			{

			}
		};
	}
}