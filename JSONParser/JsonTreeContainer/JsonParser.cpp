#include "JsonParser.h"

JsonParser::JsonParser(fstream& ifs)
{
	size_t i = 0;
	MyString currentValue;
	MyString json;

	while (!ifs.eof())
		json += ifs.get();

	size_t length = json.length();

	for (i = 0; i < length; i++)
	{
		if (json[i] == ' ' || json[i] == '\n')
			continue;

		if (json[i] == '{')
		{
			i++;
			break;
		}

		throw std::invalid_argument(INVALID_JSON_SYNTAX);
	}

	try
	{
		root.parse(json.substr(i, length - i),i);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

void JsonParser::print() const
{
	std::cout << root.stringify();
}