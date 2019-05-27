#include <iostream>
#include <string>
#include <cstdlib>

#include "Hash.h"

using namespace std;

/* This hash table implementation uses Closed Addressing, it is faster 
   then Open Addresssing(Linear Probing). However if the Load Factor is
   low use Open Addressing.
*/

//======================================================================//
//	Description: Default contructor sets all values in the table to
//				 default values
//
//	Input: None
//	Output: None
//======================================================================//
HashClass::HashClass()
{
	for (int i = 0; i < tableSize_; i++)
	{
		HashTable[i] = new item;
		HashTable[i]->name = "";
		HashTable[i]->drink = "";
		HashTable[i]->next = NULL;
	}
}

//======================================================================//
//	Description: Hashes the key values by adding all the ASCII 
//				 values of every char in the string and modulo size
//				 of the table.
//
//	Input: key - A string value entered by the user
//	Output: index - Where in the table the string will be placed
//======================================================================//
int HashClass::HashFunc(string key)
{
	int hash = 0;
	int index = 0;

	for (int i = 0; i < key.length(); i++)
	{
		hash += (int)key[i]^17;
	}
	index = hash % tableSize_;

	return index;

}

//======================================================================//
//	Description: Adds the item to its proper index, if theres a 
//				 Collision then chain the item to the table.
//
//	Input: name, drink - both values of a Item object
//	Output: None
//======================================================================//
void HashClass::AddItems(string name, string drink)
{
	int index = HashFunc(name);
	int numItems = NumItemsInIndex(index);
	item* iter = HashTable[index];
	
	//if no collision set values OR
	//if repeated key over write values
	if (HashTable[index]->name == "" )
	{
		HashTable[index]->name = name;
		HashTable[index]->drink = drink;
	}
	else
	{
		for (int i = 0; i < numItems ; i++)
		{
			if (iter->name == name)
			{
				iter->name = name;
				iter->drink = drink;
			}
			iter = iter->next;
		}
	}
	//if collision then chain it
	if(numItems >= 1)
	{
		item* ptr = HashTable[index];
		item* newPtr = new item;
		newPtr->name = name;
		newPtr->drink = drink;
		newPtr->next = NULL;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = newPtr;
	}
}


//======================================================================//
//	Description: Takes an index and returns the number of element 
//				 in that index.
//
//	Input: index - index to the value in the the table
//	Output: integer equal to the number of items in the index
//======================================================================//
int HashClass::NumItemsInIndex(int index)
{
	int numItems = 0;
	item *iter = HashTable[index];

	if (iter->name == "")
	{
		return numItems;
	}
	else 
	{
		while (iter != NULL)
		{
			iter = iter->next;
			numItems++;
		}
	}
	
	return numItems;
}

//======================================================================//
//	Description: Will print all the indecies of the table and it 
//				 will also display the number of elements in each 
//				 index.
//
//	Input: None
//	Output: None
//======================================================================//
void HashClass::PrintTable()
{
	int numItems = 0;
	
	for (int i = 0; i < tableSize_; i++)
	{
		if (HashTable[i]->name != "")
		{
			numItems = NumItemsInIndex(i);
			if (numItems == 1)
			{
				cout << "--------Index: " << i << "-------"<< endl;
				cout << "--------Contains--------" << endl;
				cout << "Name: " << HashTable[i]->name << endl;
				cout << "Drink: " << HashTable[i]->drink << endl << endl;
			}
			else
			{
				PrintIndex(i);
			}
			
		}
		else 
		{
			cout << "--------Index: " << i << "-------" << endl;
			cout << "--------Is Empty--------" << endl << endl;
		}
		
	}
}

//======================================================================//
//	Description: Will print all the items in an index where more than one
//				 item is being stored.
//
//	Input: index - the index with more then one item in it.
//	Output: None
//======================================================================//

void HashClass::PrintIndex(int index)
{
	int numItems = NumItemsInIndex(index);
	item* iter = HashTable[index];
	cout << "--------Index: " << index << "-------" << endl;
	cout << "--------Contains--------" << endl;
	for (int i = 0; i < numItems; i++)
	{
		cout << "  *Item Number : " << i+1 << "*"<< endl ;
		cout << "Name: " << iter->name << endl;
		cout << "Drink: " << iter->drink << endl << endl;
		
		iter = iter->next;
	}



}


//======================================================================//
//	Description: Will find the value for a given key
//
//	Input: name - the key we wil be looking for
//	Output: returns an index to the 
//======================================================================//
void HashClass::FindValue(string name)
{
	int index = HashFunc(name);
	bool foundName = false;
	string value;

	item* iter = HashTable[index];
	item* retPtr = NULL;
	while (iter != NULL)
	{
		if (iter->name == name)
		{
			foundName = true;
			value = iter->drink;
			retPtr = iter;
		}
		iter = iter->next;
	}
	if (foundName)
	{
		cout << name << "'s favorite drink is " << value << endl;
	}
	else
	{
		cout << name << " is not is the Hash Table" << endl;
	}
}

//======================================================================//
//	Description: Will remove a key and its values if it exist
//
//	Input: name - the key we wil be looking to remove
//	Output: None
//======================================================================//
void HashClass::RemoveValue(string name)
{
	int index = HashFunc(name);

	item* Ptr = HashTable[index];
	item* delPtr = NULL;
	item* tailPtr = NULL;

	//index computed is empty, so user not in the list
	if (HashTable[index]->name == "")
	{
		cout << name << " was not found in the Hash Table." << endl;
	}
	//only one item in list & its the first one
	//reset values( in this case we dont need to deallocate.
	else if (Ptr->next == NULL && Ptr->name == name)
	{
		Ptr->name = "";
		Ptr->drink = "";
		cout << name << " was the only value and was removed!" << endl;
	}
	//more than one item in the list and the first one is a match
	else if (Ptr->next != NULL && Ptr->name == name)
	{
		tailPtr = Ptr;
		Ptr = Ptr->next;
		tailPtr->name = Ptr->name;
		tailPtr->drink = Ptr->drink;
		tailPtr->next = Ptr->next;

		delete Ptr;
		cout << name << " was the first one in the list and was removed" << endl;
	}
	// more than one item is in the lsit & it is not the first one
	else 
	{
		bool inList = false;

		while (Ptr != NULL)
		{
			if(Ptr->name == name)
				{
					inList = true;
					break;
				}
			tailPtr = Ptr;
			Ptr = Ptr->next;
		}
		if (inList)
		{
			tailPtr->next = Ptr->next;
			delete Ptr;
			cout << name << " was removed" << endl;
		}
		else
		{
			cout << name << " is not in the Hash Table " << endl;
		}
		
	}
	
}