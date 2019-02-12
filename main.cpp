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

	if (choice == 0)
		server_main();
	else client_main();
	
    cout << "Premi un tasto per continuare...";
	int pause;
	cin >> pause;
}

void server_main()
{

}

void client_main()
{

}