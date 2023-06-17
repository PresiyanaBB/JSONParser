#pragma once
#include "../Config/Configurations.h"
#include "../Config/DynamicArray.hpp"
#include "../Config/String/MyString.h"

class JsonValue
{
protected:
	ValueTypes type = ValueTypes::null;

public:
	ValueTypes getType() const;

	JsonValue() : type(ValueTypes::null) {};
	JsonValue(ValueTypes type) : type(type) {};
	virtual void parse(const MyString& value, size_t& i) = 0;

	/// <summary>
	/// parse current json value to string
	/// </summary>
	virtual MyString stringify() const = 0;
	virtual JsonValue* clone()  const = 0;

	virtual void search(const MyString& key) const {}
	virtual void search(const MyString& key, bool (*criteria)(const MyString& lhs,const MyString& rhs)) const {}
	virtual JsonValue*& find(DynamicArray<MyString> paths, size_t& ind);

	virtual ~JsonValue() = default;
};
