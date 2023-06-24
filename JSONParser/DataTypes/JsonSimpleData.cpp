#include "../DataTypes/JsonSimpleData.h"

JsonSimpleData::JsonSimpleData(const MyString& value, size_t& i) : JsonValue(ValueTypes::null)
{
	parse(value, i);
}

JsonValue*& JsonSimpleData::find(DynamicArray<MyString> paths, size_t& ind)
{
	JsonValue* jv = nullptr;
	return jv;
}

void JsonSimpleData::parse(const MyString& value, size_t& i)
{
	if ((value.length() >= i + 4) && value.substr(i, 4) == "null")
	{
		this->type = ValueTypes::null;
		this->value = value.substr(i, 4);
		i += 4;
	}

	else if ((value.length() >= i + 4) && value.substr(i, 4) == "true")
	{
		this->type = ValueTypes::boolean;
		this->value = value.substr(i, 4);
		i += 4;
	}

	else if ((value.length() >= i + 5) && value.substr(i, 5) == "false")
	{
		this->type = ValueTypes::boolean;
		this->value = value.substr(i, 5);
		i += 5;
	}

	else if (value[i] == '\"')
	{
		MyString currentValue = "\"";

		while (value[++i] != '\"')
			currentValue += value[i];

		currentValue += '\"';
		this->type = ValueTypes::string;
		this->value = currentValue;
	}

	else if (value[i] >= '0' && value[i] <= '9')
	{
		MyString currentValue;
		while ((value[i] == '.') || (value[i] >= '0' && value[i] <= '9'))
			currentValue += value[i++];

		if (isNumber(currentValue))
		{
			this->type = ValueTypes::number;
			this->value = currentValue;
		}
	}

	else
		throw std::invalid_argument(INVALID_SIMPLE_DATA_ARGUMENT);

}


	MyString JsonSimpleData::stringify() const
	{
		return this->value;
	}

	JsonValue* JsonSimpleData::clone() const
	{
		return new JsonSimpleData(*this);
	}
