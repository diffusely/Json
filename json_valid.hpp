#pragma

#include <fstream>
#include <iostream>

class JsonValid
{
public:
	JsonValid(std::string file_name);
	~JsonValid();

	bool validate();

private:
	// For read
	char ch;
	std::fstream fin;

private:
	// Read file function
	void read_file();

	// Parse funcitons
	void skip_isspace();
	void find_char(char ch);
	void parse_val();
	void parse_obj();
	void parse_str();
	void parse_num();
	void parse_bool(const std::string &str);
	void parse_arr();
};