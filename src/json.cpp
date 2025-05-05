#include "json.hpp"

Json::~Json() {}

const std::string& Json::get_string() const 
{
	if (!is_string())
		throw std::runtime_error("Json value is not a string");
	return std::get<std::string>(value);
}

bool Json::is_string() const
{
	return std::holds_alternative<std::string>(value);
}

bool Json::is_array() const
{
	return std::holds_alternative<jsonArr>(value);
}

bool Json::is_object() const
{
	return std::holds_alternative<jsonObj>(value);
}

bool Json::is_number() const
{
	return std::holds_alternative<int>(value) || std::holds_alternative<double>(value);
}

bool Json::is_boolean() const
{
	return std::holds_alternative<bool>(value);
}

Json& Json::operator=(const char* str)
{
	value = std::string(str);
	return *this;
}

Json& Json::operator=(const std::string& str)
{
	value = str;
	return *this;
}

Json& Json::operator=(int num)
{
	value = num;
	return *this;
}

Json& Json::operator=(double num)
{
	value = num;
	return *this;
}

Json& Json::operator=(bool b)
{
	value = b;
	return *this;
}

Json& Json::operator=(const jsonObj& obj)
{
	value = obj;
	return *this;
}

Json& Json::operator=(const jsonArr& arr)
{
	value = arr;
	return *this;
}

Json& Json::operator=(std::nullptr_t)
{
	value = nullptr;
	return *this;
}

Json& Json::operator[](const std::string& key)
{
	if (!is_object())
		value = jsonObj{};

	jsonObj &obj = std::get<jsonObj>(value);
	return obj[key];
}

void Json::print(int indent) const
{
	const std::string ind(indent, ' ');

	std::visit([&](auto&& arg) {
		using T = std::decay_t<decltype(arg)>;

		if constexpr (std::is_same_v<T, std::nullptr_t>)
		{
			std::cout << "null";
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			std::cout << '"' << arg << '"';
		}
		else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>)
		{
			std::cout << arg;
		}
		else if constexpr (std::is_same_v<T, bool>)
		{
			std::cout << (arg ? "true" : "false");
		}
		else if constexpr (std::is_same_v<T, jsonObj>)
		{
			std::cout << "{\n";
			for (auto it = arg.begin(); it != arg.end(); ++it)
			{
				std::cout << ind << "  \"" << it->first << "\": ";
				it->second.print(indent + 2);
				if (std::next(it) != arg.end())
					std::cout << ",";
				std::cout << "\n";
			}
			std::cout << ind << "}";
		}
		else if constexpr (std::is_same_v<T, jsonArr>)
		{
			std::cout << "[\n";
			for (size_t i = 0; i < arg.size(); ++i)
			{
				std::cout << ind << "  ";
				arg[i].print(indent + 2);
				if (i < arg.size() - 1)
					std::cout << ",";
				std::cout << "\n";
			}
			std::cout << ind << "]";
		}
	}, value);
}
