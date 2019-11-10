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
			enum class Connection
			{
				Close,
				KeepAlive
			};

			enum class CacheControl
			{

			};

			enum class ContentEncoding
			{
				gzip
			};

			enum class ContentLanguage
			{

			};
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

		using Message = message_t<std::unordered_map<std::string, std::string>, std::string>;
		using Request = request_t<std::unordered_map<std::string, std::string>, std::string>;
		using Response = response_t<std::unordered_map<std::string, std::string>, std::string>;
	}
}