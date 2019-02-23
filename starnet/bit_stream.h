#pragma once

#include "byte_stream.h"

namespace starnet
{
	class OutputBitStream : public ByteStream
	{
	public:

		OutputBitStream() : ByteStream{} {}


	};

	class InputBitStream : public ByteStream
	{
	public:

		InputBitStream(const ByteBuffer& buffer) : 
			ByteStream{ buffer }, 
			m_byteIndex{ 0 },
			m_offset{ 0 }
		{
		
		}

	private:

		// byte counter
		uint32_t m_byteIndex;
		// offset counter
		uint8_t m_offset;
	};
}