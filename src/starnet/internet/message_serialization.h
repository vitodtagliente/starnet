#pragma once

#include <string>
#include "message.h"

namespace starnet
{
	namespace internet
	{
		template <typename T>
		std::string serialize(const T&) {}

		template <>
		std::string serialize(const header_t& header)
		{
			std::string result;
			for (auto it = header.begin(); it != header.end(); ++it)
			{
				result += (it->first + ": " + it->second + "\n");
			}
			return result;
		}

		template <>
		std::string serialize(const body_t& body)
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
		message_t<Header, Body> deserialize (const std::string& source)
		{

		}

		
	}
}


/*
// message to string conversion
template <typename Header, typename Body>
void serialize_message (const message_t<Header, Body>& message, std::string& str)
{
	using type = message_t<std::unordered_map<std::string, std::string>, std::string>;

	str.clear();
	// append header
	for (auto it = message.getHeader().begin(); it != message.getHeader().end(); ++it)
	{
		str += (it->first + ": " + it->second + type::end_line);
	}
	// append body
	str += type::blank_line + message.getBody();
}

// string to message conversion
template <typename Header, typename Body>
void deserialize_message (message_t<Header, Body>& message, const std::string& source)
{

}

template <>
void serialize_message(
	const message_t<std::unordered_map<std::string, std::string>, std::string>& message,
	std::string& str)
{
	using type = message_t<std::unordered_map<std::string, std::string>, std::string>;

	str.clear();
	// append header
	for (auto it = message.getHeader().begin(); it != message.getHeader().end(); ++it)
	{
		str += (it->first + ": " + it->second + type::end_line);
	}
	// append body
	str += type::blank_line + message.getBody();
}

template <>
void deserialize_message(
	message_t<std::unordered_map<std::string, std::string>, std::string>& message,
	const std::string& source)
{
	using type = message_t<std::unordered_map<std::string, std::string>, std::string>;

	// parse the message
	const auto& headerDelimiter = source.find(type::blank_line);
	if (headerDelimiter != std::string::npos)
	{
		message.m_body = source.substr(headerDelimiter + 1, source.length());
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
}
*/