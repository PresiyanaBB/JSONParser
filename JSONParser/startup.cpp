#include <iostream>
#include "JsonTreeContainer/JsonParser.h"
#include <fstream>
using std::fstream;

int main()
{
{
	try
	{
		//every file will be placed in folder InputFiles 
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
