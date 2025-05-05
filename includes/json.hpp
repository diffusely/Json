#pragma once

#include "json_valid.hpp"

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include <sstream>
#include <tuple>
#include <algorithm>

class Json
{
public:

	using jsonObj = std::unordered_map<std::string, Json>;
	using jsonArr = std::vector<Json>;

	using jsonValue = std::variant
		<
			std::nullptr_t,
			std::string,
			int,
			double,
			bool,
			jsonObj,
			jsonArr >;

public:

	Json() {}
	Json(std::nullptr_t) : value(nullptr) {}
	Json(const char *str) : value(std::string(str)) {}
	Json(std::string str) : value(str) {}
	Json(int num) : value(num) {}
	Json(double num) : value(num) {}
	Json(bool b) : value(b) {}
	Json(jsonObj obj) : value(obj) {}
	Json(jsonArr arr) : value(arr) {}

	~Json();

	bool is_string() const;
	bool is_array() const;
	bool is_object() const;
	bool is_number() const;
	bool is_boolean() const;

	const std::string& get_string() const;

	Json& operator=(const char* str);
    Json& operator=(const std::string& str);
    Json& operator=(int num);
    Json& operator=(double num);
    Json& operator=(bool b);
    Json& operator=(const jsonObj& obj);
    Json& operator=(const jsonArr& arr);
    Json& operator=(std::nullptr_t);
	Json& operator[](const std::string& key);

	void print(int indent = 0) const;


private:
	jsonValue value;

};