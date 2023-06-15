#include "JsonObject.h"

JsonObject::JsonObject(const MyString& value,size_t& i) : JsonValue(ValueTypes::object)
{
	parse(value,i);
}

JsonObject::JsonObject() : JsonValue(ValueTypes::object) {}

void JsonObject::parse(const MyString& value,size_t& i)
{
	bool hasKey = false;
	KeyValuePair currentPair;

	while(true)
	{
		if (value[i] == ' ' || value[i] == '\n' || value[i] == ',')
		{
			i++;
			continue;
		}
	
		else if (value.length() == i + 1)
			throw std::exception(INVALID_JSON_FILE);

		else if (value[i] == '}')
			break;

		else if (!hasKey)
		{
			currentPair.key = setKey(value,i);
			hasKey = true;
			
			while (value[i++] != ':');
		}

		else
		{
			JsonValue* jv = setValue(value, i);
			currentPair = jv;
			hasKey = false;
			i++;
			pairs.add(currentPair);
			currentPair.free();
			delete jv;
		}
	}
}

void JsonObject::search(const MyString& key) const
{
	size_t count = pairs.count();

	for (size_t i = 0; i < count; i++)
	{
		if (pairs[i].key == key)
			std::cout << pairs[i].value->stringify() << std::endl;

		else
			pairs[i].value->search(key);
	}
}

MyString JsonObject::setKey(const MyString& value,size_t& i)
{
	MyString key;

	if (value[i] != '\"')
		throw std::invalid_argument(INVALID_KEY_ARGUMENT);

	key = value[i];
	while (value[++i] != '\"')
		key += value[i];

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
	result += pairs[size - 1].value->stringify() += "\n}";

	return result;
}

JsonValue* JsonObject::clone() const
{
	return new JsonObject(*this);
}

JsonValue*& JsonObject::find(DynamicArray<MyString> paths, size_t& ind)
{
	size_t count = pairs.count();

	for (size_t i = 0; i < count; i++)
	{
		MyString a = pairs[i].key;
		MyString b = paths[ind];

		if (pairs[i].key == paths[ind])
		{
			ind++;
			if (ind == paths.count())
				return pairs[i].value;

			else
				return pairs[i].value->find(paths,ind);
		}
	}
}