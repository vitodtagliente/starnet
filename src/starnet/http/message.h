#pragma once

#include <string>
#include <unordered_map>
#include "../internet/message.h"
#include "status_code.h"
#include "headers.h"
#include "url.h"

namespace starnet
{
	namespace http
	{	
		template <typename Headers, typename Body>
		struct message_t : public internet::message_t<Headers, Body>
		{
			static message_t parse(const std::string& source);
		};

		template <typename Headers, typename Body>
		struct request_t : public message_t<Headers, Body>
		{
			Header::Method method{ Header::Method::Get };
			Url url{ "/" };
			Header::Version version{ Header::Version::v1 };

			std::string toString() const;
			
			static request_t parse(const std::string& source);
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
			return Header::to_string(method) + " " 
				+ url.toString() + " "
				+ Header::to_string(version) + "\n"
				+ message_t<Headers, Body>::toString();
		}

		template<typename Headers, typename Body>
		request_t<Headers, Body> request_t<Headers, Body>::parse(const std::string& source)
		{
			return request_t();
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