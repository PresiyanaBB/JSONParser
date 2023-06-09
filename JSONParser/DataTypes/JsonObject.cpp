#include "JsonObject.h"
#include "JsonArray.h"
#include "JsonSimpleData.h"

JsonObject::JsonObject(const MyString& value) : JsonValue(ValueTypes::object)
{
	parse(value);
}

JsonObject::JsonObject() : JsonValue(ValueTypes::object) {}

void JsonObject::parse(const MyString& value)
{
	size_t i = 0;
	size_t count = value.length();
	bool hasKey = false;

	for (size_t i = 0; i < count; i++)
	{
		KeyValuePair currentPair;
		if (value[i] == ' ' || value[i] == '\n')
			continue;
		
		if (!hasKey)
		{
			currentPair.key = setKey(value,i);
			hasKey = true;
			
			while (value[i++] != ':');
		}

		else
		{
			currentPair.value = setValue(value,i);
			hasKey = false;

			while (value[i++] != ',');
			
			pairs.add(currentPair);
		}
	}
}

MyString JsonObject::setKey(const MyString& value,size_t& i)
{
	MyString key;

	if (value[i] != '\"')
		throw std::invalid_argument(INVALID_KEY_ARGUMENT);

	key = value[i++];
	while (value[i] != '\"')
		key += value[i++];
	key += value[i];

	return key;
}

MyString JsonObject::stringify() const
{
	MyString result = "{\n";	
	size_t size = pairs.count();

	for (size_t i = 0; i < size - 1; i++)
	{
		((result += "  ") += pairs[i].key) += " : ";
		result += pairs[i].value->stringify();
		result += ",\n";
	}

	((result += "  ") += pairs[size - 1].key) += " : ";
	(result += pairs[size - 1].value->stringify()) += "\n}";

	return result;
}

JsonValue* JsonObject::clone() const
{
	return new JsonObject(*this);
}
