#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>

namespace starnet
{
	typedef std::vector<std::byte> ByteBuffer;

	class OutputMemoryStream
	{
	public:

		OutputMemoryStream() : m_buffer{}
		{

		}

		inline const ByteBuffer& getBuffer() const { return m_buffer; }
		inline const std::byte* getNativeBuffer() const { return m_buffer.data(); }
		inline const size_t& getSize() const { return m_buffer.size(); }

		template<typename T>
		OutputMemoryStream& operator<< (T data)
		{
			static_assert(std::is_fundamental<T>::value || std::is_enum<T>::value,
				"Generic write only supports primitive data type");

			const std::byte* begin = reinterpret_cast<const std::byte*>(std::addressof(data));
			const std::byte* end = begin + sizeof(T);

			m_buffer.insert(m_buffer.end(), begin, end);

			return *this;
		}

	private:
				
		// buffer of bytes
		ByteBuffer m_buffer;
	};

	class InputMemoryStream
	{
	public:

		InputMemoryStream()
		{

		}

	private:

		// buffer of bytes
		ByteBuffer m_buffer;
	};
}
