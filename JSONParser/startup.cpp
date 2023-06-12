#include <iostream>
#include "JsonTreeContainer/JsonParser.h"
#include <fstream>
using std::fstream;

int main()
{
	fstream ifs("InputFiles/json.txt");
	try
	{
		JsonParser json(ifs);
		json.print();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
	
	ifs.close();
}