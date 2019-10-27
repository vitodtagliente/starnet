#pragma once

/* 
 * This Uri class is used to parse URIs from strings,
 * render URIs as strings,
 * and get or set individual components of a URIs
 *
 * Implements RFC 3986, "Uniform Resource Identifier (URI): Generic Syntax"
 * https://www.ietf.org/rfc/rfc3986.txt
 *
 * The generic URI syntax consists of a hierarchical sequence of
 * components referred to as the scheme, authority, path, query, and
 * fragment.
 *
 * The following are two example URIs and their component parts:
 *
 *       foo://example.com:8042/over/there?name=ferret#nose
 *       \_/   \______________/\_________/ \_________/ \__/
 *        |           |            |            |        |
 *     scheme     authority       path        query   fragment
 *        |   _____________________|__
 *       / \ /                        \
 *       urn:example:animal:ferret:nose
 */

#include <string>
#include <vector>
#include <unordered_map>

namespace starnet
{
	namespace internet
	{
		class Uri
		{
		public:

			Uri();
			Uri(const std::string& uriString);
			Uri(const Uri& other);

			bool isValid() const;

			inline std::string getScheme() const { return m_schema; }
			inline std::string getAuthority() const;
			inline std::string getHost() const { return m_host; }
			inline uint16_t getPort() const { return m_port; }
			inline std::vector<std::string> getPath() const { return m_path; }
			std::string getQuery() const;
			inline std::string getFragment() const { return m_fragment; }

			bool hasPort() const;

			std::string toString() const;

			Uri& operator= (const Uri& other);
			bool operator== (const Uri& other) const;
			bool operator!= (const Uri& other) const;

		private:

			std::string m_schema;
			std::string m_host;
			uint16_t m_port;
			std::vector<std::string> m_path;
			std::unordered_map<std::string, std::string> m_query;
			std::string m_fragment;

			static std::vector<std::string> split(const std::string& str, const char delimiter);

		};
	}
}