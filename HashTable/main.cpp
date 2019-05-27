#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "Hash.h"

using namespace std;

int main()
{
	HashClass testObj;
	string name;
	string drink;

	ifstream myFile("Items.txt");
	if (myFile.is_open())
	{
		//name = key  drink = value (key value pair)
		while (myFile >> name >> drink)
		{
			testObj.AddItems(name, drink);
		}
		myFile.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		system("pause");
		return 0;
	}
	// Testing functions
	testObj.PrintTable();
	testObj.FindValue("James");
	testObj.RemoveValue("dsfafafs");
	testObj.PrintTable();



	system("pause");

	return 0;
}