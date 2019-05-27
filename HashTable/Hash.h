#include <iostream>
#include <string>
#include <cstdlib>

using namespace std; 

#pragma once


class HashClass{

public:
	// default constructor
	HashClass();
	// memeber functions
	int HashFunc(string key);
	void AddItems(string name, string drink);
	int NumItemsInIndex(int index);
	void PrintTable();
	void PrintIndex(int index);
	void FindValue(string name);
	void RemoveValue(string name);
	//swap function
private:

	static const int tableSize_ = 40;

	// Use this definition to create core of hash table
	struct item {
		string name;
		string drink;
		item* next;
	};
	item* HashTable[tableSize_];



};