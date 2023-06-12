#pragma once
#include <iostream>
#include <fstream>
#include "../DataTypes/JsonObject.h"
using std::fstream;

class JsonParser
{
	JsonObject root;

public:
	JsonParser(fstream& ifs);

	void print() const;
};