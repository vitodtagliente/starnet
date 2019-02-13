// starnet.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include "starnet.h"
#include "reflection.h"

using namespace std;
using namespace starnet;

void server_main();
void client_main();

int main()
{
	static const int port = 9000;

	int choice = 0;
	cout << "[0: Server, 1: Client]: ";
	cin >> choice;

	if (starnet::startup())
	{
		if (choice == 0)
			server_main();
		else client_main();

		starnet::shutdown();
	}	

    cout << "Premi un tasto per continuare...";
	int pause;
	cin >> pause;
}

void server_main()
{
	Socket sck;
	if (sck.initialize(NetAddress::Family::IPv4))
	{
		NetAddress address(NetAddress::UnusedPort);
		if (address.isValid())
		{
			if (sck.bind(address))
			{
				cout << "Socket binded" << endl;
			}
			else starnet::log("Unable to bind the port");
		}
		else
		{
			if (address.getState() == NetAddress::State::Error)
				cout << "Address error" << endl;
			else cout << "Address malformed" << endl;
		}
	}
	else cout << "Cannot initialize the socket" << endl;
}

void client_main()
{

}