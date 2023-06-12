#pragma once
#include "../ValueTypes/JsonValue.h"

class JsonArray : public JsonValue
{
	JsonValue** values;
	
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const JsonArray& other);
	void moveFrom(JsonArray&& other);
	void resize();

public:
	JsonArray(const MyString& value, size_t& i);
	MyString stringify() const override;
	JsonValue* clone()  const override;
	void parse(const MyString& value, size_t& i) override;

	JsonArray(const JsonArray& other);
	JsonArray(JsonArray&& other);

	JsonArray& operator=(const JsonArray& other);
	JsonArray& operator=(JsonArray&& other);
};