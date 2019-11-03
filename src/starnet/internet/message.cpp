#include "message.h"

#include <sstream>

namespace starnet
{
	namespace internet
	{
		std::string Message::Header::toString() const
		{
			std::string result;
			for (auto it = begin(); it != end(); ++it)
			{
				result += (it->first + ": " + it->second + "\n");
			}
			return result;
		}

		Message::Header Message::Header::parse(const std::string& str)
		{
			Header header;			
			for (const std::string& line : getLines(str))
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
			return header;
		}

		std::vector<std::string> Message::Header::getLines(const std::string& str)
		{
			std::vector<std::string> lines;
			std::istringstream stream(str);
			std::string line;
			while (std::getline(stream, line))
			{
				lines.push_back(line);
			}
			return lines;
		}

		Message::Message()
			: header()
			, body()
		{
		}

		Message::Message(const Body& _body)
			: header()
			, body(_body)
		{
		}

		Message::Message(const Header& _header, const Body& _body)
			: header(_header)
			, body(_body)
		{
		}

		Message::Message(const Message& message)
			: header(message.header)
			, body(message.body)
		{
		}

		std::string Message::toString() const
		{
			return header.toString() + "\n\n" + body;
		}

		Message Message::parse(const std::string& source)
		{
			Message message;
			const auto& headerDelimiter = source.find("\n\n");
			if (headerDelimiter != std::string::npos)
			{
				message.header = Header::parse(source.substr(0, headerDelimiter));
				message.body = source.substr(headerDelimiter + 1, source.length());
			}
			else
			{
				message.header = Header::parse(source);
			}
			return message;
		}
		
		Message& Message::operator=(const Message& message)
		{
			header = message.header;
			body = message.body;

			return *this;
		}
		
		bool Message::operator==(const Message& message) const
		{
			return header == message.header
				&& body == message.body;
		}
		
		bool Message::operator!=(const Message& message) const
		{
			return header != message.header
				|| body != message.body;
		}
	}
}