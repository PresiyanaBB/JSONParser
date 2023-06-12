#pragma once
#include "../ValueTypes/JsonValue.h"

//simple data types are string, number(int/double), bool, null
class JsonSimpleData : public JsonValue
{
	MyString value;

public:
	JsonSimpleData(const MyString& value,size_t& i);
	void parse(const MyString& value,size_t& i) override;
	MyString stringify() const override;
	JsonValue* clone()  const override;
};