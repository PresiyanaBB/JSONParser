#pragma once
#include "String/MyString.h"

enum class ValueTypes
{
	string,
	number,
	boolean,
	null,
	array,
	object
};

const char DECIMAL_SEPARATOR = '.';

//error msg list
const char* const INVALID_SIMPLE_DATA_ARGUMENT = "Json is invalid! There isn't such simple data type (string, number, bool, null).";
const char* const INVALID_KEY_ARGUMENT = "Json is invalid! Keys must be in (\"...\") format.";
const char* const INVALID_JSON_SYNTAX = "Json must start with { in order to be object";
const char* const INVALID_JSON_FILE = "Json file is invalid!";
const char* const FILE_NOT_FOUND = "Json file is not found or can't be used!";
const char* const INVALID_PATH = "The given path is invalid";
const char* const ELEMENT_DUPLICATION = "There is such element on the given position";

namespace
{
	bool isNumber(MyString value)
	{
		bool isDecimalPointFound = false;
		size_t len = value.length();

		if (value[0] >= '0' && value[0] <= '9')
		{
			for (size_t i = 1; i < len; i++)
			{
				if (value[i] == ' ' || value[i] == '\n')
					continue;

				if (value[i] == DECIMAL_SEPARATOR)
				{
					if (isDecimalPointFound)
						return false;

					isDecimalPointFound = true;
				}

				else if (value[i] < '0' || value[i] > '9')
					return false;
			}

			return true;
		}

		return false;
	}
}
