#include <cassert>
#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "Item.h"
//Implementation of Item class 

Item::Item(int acook_time, string aname) {
	cook_time = acook_time;
	name = aname;
}

int Item::getCookTime() const {
	return cook_time;
}

string Item::getName() const {
	return name;
}

bool operator<(const Item& item1, const Item& item2) { //uses Name of item as tiebreaker for sorting
	//sorts by cook time first then name 
	if (item1.getCookTime() == item2.getCookTime()) {
		return (item1.getName() < item2.getName());
	}
	else {
		return (item1.getCookTime() < item2.getCookTime());
	}
}

void Item::decrementCookTime() { //decrements cook time for run time simulations 
	//ensures cook time does not become negative
	if (cook_time != 0) {
		cook_time--;
	}
	else {
		cook_time = 0;
	}
}