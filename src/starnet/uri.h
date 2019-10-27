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

namespace starnet
{
	class Uri
	{
	public:

		Uri();
		Uri(const std::string& uriString);

		bool isValid() const;

	private:


	};
}