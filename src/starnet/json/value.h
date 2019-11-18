#pragma once

#include <string>

namespace starnet
{
	namespace json
	{
		class Value
		{
		public:

			enum class Type
			{
				Array,
				Boolean,
				Null,
				Number,
				Object,
				String
			};

			Value()
				: m_type(Type::Null)
				, m_value()
			{}

			Value(const bool value)
				: m_type(Type::Boolean)
				, m_value(std::to_string(value))
			{}

			Value(const int value)
				: m_type(Type::Number)
				, m_value(std::to_string(value))
			{}

			Value(const double value)
				: m_type(Type::Number)
				, m_value(std::to_string(value))
			{}

			Value(const float value)
				: m_type(Type::Number)
				, m_value(std::to_string(value))
			{}

			Value(const std::string& value)
				: m_type(Type::String)
				, m_value(value)
			{}

			bool is_array() const { return m_type == Type::Array; }
			bool is_bool() const { return m_type == Type::Boolean; }
			bool is_null() const { return m_type == Type::Null || m_value.length() == 0; }
			bool is_number() const { return m_type == Type::Number; }
			bool is_object() const { return m_type == Type::Object; }
			bool is_string() const { return m_type == Type::String; }

			std::string to_string() const { return m_value; }

		private:

			// value type
			Type m_type;
			// real value
			std::string m_value;
		};
	}
}