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

			const std::map<std::string, std::string>& getHeader() const { return m_header; }
			const std::string& getBody() const { return m_body; }
			bool isValid() const { return m_isValid; }

			virtual std::string toString() const;

			Message& operator= (const Message& message);
			bool operator== (const Message& message) const;
			bool operator!= (const Message& message) const;

			static constexpr const char* blankline = "\r\n";
			static constexpr const char* endline = "\n";

		protected:
			
			std::map<std::string, std::string> m_header;
			std::string m_body;
			bool m_isValid;
		
		};
	}
}