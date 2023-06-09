#pragma once
#include "../Config/Configurations.h"
#include "../Config/String/MyString.h"

template <typename T>
class JsonValue
{
protected:
	ValueTypes type = ValueTypes::null;
	T value;
};