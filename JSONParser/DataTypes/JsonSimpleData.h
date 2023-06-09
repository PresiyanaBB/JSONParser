#pragma once
#include "../ValueTypes/JsonValue.hpp"

//simple data types are string, number(int/double), bool, null
class JsonSimpleData : public JsonValue<MyString>
{
	//inherited:
	//MyString value and ValueTypes type

public:
	JsonSimpleData(MyString value);
};