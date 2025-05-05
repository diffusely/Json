#pragma once

#include "json_valid.hpp"
#include "json.hpp"

#include <string>
#include <sstream>

class JsonSrl
{
private:

	JsonSrl(const std::string &name);
	~JsonSrl();

public:

	// Read file and load in json
	static Json load_json(const std::string &name);

private:
	// Deleted
	JsonSrl(const JsonValid&) = delete;
	JsonSrl& operator=(const JsonSrl&) = delete;
	JsonSrl(JsonSrl&&) = delete;
	JsonSrl& operator=(JsonSrl&&) = delete;

private:
	// Write
	char ch;
	std::fstream fin;
	Json obj;
private:

	void skip_isspace();	
	Json parse_obj();
	Json parse_arr();
	Json parse_bool(const std::string &str);
	Json parse_num();
	Json parse_str();
	Json parse();
};
