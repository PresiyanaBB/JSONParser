#pragma once
#include "../ValueTypes/KeyValuePair.h"
#include "../Config/DynamicArray.hpp"
#include "JsonArray.h"
#include "../ValueTypes/JsonValue.h"
#include "JsonSimpleData.h"

class JsonObject : public JsonValue
{
	MyString setKey(const MyString& value, size_t& i);
	DynamicArray<KeyValuePair> pairs;

public:
	JsonObject();

	JsonObject(const MyString& value, size_t& i);
	void parse(const MyString& value,size_t& i) override;
	MyString stringify() const override;
	JsonValue* clone()  const override;

	void search(const MyString& key) const override;
	void search(const MyString& key, bool (*criteria)(const MyString& lhs, const MyString& rhs)) const override;
	JsonValue*& find(DynamicArray<MyString> paths, size_t& ind) override;
};