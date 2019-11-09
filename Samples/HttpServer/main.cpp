#include <iostream>
#include <starnet/starnet.h>
#include <starnet/http/http.h>

#include <starnet/internet/message.h>
#include <starnet/internet/message_serialization.h>

using namespace std;
using namespace starnet;

int main()
{
	starnet::startup();

	Address address("127.0.0.1:9090");
	
	internet::Message message;
	http::Request request;
	http::Response response;

	cout << serialize(message);


	// http::Server server(address, 20);
	// if (server.listen())
	// {
	// 	cout << "Listening... " << address.toString() << endl;
	// }

	starnet::shutdown();

	return 0;
}