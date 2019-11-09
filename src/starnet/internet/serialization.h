#pragma once

#include <string>
#include <unordered_map>
#include "message.h"
#include "../string.h"

namespace starnet
{
	namespace internet
	{
		template <typename T>
		std::string serialize(const T&) {}

		template <>
		std::string serialize(const std::unordered_map<std::string, std::string>& header)
		{
			std::string result;
			for (auto it = header.begin(); it != header.end(); ++it)
			{
				result += (it->first + ": " + it->second + "\n");
			}
			return result;
		}

		template <>
		std::string serialize(const std::string& body)
		{
			return body;
		}

		template <typename Header, typename Body>
		std::string serialize (const message_t<Header, Body>& message)
		{
			return serialize<Header>(message.header)
				+ "\r\n"
				+ serialize<Body>(message.body); 
		}

		template <typename Header, typename Body>
		bool deserialize (message_t<Header, Body>& message, const std::string& source)
		{
			const auto it = source.find("\r\n");
			if (it != std::string::npos)
			{
				deserialize(message.header, source.substr(0, it));
				deserialize(message.body, source.substr(it + 1, source.length()));
			}
			else
			{
				deserialize(message.header, source);
				message.body = Body{};
			}
			return true;
		}

		template <typename T>
		bool deserialize(T&, const std::string&) { return false; }

		template <>
		bool deserialize(std::unordered_map<std::string, std::string>& header, const std::string& source)
		{
			header.clear();
			for (const auto& line : String(source).getLines())
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

		template <>
		bool deserialize(std::string& body, const std::string& source)
		{
			body = source;
			return true;
		}
	}
}