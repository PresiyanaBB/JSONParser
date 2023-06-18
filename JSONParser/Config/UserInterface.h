#include <iostream>
#include "../Parser/JsonParser.h"
#include <fstream>
#include <stdlib.h>
using std::fstream;
using std::cin;
using std::cout;

bool isOptionValid(MyString option);
bool runUserInterface(JsonParser& json);
void printInstructions();
void run();