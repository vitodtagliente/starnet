#include "message.h"

#include <sstream>

namespace starnet
{
	namespace internet
	{
		Message::Message()
			: header()
			, body()
		{
		}

		Message::Message(const std::string& source)
			: header()
			, body()
		{
			// parse the message
			const auto& headerDelimiter = source.find(white_line);
			if (headerDelimiter != std::string::npos)
			{
				body = source.substr(headerDelimiter + 1, source.length());
			}

			for (const std::string& line : getLines(
				headerDelimiter != std::string::npos ? source.substr(0, headerDelimiter) : source
			))
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
		}

		Message::Message(const Message& message)
			: header(message.header)
			, body(message.body)
		{
		}

		std::string Message::toString() const
		{
			std::string result;
			// append header
			for (auto it = header.begin(); it != header.end(); ++it)
			{
				result += (it->first + ": " + it->second + "\n");
			}
			// append body
			return result + "\n\n" + body;
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

		std::vector<std::string> Message::getLines(const std::string& str)
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
	}
}