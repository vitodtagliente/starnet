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
		
			Message();
			Message(const std::string& source);
			Message(const Message& message);
			
			virtual std::string toString() const;

			Message& operator= (const Message& message);
			bool operator== (const Message& message) const;
			bool operator!= (const Message& message) const;

			std::map<std::string, std::string> header;
			std::string body;
			
		private:

			static constexpr const char* white_line = "\n\n";
			
			static std::vector<std::string> getLines(const std::string& str);
		};
	}
}