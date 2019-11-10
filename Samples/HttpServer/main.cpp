#include <iostream>
#include <starnet/starnet.h>
#include <starnet/http/http.h>

#include <starnet/internet/message.h>
#include <starnet/internet/serialization.h>

using namespace std;
using namespace starnet;

int main()
{
	starnet::startup();

	Address address("127.0.0.1:9090");
	
	internet::Message message;

	http::Request request;
	http::Response response;

	cout << message.toString();
	message = internet::Message::parse(
		R"(HTTP/1.1 200 OK
		Date: Mon, 27 Jul 2009 12 : 28 : 53 GMT
		Server : Apache / 2.2.14 (Win32)
		Last - Modified : Wed, 22 Jul 2009 19 : 15 : 56 GMT
		Content - Length : 88
		Content - Type : text / html
		Connection : Closed
		
		<html>
		<body>

		<h1>Hello, World!< / h1>

		< / body>
		< / html>)");


	// http::Server server(address, 20);
	// if (server.listen())
	// {
	// 	cout << "Listening... " << address.toString() << endl;
	// }

	starnet::shutdown();

	return 0;
}