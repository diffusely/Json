#include "json_valid.hpp"

JsonValid::JsonValid(std::string file_name)
	: find(false)
{
	this->fin.open(file_name, std::ios::in);
	if (!this->fin.is_open())
		throw std::runtime_error("Failed to open the file: " + file_name);
	this->fin.get(ch);
}

JsonValid::~JsonValid()
{
	this->fin.close();
}

bool JsonValid::validate()
{
	valid_val();
	skip_isspace();
	if (!fin.eof())
		throw std::runtime_error("Wrong symbole end!");
	return true;
}

bool JsonValid::is_valid(const std::string &file_name)
{
	JsonValid validator(file_name);
	return validator.validate();
}

void JsonValid::skip_isspace()
{
	while (isspace(ch) && fin.get(ch)) {}
}

void JsonValid::find_char(char c)
{
	skip_isspace();
	if (c != ch)
		throw std::runtime_error(std::string("Expected ") + c + std::string(" symbole!"));
	if (!fin.get(ch))
		throw std::runtime_error(std::string("file is end!"));
}

void JsonValid::valid_val()
{
	skip_isspace();

	find = false;
	if (ch == '"') valid_str();
	else if (ch == '[') valid_arr();
	else if (ch == '{') valid_obj();
	else if (ch == 'f') valid_bool("false");
	else if (ch == 't') valid_bool("true");
	else if (ch == 'n') valid_bool("null");
	else if (isdigit(ch) || ch == '-' || ch == '+') valid_num();
	else if (!fin.get(ch) && find);
	else throw std::runtime_error(std::string("Invalid value ") + ch);
}

void JsonValid::valid_obj()
{
	find_char('{');
	skip_isspace();
	if (ch == '}')
	{
		find = true;
		if (!fin.get(ch))
			ch = 'e';
		return ;
	}

	while (true)
	{
		valid_str();
		find_char(':');
		valid_val();

		skip_isspace();
		if (ch == '}')
		{
			find = true;
			if (!fin.get(ch))
				ch = 'e';
			return;
		}
		find_char(',');
	}
	
}

void JsonValid::valid_str()
{
	find_char('"');

	while (true)
	{
		if (ch == '\\')
		{
			if (!fin.get(ch))
				throw std::runtime_error("string error!");
			continue;
		}
		if (ch == '"')
		{
			find = true;
			fin.get(ch);
			return;
		}
		if (!fin.get(ch))
			throw std::runtime_error("string error!");
	}
}

void JsonValid::valid_num()
{
	char prev;
	if (ch == '-' || ch == '+')
		fin.get(ch);

	while (isdigit(ch))
	{
		find = true;
		prev = ch;
		if (!fin.get(ch))
			break;
	}

	if (!isdigit(prev))
		throw std::runtime_error("num error!");
	if (ch == '.')
	{	
		prev = ch;
		fin.get(ch);
	}

	while (isdigit(ch))
	{
		prev = ch;
		if (!fin.get(ch))
			break;
	}
	if (prev == '.')
		throw std::runtime_error("double num error!");
}

void JsonValid::valid_bool(const std::string &str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ch)
			throw std::runtime_error("string error!");
		if (!fin.get(ch) && i != str.size() - 1)
			throw std::runtime_error("bool error!");
	}
}

void JsonValid::valid_arr()
{
	find_char('[');
	skip_isspace();
	if (ch == ']')
	{
		find = true;
		fin.get(ch);
		return;
	}
	while (true)
	{
		valid_val();
		skip_isspace();
		if (ch == ']')
		{
			find = true;
			fin.get(ch);
			return;
		}
		find_char(',');
	}
}