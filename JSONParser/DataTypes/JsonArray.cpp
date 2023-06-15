#include "JsonArray.h"

JsonArray::JsonArray() : JsonValue(ValueTypes::array)
{
	size = 0;
	capacity = 8;
	values = new JsonValue * [capacity];
}

JsonArray::JsonArray(const MyString& value,size_t& i) : JsonValue(ValueTypes::array)
{
	size = 0;
	capacity = 8;
	values = new JsonValue * [capacity];

	parse(value,i);
}

void JsonArray::parse(const MyString& value, size_t& i)
{
	while(true)
	{
		if (value[i] == ' ' || value[i] == '\n' || value[i] == ',')
			i++;

		else if (value.length() == i + 1)
			throw std::exception(INVALID_JSON_FILE);

		else if (value[i] == ']')
			break;

		else
		{
			if (size == capacity)
				resize();

			values[size++] = setValue(value, i);
			i++;
		}
	}
}

MyString JsonArray::stringify() const
{
	MyString result = "[\n";
	for (size_t i = 0; i < size - 1; i++)
	{
		result += "  ";
		result += values[i]->stringify();
		result += ",\n";
	}

	((result += " ") += values[size - 1]->stringify()) += "\n]";
	return result;
}

JsonValue* JsonArray::clone()  const
{
	return new JsonArray(*this);
}

void JsonArray::free()
{
	for (size_t i = 0; i < size; i++)
		delete values[i];
	delete[] values;
}

void JsonArray::copyFrom(const JsonArray& other)
{
	values = new JsonValue * [other.capacity];
	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
		values[i] = other.values[i]->clone();
}

void JsonArray::moveFrom(JsonArray&& other)
{
	size = other.size;
	capacity = other.capacity;

	values = other.values;
	other.values = nullptr;

	other.size = other.capacity = 0;
}

void JsonArray::resize()
{
	JsonValue** newCollection = new JsonValue * [capacity *= 2];
	for (size_t i = 0; i < size; i++)
		newCollection[i] = values[i];
	delete[] values;
	values = newCollection;
}

JsonArray::JsonArray(const JsonArray& other)
{
	copyFrom(other);
}

JsonArray::JsonArray(JsonArray&& other)
{
	moveFrom(std::move(other));
}

JsonArray& JsonArray::operator=(const JsonArray& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

JsonArray& JsonArray::operator=(JsonArray&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

JsonArray& JsonArray::operator+=(const JsonArray& other)
{
	JsonValue** result = new JsonValue*[(size + other.size)];
	for (size_t i = 0; i < size; i++)
		result[i] = this->values[i];


	for (size_t i = 0; i < other.size; i++)
		result[size + i] = other.values[i];

	size += other.size;
	delete[] values;
	values = result;

	return *this;
}

JsonArray::~JsonArray()
{
	free();
}

void JsonArray::add(JsonArray value)
{
	if (size == capacity)
		resize();
	
	for (size_t i = 0; i < value.size; i++)
	{
		if (size == capacity)
			resize();

		values[size++] = value.values[i]->clone();
	}
}

void JsonArray::add(JsonValue* value)
{
	if (size == capacity)
		resize();
	
	values[size++] = value->clone();
}

void JsonArray::search(const MyString& key) const
{
	for (size_t i = 0; i < size; i++)
		if (values[i]->getType() == ValueTypes::object)
			values[i]->search(key);
}

void JsonArray::search(const MyString& key, bool (*criteria)(const MyString& lhs, const MyString& rhs)) const
{
	for (size_t i = 0; i < size; i++)
		if (values[i]->getType() == ValueTypes::object)
			values[i]->search(key,criteria);
}

const size_t JsonArray::getSize() const
{
	return size;
}