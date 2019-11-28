#include <iostream>
#include <starnet/starnet.h>
#include <starnet/json/json.h>

using namespace std;
using namespace starnet;

int main()
{
	json::data json = 4;
	json = "ciao";


	cout << "Premi un tasto per continuare...";
	getchar();

	return 0;
}