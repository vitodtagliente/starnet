#pragma once

#include <string>
#include <unordered_map>
#include "../internet/message.h"
#include "method.h"
#include "status_code.h"

namespace starnet
{
	namespace http
	{		
		template <typename Header, typename Body>
		struct message_t : public internet::message_t<Header, Body>
		{
			enum class Version
			{
				v11,
				v2
			};

			Version version{ v11 };
		};

		template <typename Header, typename Body>
		struct request_t : public message_t<Header, Body>
		{
			Method method{ Method::Get };
		};

		template <typename Header, typename Body>
		struct response_t : public message_t<Header, Body>
		{
			StatusCode code{ StatusCode::Unknown };
		};
	}
}