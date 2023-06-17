#include "JsonParser.h"

JsonParser::JsonParser(const MyString& fileName)
{
	this->fileName = "InputFiles/" + fileName;
	fstream ifs(this->fileName.c_str());
	size_t i = 0;
	MyString currentValue;
	MyString json;

	while (!ifs.eof())
		json += ifs.get();

	size_t length = json.length();

	for (i = 0; i < length; i++)
	{
		if (json[i] == ' ' || json[i] == '\n')
			continue;

		if (json[i] == '{')
		{
			i++;
			break;
		}

		throw std::invalid_argument(INVALID_JSON_SYNTAX);
	}

	try
	{
		root.parse(json.substr(i, length - i),i);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
	
	ifs.close();
}

void JsonParser::print() const
{
	std::cout << root.stringify();
}

JsonValue*& JsonParser::findByPath(const MyString& path)
{
	DynamicArray<MyString> paths;
	size_t ind = 0;
	MyString currentKey = "\"";
	size_t pathlen = path.length();

	for (size_t i = 0; i < pathlen; i++)
	{
		if (path[i] == '/')
		{
			currentKey += "\"";
			paths.add(currentKey);
			currentKey = "\"";
		}

		else
			currentKey += path[i];
	}

	currentKey += "\"";
	paths.add(currentKey);

	return root.find(paths, ind);
}

void JsonParser::search(const MyString& key) const
{
	std::cout << "\n[\n";
	
	if (startsWith(key, "\"*") && endsWith(key, "*\""))
		root.search(key.substr(2, key.length() - 4), contains);

	else if (endsWith(key,"*\""))
		root.search(key.substr(0,key.length() - 2), startsWith);
	
	else if (startsWith(key,"\"*"))
		root.search(key.substr(2, key.length() - 2), endsWith);

	else
		root.search(key);

	std::cout << "]\n";
}

void JsonParser::set(const MyString& path, const MyString& string)
{
	size_t i = 0;
	JsonValue*& currentValue = findByPath(path);

	if (!currentValue)
		throw std::invalid_argument(INVALID_PATH);

	JsonValue* replacement = setValue(string, i);
	delete currentValue;
	currentValue = replacement;
	replacement = nullptr;

	save();
}

void JsonParser::save(const MyString& path, const MyString& fileName)
{
	if (fileName != "")
		this->fileName = "InputFiles/" + fileName;

	MyString file = this->fileName;
	fstream ofs(file.c_str(),std::ios::trunc | std::ios::out);

	if (!ofs.is_open())
		throw std::invalid_argument(FILE_NOT_FOUND);

	if (path == "")
		ofs << root.stringify();
	
	else
		ofs << this->findByPath(path)->stringify();

	ofs.close();
}

void JsonParser::create(const MyString& path, const MyString& string)
{
	try
	{
		JsonValue*& isValueUnique = findByPath(path);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument(ELEMENT_DUPLICATION);
	}
		
	size_t len = path.length() - 1;
	MyString pathWithoutElement;
	size_t indToElement = 0;

	for (size_t i = len; i >= 0; i--)
		if (path[i] == '/')
		{
			indToElement = i;
			break;
		}

	len -= (len - indToElement);

	for (size_t i = 0; i < len; i++)
		pathWithoutElement += path[i];

	JsonValue*& currentValue = findByPath(pathWithoutElement); //path without element
	if (currentValue == nullptr)
		throw std::invalid_argument(INVALID_PATH);

	MyString curVal = currentValue->stringify();
	size_t i = 0;
	JsonValue* replacement = setValue(string, i);

	MyString result = (" [ " + curVal + " , " + replacement->stringify() + " ] ");
	delete currentValue;

	i = 0;
	currentValue = setValue(result,i);
	replacement = nullptr;

	save();
}