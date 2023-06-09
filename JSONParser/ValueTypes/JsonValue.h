#pragma once
#include "../Config/Configurations.h"
#include "../Config/String/MyString.h"

class JsonValue
{
protected:
	ValueTypes type = ValueTypes::null;

public:
	JsonValue() : type(ValueTypes::null) {};
	JsonValue(ValueTypes type) : type(type) {};
	virtual void parse(const MyString& value) = 0;
	JsonValue* setValue(const MyString& value, size_t& i);

	/// <summary>
	/// parse current json value to string
	/// </summary>
	virtual MyString stringify() const = 0;

	virtual JsonValue* clone()  const = 0;
	virtual ~JsonValue() = default;
};
