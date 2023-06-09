#pragma once
#include "JsonValue.hpp"

template<typename T>
class KeyValuePair
{
protected:
	MyString key;
	JsonValue value;

public:
	virtual KeyValuePair* clone() const = 0;
	virtual ~KeyValuePair() = default;
};