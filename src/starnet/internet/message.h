#pragma once

/*
 *
 * Implements RFC 5322, "Internet Message Format"
 * https://tools.ietf.org/html/rfc5322
 */

#include <map>
#include <string>

namespace starnet
{
	namespace internet
	{
		class Message
		{
		public:

			class Header : public std::map<std::string, std::string>
			{
			public:

				std::string toString() const;

				static Header parse(const std::string& str);
			};

			class Body : public std::string
			{

			};

			Message();

			Header header;
			Body body;

			std::string toString() const;
		};
	}
}