#pragma once

#include <string>
#include <unordered_map>
#include "header.h"

namespace starnet
{
	namespace http
	{
		class Headers : public std::unordered_map<std::string, std::string>
		{
			Header::Connection getConnection() const;
			void setConnection(const Header::Connection connection);
		};
	}
}