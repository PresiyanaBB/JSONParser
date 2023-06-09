#include "JsonParser.h"

JsonParser::JsonParser(fstream& ifs)
{
	size_t i = 0;
	MyString currentValue;
	MyString json;

	while (!ifs.eof())
		json += ifs.get();

	root.parse(json);
}