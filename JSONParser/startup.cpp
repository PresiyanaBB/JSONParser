#include <iostream>
#include "JsonTreeContainer/JsonParser.h"
#include <fstream>
using std::fstream;

int main()
{
{
	//set parse value add "?
	try
	{
		JsonParser json("json.txt");
		//json.set("management/directorId", " [  \"ddz\"  ,  \"okok\"  ] "); //!!
		//json.set("management/directorId","2"); //!!
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

	_CrtDumpMemoryLeaks();
}