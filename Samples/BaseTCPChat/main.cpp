#include <conio.h>
#include <iostream>
#include <starnet/starnet.h>

using namespace std;
using namespace starnet;

void client_main();
void server_main();

#define SERVER_PORT 9670
#define CLIENT_PORT 9000

int main()
{
	int choice = 0;
	cout << "TCP Chat [0: Server, 1: Client]: ";
	cin >> choice;

	if (choice == 0)
		server_main();
	else client_main();

	cout << "Premi un tasto per continuare...";
	_getch();

	return 0;
}

void client_main()
{
	TCPSocket sock({ Address::localAddress, CLIENT_PORT });
	if (sock.isValid())
	{
		if (sock.connect({ Address::localAddress, SERVER_PORT }))
		{
			cout << "Socket connected successfully!" << endl;
			std::string message{};
			if (sock.receive(message))
			{
				cout << "Message: " << message << endl;
			}
			else cout << "Unable to receive a message" << endl;
		}
		else
		{
			cout << "Invalid socket connection: " << starnet::getErrorMessage() << endl;
		}
	}
	else
	{
		cout << "Invalid socket creation: " << starnet::getErrorMessage() << endl;
	}
}

void server_main()
{
	TCPSocket sock({ Address::localAddress, SERVER_PORT });
	if (sock.isValid())
	{
		if (sock.bind())
		{
			if (sock.listen())
			{
				cout << "Socket listening successfully!" << endl;

				if (TCPSocket* clientSocket = sock.accept())
				{
					cout << "Press to send a message...";
					int response;
					cin >> response;
					if (clientSocket->send("ciao mondo"))
					{
						cout << "Message sent!" << endl;
					}
					else cout << "Unable to send the message" << endl;
				}
				else cout << "Unable to accept client's socket" << endl;
			}
			else cout << "Unable to listen..." << endl;
		}
		else
		{
			cout << "Invalid socket binding: " << starnet::getErrorMessage() << endl;
		}
	}
	else
	{
		cout << "Invalid socket creation: " << starnet::getErrorMessage() << endl;
	}
}