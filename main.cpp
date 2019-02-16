// starnet.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include "starnet.h"

using namespace std;
using namespace starnet;

void server_main_udp();
void client_main_udp();

void server_main_tcp();
void client_main_tcp();

int main()
{
	static const int port = 9000;

	int choice = 0;
	cout << "[0: Server, 1: Client]: ";
	cin >> choice;

	if (starnet::startup())
	{
		if (choice == 0)
			server_main_tcp();
		else client_main_tcp();

		starnet::shutdown();
	}	

    cout << "Premi un tasto per continuare...";
	int pause;
	cin >> pause;
}

void server_main_udp()
{
	UDPSocket sock({ Address::localAddress, 9706 });
	if (sock.isValid())
	{
		if (sock.bind())
		{
			cout << "Socket binded successfully!" << endl;
			cout << "Press to send a message...";
			int response;
			cin >> response;
			if (sock.send("ciao mondo", { Address::localAddress, 9000 }))
			{
				cout << "Message sent!" << endl;
			}
			else cout << "Unable to send the message" << endl;
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

void server_main_tcp()
{
	TCPSocket sock({ Address::localAddress, 9706 });
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

void client_main_udp()
{
	UDPSocket sock({ Address::localAddress, 9000 });
	if (sock.isValid())
	{
		if (sock.bind())
		{
			cout << "Socket binded successfully!" << endl;
			std::string message{};
			Address fromAddress{};
			if (sock.receive(message, fromAddress))
			{
				cout << "Message: " << message << endl;
			}
			else cout << "Unable to receive a message" << endl;
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

void client_main_tcp()
{
	TCPSocket sock({ Address::localAddress, 9000 });
	if (sock.isValid())
	{
		if (sock.connect({ Address::localAddress, 9706 }))
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