#pragma once

#include "byte_stream.h"

namespace starnet
{
	class BitStream : public ByteStream
	{
	public:

		BitStream() : ByteStream() {};
		BitStream(const ByteBuffer& buffer) : ByteStream(buffer) {}

	protected:

		// byte counter
		uint32_t m_byteIndex{ 0 };
		// offset counter
		uint8_t m_offset{ 0 };
	};

	class OutputBitStream : public BitStream
	{
	public:

		OutputBitStream() : BitStream() 
		{
			// allocate one empty byte
			m_buffer.push_back({});
		}

		template<typename T>
		void write(const T data, const std::size_t bits = sizeof(T) * 8)
		{
			static constexpr uint8_t bits_per_byte = sizeof(std::byte) * 8;

			static_assert(std::is_fundamental<T>::value || std::is_enum<T>::value,
				"Generic write only supports primitive data type");

			if (m_offset == bits_per_byte)
			{
				m_buffer.push_back({});
				++m_byteIndex;
				m_offset = 0;
			}

			if (bits + m_offset <= bits_per_byte)
			{
				// make sure to write only n defined bits
				const uint8_t amount = bits_per_byte - bits;
				std::byte data_to_write = (std::byte(data) << amount) >> amount;
				m_buffer[m_byteIndex] |= data_to_write << m_offset;
				m_offset += (uint8_t)bits;			
			}
			else
			{
			}
		}

		int out()
		{
			return (int)(m_buffer[m_byteIndex]);
		}
	};

	class InputBitStream : public BitStream
	{
	public:

		InputBitStream(const ByteBuffer& buffer) : BitStream(buffer) {}
	};
}