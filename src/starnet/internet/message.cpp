#include "message.h"

#include <sstream>
#include "../string.h"

namespace starnet
{
	namespace internet
	{
		struct MessageParser
		{
			MessageParser() = delete;

			static bool parse(const std::string& source,
				std::map<std::string, std::string>& header,
				std::string& body)
			{
				header.clear();
				body.clear();

				// parse the message
				const auto& headerDelimiter = source.find(Message::blankline);
				if (headerDelimiter != std::string::npos)
				{
					body = source.substr(headerDelimiter + 1, source.length());
				}

				for (const auto& line : String(
					headerDelimiter != std::string::npos ? source.substr(0, headerDelimiter) : source
				).getLines())
				{
					const auto& position = line.find(':');
					if (position != std::string::npos)
					{
						header.insert({
							line.substr(0, position),
							line.substr(position + 1, line.length())
							});
					}
				}

				return true;
			}
		};

		Message::Message()
			: m_header()
			, m_body()
			, m_isValid(false)
		{
		}

		Message::Message(const std::string& source)
			: m_header()
			, m_body()
			, m_isValid(false)
		{
			m_isValid = MessageParser::parse(source, m_header, m_body);
		}

		Message::Message(const Message& message)
			: m_header(message.m_header)
			, m_body(message.m_body)
			, m_isValid(false)
		{
			m_isValid = message.m_isValid;
		}

		std::string Message::toString() const
		{
			std::string result;
			// append header
			for (auto it = m_header.begin(); it != m_header.end(); ++it)
			{
				result += (it->first + ": " + it->second + endline);
			}
			// append body
			return result + blankline + m_body;
		}
		
		Message& Message::operator=(const Message& message)
		{
			m_header = message.m_header;
			m_body = message.m_body;
			m_isValid = message.m_isValid;

			return *this;
		}
		
		bool Message::operator==(const Message& message) const
		{
			return m_header == message.m_header
				&& m_body == message.m_body;
		}
		
		bool Message::operator!=(const Message& message) const
		{
			return m_header != message.m_header
				|| m_body != message.m_body;
		}
	}
}