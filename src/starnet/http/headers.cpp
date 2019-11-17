#include "headers.h"

namespace starnet
{
	namespace http
	{
		bool Headers::contains(const std::string& field) const
		{
			return find(field) != end();
		}
	}
}