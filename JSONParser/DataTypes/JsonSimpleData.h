#pragma once
#include "../ValueTypes/JsonValue.h"

//simple data types are string, number(int/double), bool, null
class JsonSimpleData : public JsonValue
{
	MyString value;

public:
	JsonSimpleData(const MyString& value,size_t& i);
	void parse(const MyString& value,size_t& i) override;
	JsonValue*& find(DynamicArray<MyString> paths, size_t& ind) override;
	MyString stringify() const override;
	JsonValue* clone()  const override;
};