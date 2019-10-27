#include "uri.h"

namespace starnet
{
	Uri::Uri()
		: m_schema()
		, m_host()
		, m_port(0)
		, m_path()
		, m_fragment()
	{

	}
	
	Uri::Uri(const std::string& uriString)
		: m_schema()
		, m_host()
		, m_port(0)
		, m_path()
		, m_fragment()
	{
		// parse the uri

		// retrieve the schema
		const auto schemaDelimiter = uriString.find(':');
		m_schema = uriString.substr(0, schemaDelimiter);


	}
	
	bool Uri::isValid() const
	{
		return false;
	}

	std::string Uri::getAuthority() const
	{
		return std::string();
	}

	std::string Uri::getQuery() const
	{
		return std::string();
	}
	
	std::string Uri::toString() const
	{
		return std::string();
	}
}