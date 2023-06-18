#pragma once
#include <iostream>
#include <fstream>
#include "../ValueTypes/JsonValueFactory.h"
using std::fstream;

class JsonParser
{
	JsonObject root;
	MyString fileName = "json.txt";

	JsonValue*& findByPath(const MyString& path);
public:
	JsonParser(const MyString& fileName);
	void print() const;

	/// <summary>
	/// _string* (everything that begins with _string), _string (only the exact string)
	/// </summary>
	/// <param name="key"></param>
	void search(const MyString& key) const;
	
	void set(const MyString& path, const MyString& string);
	
	/// <summary>
	/// path is for the path in the json (will must save only part or default - whole json)
	/// </summary>
	/// <param name="path"></param>
	/// <param name="filename"></param>
	void save(const MyString& path = "", const MyString& filename = "");
	
	void move(const MyString& pathFrom, const MyString& pathTo);
	void create(const MyString& path, const MyString& string);
	void remove(const MyString& path);
};