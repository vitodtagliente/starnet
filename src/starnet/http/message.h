#pragma once

#include "../internet/message.h"

namespace starnet
{
	namespace http
	{
		class Message : public internet::Message
		{
		public:

			enum class Version
			{
				v1,
				v2
			};

			Message() : internet::Message() {}
			Message(const std::string& source);
			Message(const Message& message) : internet::Message(message) {}

			virtual std::string toString() const override;

		};
	}
}