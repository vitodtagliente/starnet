#pragma once

#include "message.h"

namespace starnet
{
	namespace http
	{
		class Request : public Message
		{
		public:

			Request() : Message() {}
			Request(const std::string& source) : Message(source) {}

		};
	}
}