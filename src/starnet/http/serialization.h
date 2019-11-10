#pragma once

#include "../internet/serialization.h"
#include "message.h"

namespace starnet
{
	namespace internet
	{
		template <>
		std::string serialize(const http::Header& header)
		{
			return serialize(static_cast<std::unordered_map<std::string, std::string>>(header));
		}

		template <>
		bool deserialize(http::Header& header, const std::string& source)
		{
			return deserialize(static_cast<std::unordered_map<std::string, std::string>>(header), source);
		}
	}
}