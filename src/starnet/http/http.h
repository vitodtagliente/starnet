#pragma once 

#include <cstddef>
#include "client.h"
#include "message.h"
#include "server.h"
#include "url.h"

namespace starnet
{
	namespace http
	{
		enum class Version : uint8_t
		{
			v1,
			v2
		};
	}
}