#pragma once 

#include <cstddef>
#include <vector>

namespace starnet
{
	typedef std::vector<uint32_t> MemoryBuffer;

	class MemoryStream
	{
	public:

		MemoryStream() : m_buffer() {}
		MemoryStream(const std::size_t size) : m_buffer(size) 
		{
			m_bitSize = size * bits_per_byte;
		}
		MemoryStream(const MemoryBuffer& buffer) : m_buffer{ buffer } {}
		MemoryStream(const MemoryStream& stream) = delete;
		~MemoryStream() = default;

		inline const MemoryBuffer& getBuffer() const { return m_buffer; }
		inline const uint32_t* getNativeBuffer() const { return m_buffer.data(); }

		inline std::size_t getSize() const { return m_buffer.size(); }
		inline const uint32_t& getBitSize() const { return m_bitSize; }

	protected:

		// buffer of bytes
		MemoryBuffer m_buffer;
		// word index
		uint32_t m_wordIndex{ 0 };
		// number of available bits
		uint32_t m_bitSize{ 0 };

		static constexpr uint8_t bits_per_byte = 8;
		static constexpr uint8_t bits_per_word = sizeof(uint32_t) * bits_per_byte;

	};

	class OutputMemoryStream : public MemoryStream
	{
	public:

		OutputMemoryStream() : MemoryStream(1) {}
		OutputMemoryStream(const std::size_t size) : MemoryStream(size) {}

		template<typename T>
		void write(const T data, const std::size_t bits = sizeof(T) * bits_per_byte)
		{
			static_assert(std::is_fundamental<T>::value || std::is_enum<T>::value,
				"Generic write only supports primitive data type");

			if (constexpr(bits <= bits_per_word))
			{
				m_scratch |= (data << m_offset);
				m_offset += (uint8_t)bits;
				if (m_offset >= bits_per_word)
				{
					// #todo: endianness
					m_buffer[m_wordIndex] = (uint32_t)m_scratch;
					m_scratch >>= bits_per_word;
					m_buffer.push_back(0);
					++m_wordIndex;
					m_offset -= bits_per_word;
				}
			}
			else
			{

			}
		}

	private:
		// used to store temporary bits
		uint64_t m_scratch{ 0 };
		// scratch bit offset
		uint8_t m_offset{ 0 };
	};

	class InputMemoryStream : public MemoryStream
	{
	public:

		
	};
}