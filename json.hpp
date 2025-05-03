#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class Json
{
public:

	Json(std::string file_name);
	~Json();

	void validation();

	void open_file();

	bool is_space() const;
	bool is_string() const;
	bool is_array() const;
	bool is_object() const;
	bool is_number() const;
	bool is_boolean() const;

private:
	std::fstream fin;
	std::string file_name;

	std::unordered_map<std::string, int> data;

private:

	// Help functions
	void read_isspace(char &ch);
};