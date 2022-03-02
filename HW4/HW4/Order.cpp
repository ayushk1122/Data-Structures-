#include <cassert>
#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "Order.h"
//Implementation of Order class

Order::Order(int aid, int aexp_time, int aitem_count) {
	id = aid;
	exp_time = aexp_time;
	item_count = aitem_count;
}

void Order::setItems(list<string> orderTimes) { //takes a list of strings and sets member variable equal to input list
	list<string>::const_iterator itr;
	for (itr = orderTimes.begin(); itr != orderTimes.end(); itr++) {
		order_items.push_back(*itr);
	}
}

bool operator<(const Order& order1, const Order& order2) {
	//uses ID as tie breaker for orders with same expirey time 
	if (order1.getExpTime() == order2.getExpTime()) {
		return (order1.getId() < order1.getId());
	}
	else {
		return (order1.getExpTime() < order2.getExpTime());
	}
}

bool sortById(const Order& order1, const Order& order2) { //sorts by ID only 
	return (order1.getId() < order2.getId());
}

void Order::decrementExpTime() { //used to decrement time in run time simulations 
	//ensures exp time does not become negative 
	if (exp_time != 0) {
		exp_time--;
	}
	else {
		exp_time = 0;
	}
}