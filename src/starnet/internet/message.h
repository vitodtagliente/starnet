#pragma once

/*
 *
 * Implements RFC 5322, "Internet Message Format"
 * https://tools.ietf.org/html/rfc5322
 */

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace starnet
{
	namespace internet
	{
		template <typename Header, typename Body>
		struct message_t
		{
			Header header;
			Body body;

			bool operator== (const message_t& message) const;
			bool operator!= (const message_t& message) const;

			std::string toString() const;
			static message_t parse(const std::string& source);
		};
		
		template<typename Header, typename Body>
		bool message_t<Header, Body>::operator==(const message_t& message) const
		{
			return header == message.header
				&& body == message.body;
		}

		template<typename Header, typename Body>
		bool message_t<Header, Body>::operator!=(const message_t& message) const
		{
			return header != message.header
				|| body != message.body;
		}

		// generic message data representation

		using Message = message_t<std::unordered_map<std::string, std::string>, std::string>;
	}
}