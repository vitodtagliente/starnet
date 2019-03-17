#include "..\starnet\address.h"

namespace starnet
{
	Address::Address(const std::string & address, const NetworkProtocol protocol)
		: m_protocol(protocol)
	{
		// #todo: 
	}

	Address::~Address()
	{
		m_address = native_addr_t{};
		m_protocol = NetworkProtocol::Unknown;
	}

	bool Address::isValid() const
	{
		return m_protocol != NetworkProtocol::Unknown;
	}
}