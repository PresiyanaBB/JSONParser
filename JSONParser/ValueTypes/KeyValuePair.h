#pragma once
#include "JsonValue.h"

class KeyValuePair
{
public:
	MyString key;
	JsonValue* value = nullptr;

	void free();
	void copyFrom(const KeyValuePair& other);
	void moveFrom(KeyValuePair&& other);

public:
	KeyValuePair() = default;
	KeyValuePair(const KeyValuePair& other);
	KeyValuePair(KeyValuePair&& other);

	KeyValuePair& operator=(const KeyValuePair& other);
	KeyValuePair& operator=(KeyValuePair&& other);
	KeyValuePair& operator=(JsonValue* other);

	~KeyValuePair();
};

bool operator==(const KeyValuePair& lhs, const KeyValuePair& rhs);
bool operator!=(const KeyValuePair& lhs, const KeyValuePair& rhs);