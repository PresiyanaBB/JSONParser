#include "MyString.h"

bool contains(const MyString& lhs, const MyString& rhs)
{
	size_t iterCount = lhs.length() - rhs.length();
	for (size_t i = 0; i <= iterCount; i++)
		if (lhs.substr(i, rhs.length()) == rhs)
			return true;

	return false;
}

bool startsWith(const MyString& lhs, const MyString& rhs)
{
	if (lhs.length() >= rhs.length())
		return (lhs.substr(0, rhs.length()) == rhs);
	
	return false;
}

bool endsWith(const MyString& lhs, const MyString& rhs)
{
	if (lhs.length() >= rhs.length())
		return (lhs.substr(lhs.length() - rhs.length(), rhs.length()) == rhs);

	return false;
}

MyString::MyString(size_t capacity)
{
	_length = capacity - 1;
	_data = new char[capacity];
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs._length + rhs._length + 1);

	result[0] = '\0';
	strcat(result._data, lhs._data);
	strcat(result._data, rhs._data);

	return result;
}

MyString& MyString::operator+=(const MyString& other)
{
	char* result = new char[(_length += other._length) + 1];
	result[0] = '\0';
	strcat(result, _data);
	strcat(result, other._data);

	delete[] _data;
	_data = result;

	return *this;
}

MyString& MyString::operator+=(const char* other)
{
	char* result = new char[(_length += strlen(other)) + 1];
	result[0] = '\0';
	strcat(result, _data);
	strcat(result, other);

	delete[] _data;
	_data = result;

	return *this;
}

MyString& MyString::operator+=(const char other)
{
	char* result = new char[(_length += 1) + 1];
	result[0] = '\0';
	strcat(result, _data);
	result[_length - 1] = other;
	result[_length] = '\0';

	delete[] _data;
	_data = result;

	return *this;
}

MyString::MyString() : MyString(1)
{
	_data[0] = '\0';
}

MyString::MyString(const char* data) : MyString(strlen(data) + 1)
{
	strcpy(_data, data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyString& MyString::operator=(const char* other)
{
	free();

	_length = strlen(other);
	_data = new char[_length + 1];
	strcpy(_data, other);

	return *this;
}

MyString& MyString::operator=(const char other)
{
	free();
	if (other == '\0')
	{
		_length = 0;
		_data = new char[1];
		_data[0] = other;
	}

	else
	{
		_length = 1;
		_data = new char[_length + 1];
		_data[0] = other;
		_data[1] = '\0';
	}

	return *this;
}

void MyString::free()
{
	delete[] _data;
	_data = nullptr;
}

MyString::~MyString()
{
	free();
}

size_t MyString::length() const
{
	return _length;
}

void MyString::copyFrom(const MyString& other)
{
	_length = other._length;
	_data = new char[_length + 1];
	strcpy(_data, other._data);
}

MyString::MyString(MyString&& other) noexcept
{
	_data = other._data; // to function moveFrom ?
	other._data = nullptr;
	_length = other._length;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		_data = other._data;
		other._data = nullptr;
		_length = other._length;
	}
	return *this;
}

char& MyString::operator[](size_t index) 
{
	return _data[index];
}

char MyString::operator[](size_t index) const
{
	return _data[index];
}

MyString MyString::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > _length)
		throw std::length_error("Error, Substr out of range");


	MyString res(howMany + 1);
	for (int i = 0; i < howMany; i++)
		res._data[i] = _data[begin + i];
	res[howMany] = '\0';
	return res;
}

const char* MyString::c_str() const
{
	return _data;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff; // is.getLine(buff, 1024);

	delete[] str._data;
	str._length = strlen(buff);
	str._data = new char[str._length + 1];
	strcpy(str._data, buff);
	return is;
}


bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}
