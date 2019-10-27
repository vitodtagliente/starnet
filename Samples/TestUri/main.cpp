#include <iostream>
#include <starnet/starnet.h>
#include <starnet/http/http.h>

using namespace std;
using namespace starnet;

int main()
{
	starnet::startup();

	Address address("127.0.0.1:9090");
	http::Server server(address, 20);
	if (server.listen())
	{
		cout << "Listening... " << address.toString() << endl;
	}

	starnet::shutdown();

	return 0;
}