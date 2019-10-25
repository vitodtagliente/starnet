#include <iostream>
#include <starnet/starnet.h>
#include <starnet/http/http.h>

using namespace std;
using namespace starnet;

int main()
{
	starnet::startup();

	Address address("127.0.0.1:9090");
	HTTPServer server(address, 20);
	if (server.listen())
	{
		cout << "Listening... " << address.toString() << endl;
	}

	Socket* clientSocket = server.getSocket()->accept();
	cout << "Client accepted" << endl;

	char buffer[3000];
	const std::size_t buffer_size = sizeof(buffer);
	int32_t byteRead{ 0 };

	while (true)
	{
		if (server.getSocket()->receive(
			reinterpret_cast<uint8_t*>(buffer),
			buffer_size,
			byteRead
		))
		{
			std::string data = { buffer, (unsigned int)byteRead };
			cout << data << endl;
		}
	}

	starnet::shutdown();

	return 0;
}