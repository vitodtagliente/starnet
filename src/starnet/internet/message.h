#pragma once

/*
 *
 * Implements RFC 5322, "Internet Message Format"
 * https://tools.ietf.org/html/rfc5322
 */

#include <map>
#include <string>
#include <vector>

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

			private:

				static std::vector<std::string> getLines(const std::string& str);
			};

			using Body = std::string;

			Message();
			Message(const std::string& source);

			Header header;
			Body body;

			std::string toString() const;
		};
	}
}