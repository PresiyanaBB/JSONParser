#include "KeyValuePair.h"

void KeyValuePair::free()
{
	if (value)
	{
		delete value; 
		value = nullptr;
	}
}

KeyValuePair& KeyValuePair::operator=(JsonValue* other)
{
	if (value != other)
	{
		value = other->clone();
		other = nullptr;
	}
	return *this;
}

void KeyValuePair::copyFrom(const KeyValuePair& other)
{
	value = other.value->clone();
	key = other.key;
}

void KeyValuePair::moveFrom(KeyValuePair&& other)
{
	value = other.value->clone();
	key = other.key;

	other.value = nullptr;
	other.key = "";
}

KeyValuePair::KeyValuePair(const KeyValuePair& other)
{
	copyFrom(other);
}

KeyValuePair::KeyValuePair(KeyValuePair&& other)
{
	moveFrom(std::move(other));
}

KeyValuePair& KeyValuePair::operator=(const KeyValuePair& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
KeyValuePair& KeyValuePair::operator=(KeyValuePair&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

KeyValuePair::~KeyValuePair()
{
	free();
}

bool operator==(const KeyValuePair& lhs, const KeyValuePair& rhs)
{
	return (lhs.key == rhs.key) && (lhs.value->stringify() == rhs.value->stringify());
}

bool operator!=(const KeyValuePair& lhs, const KeyValuePair& rhs)
{
	return !(lhs == rhs);
}