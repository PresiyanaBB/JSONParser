#pragma once
#include "../ValueTypes/KeyValuePair.h"
#include "../Config/DynamicArray.hpp"

class JsonObject : public JsonValue
{
	DynamicArray<KeyValuePair> pairs;
	MyString setKey(const MyString& value, size_t& i);

public:
	JsonObject();
	JsonObject(const MyString& value);
	void parse(const MyString& value) override;
	MyString stringify() const override;
	JsonValue* clone()  const override;
};