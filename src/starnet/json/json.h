#pragma once

#include <map>
#include <string>
#include <vector>

namespace starnet
{
	namespace json
	{
		class data
		{
		public:

			using string_t = std::string;
			using array_t = std::vector<data>;
			using object_t = std::map<string_t, data>;

			enum class Type
			{
				Array,
				Boolean,
				Null,
				Number,
				Object,
				String
			};

			data()
				: m_type(Type::Null)
				, m_numberType(NumberType::Undefined)
				, m_bool()
			{}

			data(const bool value)
				: m_type(Type::Boolean)
				, m_numberType(NumberType::Undefined)
				, m_bool(value)
			{}

			data(const int value)
				: m_type(Type::Number)
				, m_numberType(NumberType::Int)
				, m_int(value)
			{}

			data(const double value)
				: m_type(Type::Number)
				, m_numberType(NumberType::Double)
				, m_double(value)
			{}

			data(const float value)
				: m_type(Type::Number)
				, m_numberType(NumberType::Float)
				, m_float(value)
			{}

			data(const string_t& value)
				: m_type(Type::String)
				, m_numberType(NumberType::Undefined)
				, m_string(value)
			{}

			data(const array_t& value)
				: m_type(Type::Array)
				, m_numberType(NumberType::Undefined)
				, m_array(value)
			{}

			data(const object_t& value)
				: m_type(Type::Object)
				, m_numberType(NumberType::Undefined)
				, m_object(value)
			{}

			bool is_array() const { return m_type == Type::Array; }
			bool is_bool() const { return m_type == Type::Boolean; }
			bool is_null() const { return m_type == Type::Null; }
			bool is_number() const { return m_type == Type::Number; }
			bool is_object() const { return m_type == Type::Object; }
			bool is_string() const { return m_type == Type::String; }

			bool as_bool() const { return m_bool; }
			int as_int() const { return m_int; }
			float as_float() const { return m_float; }
			double as_double() const { return m_double; }
			const array_t& as_array() const { return m_array; }
			const object_t& ar_object() const { return m_object; }
			const string_t& as_string() const { return m_string; }

			Type type() const { return m_type; }

			string_t to_string() const 
			{ 
				switch (m_type)
				{
				case Type::Boolean: return std::to_string(m_bool);
				case Type::Null: return "";
				case Type::Array: return "";
				case Type::Object: return "";
				case Type::Number:
				{
					switch (m_numberType)
					{
					case NumberType::Int: return std::to_string(m_int);
					case NumberType::Double: return std::to_string(m_double);
					case NumberType::Float: return std::to_string(m_float);
					default: return "";
					}
				}
				default:
					return m_string;
				}
			}

			bool operator== (const data& other) const
			{
				if (m_type == other.m_type)
				{
					switch (m_type)
					{
					case Type::Boolean: return m_bool == other.m_bool;
					case Type::Null: return true;
					case Type::String: return m_string == other.m_string;
					/// #TODO
					}
				}
				return false;
			}

			bool operator!= (const data& other) const
			{
				return true; /// TODO
			}

			data& operator= (const data& other)
			{
				

				return *this;
			}

			data& operator= (const bool value)
			{
				

				return *this;
			}

			data& operator= (const int value)
			{
				m_type = Type::Number;
				m_int = value;

				return *this;
			}

			data& operator= (const double value)
			{
				m_type = Type::Number;
				m_numberType = NumberType::Double;
				m_double = value;

				return *this;
			}

			data& operator= (const float value)
			{
				m_type = Type::Number;
				m_numberType = NumberType::Float;
				m_float = value;

				return *this;
			}

			data& operator= (const std::string& value)
			{
				m_type = Type::String;
				m_string = value;

				return *this;
			}

			data& operator= (const array_t& value)
			{
				m_type = Type::Array;
				m_array = value;

				return *this;
			}

			data& operator= (const object_t& value)
			{
				m_type = Type::Object;
				m_object = value;

				return *this;
			}

		private:

			enum class NumberType
			{
				Undefined,
				Int,
				Float,
				Double
			};

			// value type
			Type m_type;
			NumberType m_numberType;
			// raw data
			union
			{
				bool m_bool;
				int m_int;
				float m_float;
				double m_double;
				std::string m_string;
				std::vector<data> m_array;
				std::map<std::string, data> m_object;
			};
		};
	}
}