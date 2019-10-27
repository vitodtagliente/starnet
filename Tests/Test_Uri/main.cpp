#include <iostream>
#include <starnet/starnet.h>
#include <starnet/uri.h>

using namespace std;
using namespace starnet;

int main()
{
	Uri uri("foo://example.com:8042/over/there?name=ferret#nose");
	Uri urn("urn:example:animal:ferret:nose");

	return 0;
}