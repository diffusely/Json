#pragma once

#include <fstream>
#include <iostream>
#include <string>

class JsonValid
{
public:
	// Brilliant
	static bool is_valid(const std::string &file_name);

private:
	// Ctor and Dtor
	JsonValid(std::string file_name);
	~JsonValid();
	bool validate();

private:
	// For read
	char ch;
	bool find;
	std::fstream fin;

private:
	// Deleted
	JsonValid(const JsonValid&) = delete;
	JsonValid& operator=(const JsonValid&) = delete;
	JsonValid(JsonValid&&) = delete;
	JsonValid& operator=(JsonValid&&) = delete;

protected:
	// Parse funcitons
	void skip_isspace();
	void find_char(char ch);
	void valid_val();
	void valid_obj();
	void valid_str();
	void valid_num();
	void valid_bool(const std::string &str);
	void valid_arr();
};