#include <iostream>
#include "Parser/JsonParser.h"
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
		//json.create("management/directorId/create()", "\"createTestValue\"");
		//json.create("management/directorId/create()", " { \"createpair\" : \"createt2\" } ");
		//json.remove("management/directorId");
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}

	_CrtDumpMemoryLeaks();
}