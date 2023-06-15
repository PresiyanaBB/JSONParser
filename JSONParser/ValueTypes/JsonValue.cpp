#include "JsonValue.h"
#include "../DataTypes/JsonArray.h"
#include "../DataTypes/JsonObject.h"
#include "../DataTypes/JsonSimpleData.h"

JsonValue* JsonValue::setValue(const MyString& value, size_t& i)
{
	while (value[i] == ' ' || value[i] == '\n' || value[i] == ',')
		i++;

	if (value[i] == '{')
		return new JsonObject(value, ++i);

	else if (value[i] == '[')
		return new JsonArray(value, ++i);

	else
		return new JsonSimpleData(value,i);
}

ValueTypes JsonValue::getType() const
{
	return type;
}

JsonValue*& JsonValue::find(DynamicArray<MyString> paths, size_t& ind)
{
	JsonValue* jv;
	return jv;
}
