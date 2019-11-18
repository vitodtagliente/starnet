#pragma once

#include <map>
#include <string>
#include <vector>

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

			Value(const std::vector<Value>& values)
				: m_type(Type::Array)
				, m_values(values)
			{}

			bool is_array() const { return m_type == Type::Array; }
			bool is_bool() const { return m_type == Type::Boolean; }
			bool is_null() const { return m_type == Type::Null || m_value.length() == 0; }
			bool is_number() const { return m_type == Type::Number; }
			bool is_object() const { return m_type == Type::Object; }
			bool is_string() const { return m_type == Type::String; }

			bool as_bool() const { return static_cast<bool>(std::atoi(m_value.c_str())); }
			int as_int() const { return std::atoi(m_value.c_str()); }
			float as_float() const { return std::atof(m_value.c_str()); }
			double as_double() const { return std::stod(m_value.c_str()); }
			const std::string& as_string() const { return m_value; }

			std::string to_string() const { return m_value; }

			bool operator== (const Value& other) const
			{
				return m_type == other.m_type
					&& m_value == other.m_value;
			}

			bool operator!= (const Value& other) const
			{
				return m_type != other.m_type
					|| m_value != other.m_value;
			}

			Value& operator= (const Value& other)
			{
				m_type = other.m_type;
				m_value = other.m_value;

				return *this;
			}

			Value& operator= (const bool value)
			{
				m_type = Type::Boolean;

				return *this;
			}

			Value& operator= (const int value)
			{
				m_type = Type::Number;

				return *this;
			}

			Value& operator= (const double value)
			{
				m_type = Type::Number;

				return *this;
			}

			Value& operator= (const float value)
			{
				m_type = Type::Number;

				return *this;
			}

			Value& operator= (const std::string& value)
			{
				m_type = Type::String;

				return *this;
			}

		private:

			// value type
			Type m_type;
			// raw data
			union
			{
				std::string m_value;
				std::vector<Value> m_values;
				std::map<std::string, Value> m_propeties;
			};
		};
	}
}