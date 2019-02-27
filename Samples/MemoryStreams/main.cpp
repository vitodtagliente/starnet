#include <iostream>
#include <starnet/starnet.h>

using namespace std;
using namespace starnet;

enum class FooType : uint8_t
{
	None,
	Ciao,
	Prova
};

struct FVector
{
	int x;
	int y;
};

OutputByteStream& operator<< (OutputByteStream& stream, const FVector& vector)
{
	stream << vector.x;
	stream << vector.y;
	return stream;
}

InputByteStream& operator>> (InputByteStream& stream, FVector& vector)
{
	stream >> vector.x;
	stream >> vector.y;
	return stream;
}

int main()
{
	
	int number = 0;

	OutputMemoryStream os;
	os.write(5, 3);
	os.write(4, 3);
	os.write(0);
	
	InputMemoryStream is(os.getBuffer());
	is.read(number, 3);
	cout << number << endl;
	is.read(number, 4);
	cout << number << endl;


	cout << "Premi un tasto per continuare...";
	getchar();

	return 0;
}