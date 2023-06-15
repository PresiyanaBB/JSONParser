#include <iostream>
#include "JsonTreeContainer/JsonParser.h"
#include <fstream>
using std::fstream;

int main()
{
{
	//set parse value
	//search parse value, add regex
	//save add path

	try
	{
		///every file will be placed in folder InputFiles 
		JsonParser json("json.txt");
		//json.print();
		//json.search("\"name\"");
		//json.search("\"add*\"");
		//json.search("\"*date\"");
		//json.search("\"*am*\"");
		//json.set("management/directorId","\"a\""); //!!
		//json.set("management/directorId","2"); //!!
		//json.save();
		//json.save("management","testPath.txt");
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

	_CrtDumpMemoryLeaks();
}