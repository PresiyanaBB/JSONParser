#include "JsonValue.h"

ValueTypes JsonValue::getType() const
{
	return type;
}

JsonValue*& JsonValue::find(DynamicArray<MyString> paths, size_t& ind)
{
	JsonValue* jv;
	return jv;
}
