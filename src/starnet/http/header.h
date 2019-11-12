#pragma once

#include <cstddef>
#include <string>

namespace starnet
{
	namespace http
	{
		struct Header
		{
			Header() = delete;

			enum class Version : uint8_t
			{
				v1 = 1,
				v2 = 2
			};

			enum class Method
			{
				Get,
				Head,
				Post,
				Put,
				Delete,
				Connect,
				Options,
				Trace
			};

			enum class Connection
			{
				Close,
				KeepAlive
			};

			enum class CacheControl
			{
				NoCache
			};

			enum class ContentEncoding
			{
				gzip
			};

			enum class ContentLanguage
			{

			};

			template <typename T> static std::string name() { return {}; }
			template<> static std::string name<Connection>() { return "Connection"; }
			template<> static std::string name<CacheControl>() { return "Cache-Control"; }
			template<> static std::string name<ContentEncoding>() { return "Encoding"; }
			template<> static std::string name<ContentLanguage>() { return "Content-Language"; }

			static std::string to_string(const Version version);
			static void value(const std::string& str, Version& version);

			static std::string to_string(const Connection connection);
			static void value(const std::string& str, Connection& connection);

			static std::string to_string(const Method method);
			static void value(const std::string& str, Method& method);
		};
	}
}