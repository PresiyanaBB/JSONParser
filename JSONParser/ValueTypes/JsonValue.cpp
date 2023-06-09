#include "JsonValue.h"
#include "../DataTypes/JsonArray.h"
#include "../DataTypes/JsonObject.h"
#include "../DataTypes/JsonSimpleData.h"

JsonValue* JsonValue::setValue(const MyString& value, size_t& i)
{
	MyString k_value;
	MyString currentValue;

	if (value[i] == '\"')
	{
		currentValue += value[i];
		while (value[++i] != '\"')
		{
			currentValue += value[i];
		}
		currentValue += '\"';

		return new JsonSimpleData(currentValue);
	}

	if (value.substr(i, 4) == "true" || value.substr(i, 4) == "null")
	{
		currentValue = value.substr(i, 4);
		i += 4;
		return new JsonSimpleData(currentValue);
	}

	if (value.substr(i, 5) == "false")
	{
		currentValue = value.substr(i, 5);
		i += 5;
		return new JsonSimpleData(currentValue);
	}

	if (value[i] >= 0 && value[i] <= 9)
	{
		while (value[i] != ',')
			currentValue += value[i++];

		return new JsonSimpleData(currentValue);
	}

	if (value[i] == '{')
	{
		while (value[i] != '}')
			currentValue += value[i++];

		return new JsonObject(currentValue);
	}

	if (value[i] == '[')
	{
		while (value[i] != ']')
			currentValue += value[i++];

		return new JsonArray(currentValue);
	}
}
