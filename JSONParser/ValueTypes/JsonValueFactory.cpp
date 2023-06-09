#include "JsonValueFactory.h"

JsonValue* setValue(const MyString& value, size_t& i)
{
	while (value[i] == ' ' || value[i] == '\n' || value[i] == ',')
		i++;

	if (value[i] == '{')
		return new JsonObject(value, ++i);

	else if (value[i] == '[')
		return new JsonArray(value, ++i);

	else
		return new JsonSimpleData(value, i);
}
