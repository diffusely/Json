#include "json.hpp"

Json::Json(std::string file_name)
	: file_name(file_name)
{
	this->fin.open(file_name, std::ios::in);
}

Json::~Json()
{
	this->fin.close();
}

void Json::validation()
{
	char ch;
	fin.get(ch);

	read_isspace(ch);
	if (ch != '{')
	{
		std::cout << "start is not {\n";
		return ;
	}
	//std::cout << ch;
	while (fin.get(ch))
	{
		read_isspace(ch);
		if (ch != '"')
		{
			std::cout << "token is not start  \" \n";
			return ;
		}



		if (ch == '}')
			break ;
    }
	//std::cout << ch;
}

bool Json::is_space() const
{
	return false;
}

bool Json::is_string() const
{
	return false;
}

bool Json::is_array() const
{
	return false;
}

bool Json::is_object() const
{
	return false;
}

bool Json::is_number() const
{
	return false;
}

bool Json::is_boolean() const
{
	return false;
}

void Json::read_isspace(char &ch)
{
	while (isspace(ch) && fin.get(ch)) {}
}

