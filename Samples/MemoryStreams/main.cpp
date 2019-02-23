#include <conio.h>
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
	OutputByteStream os;
	os << 13;
	os << (uint8_t)2;
	os << FVector{ 1, 5 };
	os << 's';
	os << 4.12f;
	os << FooType::Prova;

	InputByteStream is{ os.getBuffer() };
	int number;
	is >> number;
	uint8_t n2;
	is >> n2;
	FVector f{};
	is >> f;
	
	cout << "Premi un tasto per continuare...";
	_getch();

	return 0;
}