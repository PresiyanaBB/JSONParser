#pragma once
#include "../ValueTypes/KeyValuePair.h"
#include "../ValueTypes/JsonValueFactory.h"

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

	DynamicArray<KeyValuePair>& getPairs();
	void search(const MyString& key) const override;
	void search(const MyString& key, bool (*criteria)(const MyString& lhs, const MyString& rhs)) const override;
	JsonValue*& find(DynamicArray<MyString> paths, size_t& ind) override;
};