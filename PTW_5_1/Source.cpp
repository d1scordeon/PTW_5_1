#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

void WriteToFile(const string &filename)
throw (invalid_argument);

void PrintFileContent(const string &filename)
throw (invalid_argument);

void RewriteToFileIf(const string &source, const string &destination)
throw (invalid_argument);

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	string source;
	string destination;
	char choice;

	do
	{
		cout << "\n\nWhat do you wish to do?\n[1] - Print file's content\n[2] - Write to a file\n[3] - Rewrite to a file if (...)\n\n[0] - Exit the program\n";
		cin >> choice;

		switch (choice)
		{
		case '1':
			cout << "File's name : ";
			cin >> source;

			PrintFileContent(source);

			break;
		case '2':
			cout << "File's name : ";
			cin >> source;
			
			WriteToFile(source);

			break;
		case '3':
			cout << "Source : ";
			cin >> source;

			cout << "Destination : ";
			cin >> destination;

			try
			{
				RewriteToFileIf(source, destination);
			}
			catch (invalid_argument exception)
			{
				cerr << exception.what() << endl;
			}

			break;
		case '0':
			break;
		default:
			cerr << "Invalid option selected.\n\n";

			break;
		}
	} while (choice != '0');

	return 0;
}

void WriteToFile(const string &filename)
throw (invalid_argument)
{	
	fstream write(filename, ios::out | ios::binary | ios::trunc);

	if (!write)
	{
		throw invalid_argument("Could not open \"" + filename + "\"");
	}

	const size_t size = 250;

	char choice;
	string input;

	do
	{
		cin.get();
		cin.sync();

		cout << "Line : ";
		getline(cin, input, '\n');

		for (size_t elem = 0; elem < input.size(); elem++)
		{
			write.write(reinterpret_cast<char *>(&input[elem]), sizeof(input[elem]));
		}
		
		cin.get();
		cin.sync();

		cout << "Continue? (Y/N)\n";
		cin >> choice;

	} while (choice == 'y' || choice == 'Y');
}

void PrintFileContent(const string &filename)
throw (invalid_argument)
{
	fstream read(filename, ios::in | ios::binary | ios::_Nocreate);

	if (!read)
	{
		throw invalid_argument("Could not open \"" + filename + "\"");
	}

	char value;
	
	while (read.read(reinterpret_cast<char *>(&value), sizeof(value)))
	{
		cout << value;
	}
	cout << endl;
}

void RewriteToFileIf(const string &source, const string &destination)
throw (invalid_argument)
{
	fstream read(source, ios::in | ios::binary | ios::_Nocreate);
	fstream write(destination, ios::out | ios::binary | ios::trunc);

	if (!read)
	{
		throw invalid_argument("Could not open \"" + source + "\"");
	}

	if (!write)
	{
		throw invalid_argument("Could not open \"" + destination + "\"");
	}

	char value;

	while (read.read(reinterpret_cast<char *>(&value), sizeof(value)))
	{
		if (value == '³' ||
			value == 'í' ||
			value == 'ô' ||
			value == 'î' ||
			value == 'ð' ||
			value == 'ì' ||
			value == 'à' ||
			value == 'ò' ||
			value == 'è' ||
			value == 'ê')
		{
			write.write(reinterpret_cast<char *>(&value), sizeof(value));
		}
	}
}