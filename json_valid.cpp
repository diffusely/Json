#include "json_valid.hpp"

JsonValid::JsonValid(std::string file_name)
{
	this->fin.open(file_name, std::ios::in);
	this->fin.get(ch);
}

JsonValid::~JsonValid()
{
	this->fin.close();
}

bool JsonValid::validate()
{
	try
	{
		parse_val();
        skip_isspace();
		if (!fin.eof())
			throw std::runtime_error("Wrong symbole end!\n");
	}
	catch(const std::exception &e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	return true;
}

void JsonValid::skip_isspace()
{
	while (isspace(ch) && fin.get(ch)) {}
}

void JsonValid::find_char(char c)
{
	skip_isspace();
	if (c != ch)
		throw std::runtime_error(std::string("Expected ") + c + std::string(" symbole\n"));
	if (!fin.get(ch))
		throw std::runtime_error(std::string("file is end!\n"));
}

void JsonValid::parse_val()
{
	skip_isspace();

	if (ch == '"') parse_str();
	else if (ch == '[') parse_arr();
	else if (ch == '{') parse_obj();
	else if (ch == 'f') parse_bool("false");
	else if (ch == 't') parse_bool("true");
	else if (ch == 'n') parse_bool("null");
	else if (isdigit(ch) || ch == '-' || ch == '+') parse_num();
	else if (!fin.get(ch));
	else throw std::runtime_error(std::string("Invalid value\n") + ch);
}

void JsonValid::parse_obj()
{
	find_char('{');
	skip_isspace();
	if (ch == '}')
	{
		fin.get(ch);
		return ;
	}

	while (true)
	{
		parse_str();
		find_char(':');
		parse_val();

		skip_isspace();
		if (ch == '}')
		{
			fin.get(ch);
			return;
		}
		find_char(',');

		// when have parsing errors xDD
		// skip_isspace();
		// if (ch == '}')
		// {
		// 	fin.get(ch);
		// 	return;
		// }
	}
	
}

void JsonValid::parse_str()
{
	find_char('"');

	while (true)
	{
		if (!fin.get(ch))
			throw std::runtime_error("string error!\n");
		if (ch == '\\')
		{
			if (!fin.get(ch))
				throw std::runtime_error("string error!\n");
			continue;
		}
		if (ch == '"')
		{
			fin.get(ch);
			return;
		}
	}
}

void JsonValid::parse_num()
{
	if (ch == '-' || ch == '+')
		fin.get(ch);

	while (isdigit(ch))
		if (!fin.get(ch))
			throw std::runtime_error("num error!!\n");

	if (ch == '.')
		fin.get(ch);

	while (isdigit(ch))
		if (!fin.get(ch))
			throw std::runtime_error("num error!!\n");
}

void JsonValid::parse_bool(const std::string &str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ch)
			throw std::runtime_error("string error!\n");
		if (!fin.get(ch))
			throw std::runtime_error("bool end error!\n");
	}
}

void JsonValid::parse_arr()
{
	find_char('[');
	skip_isspace();
	if (ch == ']')
	{
		fin.get(ch);
		return;
	}
	while (true)
	{
		parse_val();
		skip_isspace();
		if (ch == ']')
		{
			fin.get(ch);
			return;
		}
		find_char(',');
	}
}