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
		public:

			template <typename T>
			bool contains() const
			{
				return contains(Header::name<T>());
			}

			bool contains(const std::string& field) const;
			
			template <typename T>
			void set(const std::string& value)
			{
				const auto it = find(Header::name<T>());
				if (it != end())
				{
					it->second = value;
				}
			}

			template <typename T>
			std::string value() const
			{
				const auto it = find(Header::name<T>());
				if (it != end())
					return it->second;
				return {};
			}

		private:

		};
	}
}