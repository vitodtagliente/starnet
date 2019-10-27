#include "uri.h"

namespace starnet
{
	Uri::Uri()
		: m_schema()
		, m_host()
		, m_port(0)
		, m_path()
		, m_query()
		, m_fragment()
	{

	}
	
	Uri::Uri(const std::string& uriString)
		: m_schema()
		, m_host()
		, m_port(0)
		, m_path()
		, m_query()
		, m_fragment()
	{
		// extract the schema
		const auto schemaDelimiter = uriString.find(':');
		m_schema = uriString.substr(0, schemaDelimiter);

		// extract the authority component
		std::string temp = uriString.substr(schemaDelimiter + 1, uriString.length());
		if (temp.substr(0, 2) == "//") 
		{
			const auto authorityDelimiter = temp.find('/', 2);
			const std::string& authority = temp.substr(2, authorityDelimiter - 2);

			const auto hostDelimiter = authority.find(':');
			if (hostDelimiter != std::string::npos)
			{
				m_host = authority.substr(0, hostDelimiter);
				m_port = std::atoi(authority.substr(hostDelimiter + 1, authority.length()).c_str());
			}
			else
			{
				m_host = authority;
			}

			temp = temp.substr(authorityDelimiter + 1, temp.length());
		}

		// extract the fragment
		const auto fragmentDelimiter = temp.find('#');
		if (fragmentDelimiter != std::string::npos)
		{
			m_fragment = temp.substr(fragmentDelimiter + 1, temp.length());

			temp = temp.substr(0, fragmentDelimiter);
		}

		// extract the query
		const auto queryDelimiter = temp.find('?');
		if (queryDelimiter != std::string::npos)
		{
			std::string query = temp.substr(queryDelimiter + 1, temp.length());
			

			temp = temp.substr(0, queryDelimiter);
		}

		// extract the path

	}
	
	bool Uri::isValid() const
	{
		return false;
	}

	std::string Uri::getAuthority() const
	{
		if (m_port > 0)
			return m_host + ":" + std::to_string(m_port);
		return m_host;
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