#pragma once
#include <iostream>
#include <fstream>
#include "../DataTypes/JsonObject.h"
using std::fstream;

class JsonParser
{
	friend class JsonParser;
	JsonObject root;
	MyString fileName = "json.txt";

	//JsonObject findByPath(MyString path);

public:
	JsonParser(const MyString& fileName);
	void print() const;

	/// <summary>
	/// path is for the path in the json (will must save only part or default - whole json)
	/// </summary>
	void save(const MyString& path, const MyString& filename = "json.txt") const;
	
	void move(const MyString& pathFrom, const MyString& pathTo) const;
	void search(const MyString& key) const; //_string* (everything that begins with _string), _string (only the exact string)
	void set(const MyString& path, const MyString& string) const;
	void create(const MyString& path, const MyString& string) const;
	void remove(const MyString& path) const;
};