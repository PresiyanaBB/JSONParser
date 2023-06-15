#include <iostream>
#include "JsonTreeContainer/JsonParser.h"
#include <fstream>
using std::fstream;

int main()
{
{
	try
	{
		///every file will be placed in folder InputFiles 
		JsonParser json("json.txt");
		//json.print();
		//json.search("\"name\"");
		//json.set("management/directorId","\"a\""); //!!
		//json.set("management/directorId","2"); //!!
		json.save();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

	_CrtDumpMemoryLeaks();
}