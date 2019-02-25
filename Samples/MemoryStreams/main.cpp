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

	// 5: 101
	OutputBitStream obs;
	obs.write((uint8_t)5, 7);
	obs.write(5);

	InputBitStream ibs(obs.getBuffer());
	ibs.read(number, 6);
	cout << number << endl;
	
	cout << "Premi un tasto per continuare...";
	getchar();

	return 0;
}