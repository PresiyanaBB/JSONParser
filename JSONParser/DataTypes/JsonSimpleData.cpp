#include "../DataTypes/JsonSimpleData.h"

JsonSimpleData::JsonSimpleData(const MyString& value) : JsonValue(ValueTypes::null)
{
	parse(value);
}

void JsonSimpleData::parse(const MyString& value)
{
	if (value == "null")
	{
		type = ValueTypes::null;
		this->value = value;
	}

	else if (value == "true" || value == "false")
	{
		type = ValueTypes::boolean;
		this->value = value;
	}

	else if (value[0] == '\"' && value[value.length() - 1] == '\"')
	{
		type = ValueTypes::string;
		this->value = value;
	}

	else if (isNumber(value))
	{
		type = ValueTypes::number;
		this->value = value;
	}

	else
	{
		throw std::invalid_argument(INVALID_SIMPLE_DATA_ARGUMENT);
	}
}


MyString JsonSimpleData::stringify() const
{
	return this->value;
}

JsonValue* JsonSimpleData::clone() const
{
	return new JsonSimpleData(*this);
}
