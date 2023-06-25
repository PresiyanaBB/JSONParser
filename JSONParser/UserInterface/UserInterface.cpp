#include "UserInterface.h"

bool isOptionValid(MyString option)
{
	return (option == "open" ||
			option == "print" ||
			option == "search" ||
			option == "set" ||
			option == "create" ||
			option == "delete" ||
			option == "move" ||
			option == "save" ||
			option == "saveas" ||
			option == "exit");
}

void printInstructions()
{
	cout
	 << "-----------------------------------------------------------------------------------\n" <<
		"Command list:   |Description                        |Syntax:                       \n" <<
		"-----------------------------------------------------------------------------------\n" <<
		"open            |opens file                         |open <filename>               \n" <<
		"print           |print file on console              |print                         \n" <<
		"search          |search by key                      |search \"key\"                \n" <<
		"set             |set json value on path             |set \"path\" \"json\"         \n" <<
		"create          |creates new object on given path   |create \"path\" \"json\"      \n" <<
		"delete          |deletes object on path             |delete \"path\"               \n" <<
		"move            |moves object to another path       |move \"pathFrom\" \"pathTo\"  \n" <<
		"save            |saves json on path as same file    |save \"path\"                 \n" <<
		"saveas          |saves json on path as new file     |saveas \"path\" <filename>    \n" <<
		"exit            |exit console                       |exit                          \n\n" <<
		"command: ";
}

bool runUserInterface(JsonParser& json)
{
	printInstructions();

	MyString option;
	cin >> option;

	system("cls");
	if (!isOptionValid(option))
	{
		return true;
	}

	if (option == "open")
	{
		MyString filename;
		cin >> filename;
		json.open(filename);
		cout << filename << " opened successfully\n";
	}

	else if (option == "print")
	{
		json.print();
		cout << "\n\n";
	}

	else if (option == "exit")
		exit(0);

	else if (option == "search")
	{
		MyString key;
		cin >> key;
		json.search(key);
		cout << '\n';
	}

	else if (option == "set")
	{
		MyString path, obj;
		cin >> path;
		cin >> obj;
		json.set(path, obj);
		cout << option << " executed successfully.\n";
	}

	else if (option == "create")
	{
		MyString path, obj;
		cin >> path;
		cin >> obj;
		json.create(path, obj);
		cout << option << " executed successfully.\n";
	}

	else if (option == "delete")
	{
		MyString path;
		cin >> path;
		json.remove(path);
		cout << option << " executed successfully.\n";
	}

	else if (option == "move")
	{
		MyString pathFrom, pathTo;
		cin >> pathFrom;
		cin >> pathTo;
		json.move(pathFrom, pathTo);
		cout << option << " executed successfully.\n";
	}

	else if (option == "save")
	{
		MyString path;
		cin >> path;
		json.save(path);
		cout << "file saved successfully\n";
	}

	else if (option == "saveas")
	{
		MyString path, file;
		cin >> path;
		cin >> file;
		json.save(path, file);
		cout << file << " saved successfully\n";
	}

	else
		return true;
}

void run()
{
	MyString filename;
	cout << "Note: first open file\n";
	while (true)
	{
		try
		{
			printInstructions();

			MyString option;
			cin >> option;

			if (option == "exit")
				exit(0);

			if (option == "open")
			{
				cin >> filename;
				JsonParser json(filename);

				system("cls");

				cout << filename << " opened successfully\n";

				while (runUserInterface(json))
					runUserInterface(json);
			}

			else
			{
				system("cls");
				continue;
			}
		}
		catch (const std::exception& ex)
		{
			system("cls");
			cout << ex.what() << "\n";
		}
	}
}