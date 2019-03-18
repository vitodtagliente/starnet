#include <iostream>
#include <starnet/starnet.h>

using namespace std;
using namespace starnet;

const Address::port_t SERVER_PORT = 9001;
const Address::port_t CLIENT_PORT = 9000;

void client_main();
void server_main();

int main()
{
	starnet::startup();

	int choice = 0;
	cout << "UDP Chat [0: Server, 1: Client]: ";
	cin >> choice;

	if (choice == 0)
		server_main();
	else client_main();

	cout << "Premi un tasto per continuare...";
	int exit;
	cin >> exit;

	starnet::shutdown();

	return 0;
}

void client_main()
{
	Address address{ "127.0.0.1", CLIENT_PORT };
	Address server{ "127.0.0.1", SERVER_PORT };
	Socket socket(address, Socket::TransportProtocol::UDP);
	if (socket.bind())
	{
		std::string message;
		cin >> message;
		cout << "Sending: " << message << endl;

		int32_t byteSent = 0;
		socket.sendTo(server, reinterpret_cast<const uint8_t*>(message.data()), message.size(), byteSent);
	}
}

void server_main() 
{
	Address address{ "127.0.0.1", SERVER_PORT };
	Socket socket(address, Socket::TransportProtocol::UDP);
	if (socket.bind())
	{
		uint8_t buffer[100];
		const std::size_t buffer_size = sizeof(buffer);

		Address client;
		int32_t byteRead{ 0 };
		int32_t byteSent{ 0 };
		while (socket.receiveFrom(client, buffer, buffer_size, byteRead))
		{
			std::string message{ reinterpret_cast<char*>(buffer), (unsigned int)byteRead };
			cout << message << endl;
			socket.sendTo(client, buffer, buffer_size, byteSent);
		}
	}
}