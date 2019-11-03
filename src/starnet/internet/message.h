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
			Message(const Body& _body);
			Message(const Header& _header, const Body& _body);
			Message(const Message& message);

			std::string toString() const;

			static Message parse(const std::string& source);

			Message& operator= (const Message& message);
			bool operator== (const Message& message) const;
			bool operator!= (const Message& message) const;

			Header header;
			Body body;
		};
	}
}