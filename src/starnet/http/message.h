#pragma once

#include <string>
#include <unordered_map>
#include "../internet/message.h"
#include "method.h"
#include "status_code.h"
#include "headers.h"
#include "url.h"

namespace starnet
{
	namespace http
	{		
		enum class Version : uint8_t
		{
			v1 = 1,
			v2 = 2
		};

		template <typename Headers, typename Body>
		struct message_t : public internet::message_t<Headers, Body>
		{
			Version version{ Version::v1 };

			static message_t parse(const std::string& source);
		};

		template <typename Headers, typename Body>
		struct request_t : public message_t<Headers, Body>
		{
			Method method{ Method::Get };

			std::string toString() const;
		};

		template <typename Headers, typename Body>
		struct response_t : public message_t<Headers, Body>
		{
			StatusCode code{ StatusCode::Unknown };

			std::string toString() const;
		};

		template<typename Headers, typename Body>
		inline std::string request_t<Headers, Body>::toString() const
		{
			return "tttt"
				+ message_t<Headers, Body>::toString();
		}

		template<typename Headers, typename Body>
		inline std::string response_t<Headers, Body>::toString() const
		{
			return "tyyyy"
				+ message_t<Headers, Body>::toString();
		}

		// base data representation

		using Message = message_t<Headers, std::string>;
		using Request = request_t<Headers, std::string>;
		using Response = response_t<Headers, std::string>;
		
	}
}