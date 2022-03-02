#pragma once
#ifndef Item_h
#define Item_h
#include <cassert>
#include <iostream>
#include <string>
using namespace std;
/*
* This class represents an Item object which is used in the Pizza event simulator 
*/

class Item
{
public:
	Item(int acook_time, string aname); //overloaded constuctor 

	//Accessor methods 
	int getCookTime() const;
	string getName() const;

	//Modifier methods 
	void decrementCookTime();

private: //member variables 
	int cook_time;
	string name;
};

bool operator<(const Item& item1, const Item& item2); //used for sorting of item objects 
#endif 
