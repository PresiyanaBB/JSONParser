#pragma once
#include "../ValueTypes/JsonValue.h"
#include "JsonObject.h"
#include "../Config/DynamicArray.hpp"
#include "JsonSimpleData.h"
#include "../ValueTypes/JsonValueFactory.h"

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
	JsonArray();
	MyString stringify() const override;
	JsonValue* clone()  const override;
	void parse(const MyString& value, size_t& i) override;

	JsonArray(const JsonArray& other);
	JsonArray(JsonArray&& other);

	void add(JsonValue* value);
	void add(JsonArray value);
	const size_t getSize() const;

	void search(const MyString& key) const override;
	void search(const MyString& key, bool (*criteria)(const MyString& lhs, const MyString& rhs)) const override;

	JsonArray& operator=(const JsonArray& other);
	JsonArray& operator=(JsonArray&& other);
	JsonArray& operator+=(const JsonArray& other);

	~JsonArray();
};