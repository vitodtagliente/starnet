#include <iostream>
#include <starnet/starnet.h>
#include <starnet/internet/uri.h>

using namespace std;
using namespace starnet;

int main()
{
	internet::Uri uri("foo://example.com:8042/over/there?name=ferret#nose");
	internet::Uri urn("urn:example:animal:ferret:nose");
	cout << uri.toString() << endl;

	return 0;
}