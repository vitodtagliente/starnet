#include <iostream>
#include <starnet/starnet.h>

using namespace std;
using namespace starnet;

int main()
{
	starnet::startup();

	NetworkAddress<NetworkProtocol::IPv4> address("127.0.0.1:80");

	cout << "Premi un tasto per continuare...";
	int exit;
	cin >> exit;

	starnet::shutdown();

	return 0;
}