#pragma once

#include <string>
#include <unordered_map>
#include "../internet/message.h"
#include "method.h"
#include "status_code.h"
#include "header.h"

namespace starnet
{
	namespace http
	{		
		enum class Version : uint8_t
		{
			v1 = 1,
			v2 = 2
		};

		template <typename Header, typename Body>
		struct message_t : public internet::message_t<Header, Body>
		{
			Version version{ Version::v1 };

			static message_t parse(const std::string& source);
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

		// base data representation

		using Message = message_t<Header, std::string>;
		using Request = request_t<Header, std::string>;
		using Response = response_t<Header, std::string>;
	}
}