#include <iostream>
#include "JsonTreeContainer/JsonParser.h"
#include <fstream>
using std::fstream;

int main()
{
{
	try
	{
		///every file is in folder InputFiles 
		JsonParser json("json.txt");
		json.print();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

	_CrtDumpMemoryLeaks();
}