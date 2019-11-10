#pragma once

#include <string>
#include <unordered_map>

namespace starnet
{
	namespace http
	{
		class Header : public std::unordered_map<std::string, std::string>
		{
			enum class Connection
			{
				Close,
				KeepAlive
			};

			enum class CacheControl
			{

			};

			enum class ContentEncoding
			{
				gzip
			};

			enum class ContentLanguage
			{

			};

			Connection getConnection() const;
			void setConnection(const Connection connection);

			
		};
	}
}