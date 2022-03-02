// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include "Order.h"
#include "Item.h"
using namespace std;
/*
* Main program to run Pizza Event Simulation 
*/


typedef list<Order> OrderList;
typedef list<Item> KitchenList;

//Needed for CanFillOrder()
typedef list <KitchenList::const_iterator> OrderFillList;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove);

void printOrders(list<Order> orders) { //function prints list of Orders with the correct formatting 
    list<Order>::const_iterator itr;
    for (itr = orders.begin(); itr != orders.end(); itr++) {
        cout << "  #" << (*itr).getId() << " (" << (*itr).getExpTime() << " minute(s) left):" << endl;

        list<string>::const_iterator itr2;
        list<string> order_items = (*itr).getItems();
        for (itr2 = order_items.begin(); itr2 != order_items.end(); itr2++) {
            cout << "    " << (*itr2) << endl;
        }
    }
}

int main() {
  OrderList orders;
  KitchenList food_cooking;
  KitchenList food_completed;
  OrderFillList itemsToRemove; //filled whenever CanFillOrder is called, empty if order can't be filled

  string token;
  while (cin >> token) {
    if (token == "add_order") {
        int id, promised_time, n_items = 0;
        string next_item;
        list <string> order_items;

        cin >> id >> promised_time >> n_items;
        assert(n_items > 0);
        Order order(id, promised_time, n_items); //creates new Order from input values

        for (int i = 0; i < n_items; i++) { //loops through each item for Order and adds to list of strings
            cin >> next_item;
            order_items.push_back(next_item);
        }
        order.setItems(order_items); //sets list of Order items for given order to inputted items
        orders.push_back(order); //adds order to list of orders
        orders.sort(); //sorts list of Orders to maintain correct order after insert
        cout << "Received new order #" << order.getId() << " due in " << order.getExpTime() << " minute(s):" << endl;
        list<string>::const_iterator itr;
        list<string> order_its = order.getItems();
        for (itr = order_its.begin(); itr != order_its.end(); itr++) { //loops through and prints items in Order
            cout << "  " << (*itr) << endl;
        }

    } else if (token == "add_item") {
        int cook_time = -1;
        string name;
        cin >> cook_time >> name;
        assert(cook_time >= 0);
        Item item(cook_time, name); //creates new Item object with given input values
        food_cooking.push_back(item); //adds Item to food cooking list 
        food_cooking.sort(); //sorts to maintain order 
        cout << "Cooking new " << item.getName() << " with " << item.getCookTime() << " minute(s) left." << endl;

    } else if (token == "print_orders_by_time") {
        orders.sort(); //sorts by time 
        cout << "Printing " << orders.size() << " order(s) by promised time remaining:" << endl;
        printOrders(orders); //prints Orders with correct formatting 

    } else if (token == "print_orders_by_id") {
        orders.sort(sortById); //sorts by ID only 
        cout << "Printing " << orders.size() << " order(s) by ID:" << endl;
        printOrders(orders); //prints Orders with correct formatting 

    } else if (token == "print_kitchen_is_cooking") {
        food_cooking.sort(); //sorts Items according to operator< function
        cout << "Printing " << food_cooking.size() << " items being cooked:" << endl;
        list<Item>::const_iterator itr;
        for (itr = food_cooking.begin(); itr != food_cooking.end(); itr++) { //loops through and prints each Item cooking
            cout << "  " << (*itr).getName() << " (" << (*itr).getCookTime() << " minute(s) left)" << endl;
        }

    } else if (token == "print_kitchen_has_completed") {
        cout << "Printing " << food_completed.size() << " completely cooked items:" << endl;
        list<Item>::const_iterator itr;
        for (itr = food_completed.begin(); itr != food_completed.end(); itr++) { //loops through and prints all cooked Items
            cout << "  " << (*itr).getName() << endl;
        }

    } else if (token == "run_for_time") { //run for time simulation 
        int run_time = 0;
        cin >> run_time;
        assert(run_time >= 0);
        //sorts lists to ensure smallest times are first in list
        food_cooking.sort();
        orders.sort();
        cout << "===Starting run of " << run_time << " minute(s)===" << endl;

        while ((run_time) >= 0) { //runs for run_time number of minutes 
            KitchenList::iterator itr; //non const iterator to allow changes to be made to Item objects
            itr = food_cooking.begin();
            while (itr != food_cooking.end()) { //loops through all Items in cooking list
                if (run_time != 0) {
                    (*itr).decrementCookTime(); //decrements each itmes cook time as long as run time is not 0
                }

                if (((*itr).getCookTime()) <= 0) { //if cook time is done (<= 0)
                    //Item is added to completed list and removed from cooking list
                    food_completed.push_back((*itr));
                    cout << "Finished cooking " << (*itr).getName() << endl;
                    itr = food_cooking.erase(itr);
                }

                else { //increments iterator otherwise 
                    itr++;
                }
            } 

            list<Order>::iterator itr2;
            itr2 = orders.begin();
            while (itr2 != orders.end()) { //loops through all orders 
                if (run_time != 0) { //decrements expirey time as long as run time is not 0
                    (*itr2).decrementExpTime();
                }
                if (CanFillOrder((*itr2), food_completed, itemsToRemove)) { //checks if Order can be filled 
                    //calling canFillOrder fills itemsToRemove list with iterator values for food_completed list
                    //if so order is removed from list of orders
                    cout << "Filled order #" << (*itr2).getId() << endl;
                    itr2 = orders.erase(itr2);
                    list<KitchenList::const_iterator>::const_iterator itr3;
                    //all items in order are removed from completed list 
                    for (KitchenList::const_iterator ct : itemsToRemove) { //loops through each iterator in itemsToRemove 
                        cout << "Removed a " << (*ct).getName() << " from completed items." << endl;
                        ct = food_completed.erase(ct); //erases each value in food completed for every iterator index
                    }
                }
                else if (((*itr2).getExpTime()) <= 0) { //if order can't be filled checks if order is expired 
                    //if so order is erased from list of orders 
                    cout << "Order # " << (*itr2).getId() << " expired." << endl;
                    itr2 = orders.erase(itr2);
                }
                else { //otherwise increments iterator and checks next order
                    itr2++;
                }
            }
            run_time--; //decrements run time to satsify while loop
        }
        cout << "===Run for specified time is complete===" << endl;
    }
    else if (token == "run_until_next") { //run until event occurs simulation 
        cout << "Running until next event." << endl;

        int time_passed = 0;
        bool event_occured = false; //bool values to keep track if event has occured 
        bool zero_check = false; //bool value to track if a value is equal to 0
        //sorts to maintain correct order, with smallest time values first 
        food_cooking.sort();
        orders.sort();

        while (event_occured == false) { //loops until event occurs 
            if ((food_cooking.size() == 0) && (orders.size() == 0)) { //if no events are left to be checked 
                //ends simulation 
                break;
            }

            KitchenList::iterator itr;
            itr = food_cooking.begin();
            while (itr != food_cooking.end()) { //loops through all Items and checks for first event
                if ((*itr).getCookTime() == 0) { //checks for zero case
                    zero_check = true;
                }
                if (zero_check == false) { //if cook time is 0 time should not be decremented 
                    //decrements all Items cook time even if event has occurred 
                    (*itr).decrementCookTime();
                }
                if (event_occured == false) { //only checks event case if no event has occured 
                    if (((*itr).getCookTime()) <= 0) { //if Item is done cooking
                        //adds Item to completed list and removed from cooking list
                        food_completed.push_back((*itr));
                        cout << "Finished cooking " << (*itr).getName() << endl;
                        event_occured = true; //event has occurred sets bool value to true 
                        itr = food_cooking.erase(itr);
                    }
                }
                else { //otherwise increments iterator and checks next item
                    itr++;
                }
            }

            list<Order>::iterator itr2;
            itr2 = orders.begin();
            while (itr2 != orders.end()) { //loops through all Orders 
                if ((*itr2).getExpTime() == 0) { //checks zero case
                    zero_check = true;
                }
                if (zero_check == false) { //if zero case is true does not decrement exp time
                    //decrements all orders exp time regardless if event has occurred 
                    (*itr2).decrementExpTime();
                }
                if (event_occured == false) { //only checks Order events if event has not occurred 
                    if (CanFillOrder((*itr2), food_completed, itemsToRemove)) { //checks second event, if order can be filled
                        //if so order is removed from list of orders and all itmes in order are removed from completed list
                        event_occured = true; //event has occurred so bool value is set to true 
                        cout << "Filled order #" << (*itr2).getId() << endl;
                        itr2 = orders.erase(itr2);
                        list<KitchenList::const_iterator>::const_iterator itr3;
                        for (KitchenList::const_iterator ct : itemsToRemove) { //loops through and removes all items from completed list
                            cout << "Removed a " << (*ct).getName() << " from completed items." << endl;
                            ct = food_completed.erase(ct); //removes each item in order from completed list 
                        }
                    }
                    else if (((*itr2).getExpTime()) <= 0) { //if order cannot be filled checks if order is expired, third event 
                        //if so order is removed from list of orders 
                        cout << "Order # " << (*itr2).getId() << " expired." << endl;
                        event_occured = true; //event has occurred so bool value is sent to true
                        itr2 = orders.erase(itr2);
                    }
                    else { //otherwise increments iterator 
                        itr2++;
                    }
                }
                else { //otherwise increments iterator 
                    itr2++;
                }
            }
            time_passed++; //increments time passed to simulate time advancing 
            if ((event_occured == true) && (zero_check == false)) { //checks if event has occurred 
                cout << time_passed << " minute(s) have passed." << endl;
            }
            else if ((event_occured == true) && (zero_check == true)) { //checks zero case
                cout << 0 << " minute(s) have passed." << endl;
            }
        }  
        
        if(event_occured == false) { //if no event occurred 
            cout << "No events waiting to process." << endl; 
        }
    }
  }
  return 0;
}


bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  list <string> order_items = order.getItems();
  order_items.sort();

  list<string>::const_iterator item_it;
  string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}

