#include "json_srl.hpp"

JsonSrl::JsonSrl(const std::string &name)
{
	JsonValid::is_valid(name);
	this->fin.open(name, std::ios::in);
	if (!fin)
		throw std::runtime_error("file is not open!\n");
}

Json JsonSrl::load_json(const std::string &name)
{
	JsonSrl j(name);
	return j.parse();
}

JsonSrl::~JsonSrl()
{
	this->fin.close();
}

Json JsonSrl::parse()
{
	skip_isspace();

	if (ch == '"') return parse_str();
	else if (ch == '[') return parse_arr();
	else if (ch == '{') return parse_obj();
	else if (ch == 'f') return parse_bool("false");
	else if (ch == 't') return parse_bool("true");
	else if (ch == 'n') return parse_bool("null");

	return parse_num();
}


Json JsonSrl::parse_num()
{
	std::string number;

	number.push_back(ch);
	while (fin.get(ch) && (std::isdigit(ch) || ch == '.'))
		number.push_back(ch);

	fin.unget(); // Back 1 ch

	if (number.find('.') != std::string::npos)
		return Json(std::stod(number));
	else
		return Json(std::stoi(number));
}

Json JsonSrl::parse_arr()
{
	Json::jsonArr arr;
	skip_isspace();
	if (ch == ']') return arr;
	fin.unget();
	while (true)
	{
		arr.push_back(parse());
		skip_isspace();
		if (ch == ']') break;
	}
	return Json(arr);
}

Json JsonSrl::parse_obj()
{
	Json::jsonObj obj;
	skip_isspace();
	if (ch == '}') return obj;
	fin.unget();

	while (true)
	{
		skip_isspace();
		Json temp = parse_str();

		skip_isspace();
		Json val = parse();
		obj[temp.get_string()] = val;

		skip_isspace();
		if (ch == '}') break;
	}
	return Json(obj);
}

void JsonSrl::skip_isspace()
{
	while (fin.get(ch) && std::isspace(ch)) {}
}

Json JsonSrl::parse_str()
{
	std::string str;
	while (fin.get(ch))
	{
		if (ch == '"') break;
		if (ch == '\\')
		{
			fin.get(ch);
			if (ch == '"') str.push_back('"');
			else if (ch == 'n') str.push_back('\n');
			else if (ch == 't') str.push_back('\t');
			else str.push_back(ch);
		}
		else
			str.push_back(ch);
	}
	return Json(str);
}

Json JsonSrl::parse_bool(const std::string &str)
{
	for (int i = 0; i < str.size() - 1; i++)
		fin.get(ch);
	if (str == "true")
		return Json(true);
	else if (str == "false")
		return Json(false);
	return Json(nullptr);
}
