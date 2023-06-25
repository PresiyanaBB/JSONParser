#include "JsonParser.h"

JsonParser::JsonParser(const MyString& fileName)
{
	this->fileName = "InputFiles/" + fileName;
	fstream ifs(this->fileName.c_str());
	size_t i = 0;
	MyString currentValue;
	MyString json;

	if (!ifs.is_open())
		throw std::invalid_argument(FILE_NOT_FOUND);

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
		root.parse(json.substr(i, length - i), i);
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

	if (path[0] != '\"' || path[path.length() - 1] != '\"')
		throw std::invalid_argument(PATH_NOT_IN_QUOTATION_MARKS);

	DynamicArray<MyString> paths;
	size_t ind = 0;
	MyString currentKey;
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
	paths.add(currentKey);

	JsonValue*& jv = root.find(paths, ind);
	return jv;
}

DynamicArray<KeyValuePair>& JsonParser::findPair(const MyString& path)
{
	size_t len = path.length() - 1;
	MyString pathWithoutElement;
	size_t indToElement = 0;

	for (int i = len; i >= 0; i--)
		if (path[i] == '/')
		{
			indToElement = i;
			break;
		}

	len -= (len - indToElement);

	for (size_t i = 0; i < len; i++)
		pathWithoutElement += path[i];

	pathWithoutElement += "\"";

	if (pathWithoutElement != "" && pathWithoutElement != "\"")
	{
		JsonValue*& value = findByPath(pathWithoutElement);
		DynamicArray<KeyValuePair>& kvp = dynamic_cast<JsonObject*>(value)->getPairs();
		return kvp;
	}

	else
		return root.getPairs();
}

void JsonParser::search(const MyString& key) const
{
	std::cout << "\n[\n";

	if (startsWith(key, "\"*") && endsWith(key, "*\""))
		root.search(key.substr(2, key.length() - 4), contains);

	else if (endsWith(key, "*\""))
		root.search(key.substr(0, key.length() - 2), startsWith);

	else if (startsWith(key, "\"*"))
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
	fstream ofs(file.c_str(), std::ios::trunc | std::ios::out);

	if (path == "")
		ofs << root.stringify();

	else
	{
		try
		{
			MyString elementKey;

			for (int i = path.length() - 1; i >= 0; i--)
			{
				if (path[i] == '/')
					break;

				elementKey += path[i];
			}

			JsonValue*& elementValue = findByPath(path);
			KeyValuePair pair;
			elementKey.reverse();
			pair.key = "\"" + elementKey;
			pair.value = elementValue;
			DynamicArray<KeyValuePair>& pairs = findPair(path);

			if (pair.key[1] == '\"')
				pair.key = pair.key.substr(1, pair.key.length() - 1);


			ofs << "{\n" + pair.key + " : " + pair.value->stringify() + "\n}";

			pair.value = nullptr;
		}
		catch (const std::exception&)
		{
			ofs << root.stringify();
		}
	}

	ofs.close();
}

void JsonParser::create(const MyString& path, const MyString& string)
{
	/*try
	{
		JsonValue*& isValueUnique = findByPath(path);
		if (isValueUnique != nullptr)
			throw std::invalid_argument(ELEMENT_DUPLICATION);
	}
	catch (const std::exception&)
	{

	}*/

	size_t len = path.length() - 1;
	MyString pathWithoutElement;
	size_t indToElement = 0;

	for (int i = len; i >= 0; i--)
		if (path[i] == '/')
		{
			indToElement = i;
			break;
		}

	len -= (len - indToElement);

	for (size_t i = 0; i < len; i++)
		pathWithoutElement += path[i];

	if (pathWithoutElement[pathWithoutElement.length() - 1] != '\"')	
		pathWithoutElement += "\"";

	JsonValue*& currentValue = findByPath(pathWithoutElement); //path without element
	if (currentValue == nullptr)
		throw std::invalid_argument(INVALID_PATH);

	MyString curVal = currentValue->stringify();
	size_t i = 0;
	JsonValue* replacement = setValue(string.substr(1, string.length() - 2), i);

	MyString result = (" [ " + curVal + " , " + replacement->stringify() + " ] ");

	delete currentValue;
	i = 0;
	currentValue = setValue(result, i);

	delete replacement;
	replacement = nullptr;
}

void JsonParser::remove(const MyString& path)
{
	MyString elementKey;

	for (int i = path.length() - 1; i >= 0; i--)
	{
		if (path[i] == '/')
			break;

		elementKey += path[i];
	}

	JsonValue*& elementValue = findByPath(path);
	KeyValuePair pair;
	elementKey.reverse();
	pair.key = "\"" + elementKey;
	pair.value = elementValue;
	DynamicArray<KeyValuePair>& pairs = findPair(path);

	if (pair.key[1] == '\"')
		pair.key = pair.key.substr(1, pair.key.length() - 1);

	DynamicArray<KeyValuePair> newPairs;

	size_t i;
	for (i = 0; i < pairs.count(); i++)
	{
		if (pair == pairs[i])
			continue;

		newPairs.add(pairs[i]);
	}

	pairs = newPairs;

	delete pairs[pairs.count()].value;
	pairs[pairs.count()].value = nullptr;
	elementValue = nullptr;
	pair.value = nullptr;
}

void JsonParser::move(const MyString& pathFrom, const MyString& pathTo)
{
	MyString elementKey;

	for (int i = pathFrom.length() - 1; i >= 0; i--)
	{
		if (pathFrom[i] == '/')
			break;

		elementKey += pathFrom[i];
	}

	JsonValue*& elementValue = findByPath(pathFrom);
	KeyValuePair pair;
	elementKey.reverse();
	pair.key = "\"" + elementKey;
	pair.value = elementValue;
	DynamicArray<KeyValuePair>& pairs = findPair(pathFrom);

	if (pair.key[1] == '\"')
		pair.key = pair.key.substr(1, pair.key.length() - 1);

	MyString moveValue = "\"" + pair.value->stringify() + "\"";
	MyString path = pathTo.substr(0,pathTo.length() - 1) + "/new\"";

	pair.value = nullptr;
	create(path, moveValue);
	remove(pathFrom);
}

void JsonParser::open(const MyString& filename)
{
	JsonParser json2(filename);
	this->fileName = json2.fileName;
	this->root = json2.root;
}

const MyString JsonParser::getFileName() const
{
	return this->fileName;
}