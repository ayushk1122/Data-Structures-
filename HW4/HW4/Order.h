#pragma once
#ifndef Order_h
#define Order_h
#include <cassert>
#include <iostream>
#include <string>
#include <list>
using namespace std;
/*
* This class represents a Order object used in the Pizza Event simulator 
*/
class Order
{
public:
	Order(int aid, int aexp_time, int aitem_count); //overloaded constructor 
	
	//accessor methods 
	int getId() const { return id; }
	int getExpTime() const { return exp_time; }
	int getItemCount() const { return item_count; }
	list<string> getItems() const { return order_items; }

	//modifier methods 
	void setItems(list<string> orderItems);
	void decrementExpTime();

private: //member variables 
	int id;
	int exp_time;
	int item_count;
	list<string> order_items; //represents items needed to complete order
};

bool operator<(const Order& order1, const Order& order2); //used for sorting of orders
bool sortById(const Order& order1, const Order& order2); //used for sorting of orders by only ID
#endif
