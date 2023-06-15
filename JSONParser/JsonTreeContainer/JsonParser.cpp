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
	root.search(key);
	std::cout << "]\n";
}

void JsonParser::set(const MyString& path, const MyString& string)
{
	size_t i = 0;
	JsonValue*& currentValue = findByPath(path);
	JsonValue* replacement = currentValue->setValue(string, i);
	delete currentValue;
	currentValue = replacement;
	replacement = nullptr;

	save();
}

void JsonParser::save(const MyString& path, const MyString& fileName)
{
	//path!!!!
	if (fileName != "")
		this->fileName = "InputFiles/" + fileName;

	MyString file = this->fileName;
	fstream ofs(file.c_str(),std::ios::trunc | std::ios::out);

	if (!ofs.is_open())
		throw std::invalid_argument(FILE_NOT_FOUND);

	ofs << root.stringify();

	ofs.close();
}