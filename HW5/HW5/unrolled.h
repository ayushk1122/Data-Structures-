#pragma once
#ifndef unrolled_h
#define unrolled_h

#include <cstddef>
#include <cassert>
#include <iostream>

using namespace std;

const int NUM_ELEMENTS_PER_NODE = 6;


template <class T> 
class Node { //Class representing a singular Node, used to make up unrolled link list
public:
	Node() { //default constructor 
		next_ = NULL;
		prev_ = NULL;
		num_elements = 0;
	}
	Node(const T& v) { //overloaded constructor 
		num_elements = 1;
		value[0] = v; //sets first value to inputted value
		next_ = NULL;
		prev_ = NULL;
	}

	void editValue(const T nvalues[]) { //repalces old values with new values
		for (unsigned int i = 0; i < NUM_ELEMENTS_PER_NODE; i++) {
			value[i] = nvalues[i];
		}
	}

	void insertBack(const T& val) { //inserts input value at the back of node values
		value[num_elements] = val;
		num_elements++; //updates number of elements in node
	}

	void insertFront(const T& val) { //inserts input value at front of node values
		T tempArr[NUM_ELEMENTS_PER_NODE]{}; //temp array to store values
		tempArr[0] = val;
		unsigned int tempArrIndex = 1;
		for (unsigned int i = 0; i < NUM_ELEMENTS_PER_NODE; i++) {
			if (tempArrIndex < NUM_ELEMENTS_PER_NODE) {
				tempArr[tempArrIndex] = value[i];
			}
			tempArrIndex++;
		}
		editValue(tempArr); //replaces values with new values 
		num_elements++;
	}

	void eraseValue(unsigned int index) { //removes value at input index 
		T tempArr[NUM_ELEMENTS_PER_NODE]{};
		unsigned int tempArrIndex = 0;

		//loops through both halfs of array and removes value at given index
		for (unsigned int i = 0; i < index; i++) {
			tempArr[i] = value[i];
		}

		tempArrIndex = index;

		//skips index to essentially remove it
		for (unsigned int i = index+1; i < num_elements; i++) {
			tempArr[tempArrIndex] = value[i];
			tempArrIndex++;
		}

		num_elements--;
		editValue(tempArr); //replaces values with new values 
		
	}

	void insertValue(unsigned int index, const T& insertVal) { //inserts value at given index
		T tempArray[NUM_ELEMENTS_PER_NODE]{};
		//loops through first half until given index
		for (unsigned int i = 0; i < index; i++) {
			tempArray[i] = value[i];
		}

		//sets value at given index
		tempArray[index] = insertVal;
		unsigned int tempArrayIndex = index + 1;

		//loops through rest of values and copies over 
		for (unsigned int i = index; i < num_elements; i++) {
			if (tempArrayIndex < NUM_ELEMENTS_PER_NODE) {
				tempArray[tempArrayIndex] = value[i];
				tempArrayIndex++;
			}
		}
		num_elements++;
		editValue(tempArray); //replaces values with new values 
	}

	void editNumElem(unsigned int newNum) { //changes number of elements in node
		num_elements = newNum;
	}

	T value[NUM_ELEMENTS_PER_NODE]{}; //array of values for each node
	//pointers to next and previous Nodes
	Node<T>* next_;
	Node<T>* prev_;
	unsigned int num_elements; //number of elements in value array for node
};

template <class T> class unrolled;

template <class T>
class list_iterator { //Class representing a list iterator for an Unrolled Link List 
public:
	list_iterator(Node<T>* p){ //overloaded constructor using Node pointer
		ptr_ = p;
		offset = 0;
	}

	list_iterator(Node<T>* p, unsigned int index) { //overloaded constructor with index for offset
		ptr_ = p;
		offset = index;
	}

	T& operator*() { return (*ptr_).value[offset]; } //returns value array whenever * is used before iterator 

	list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
		if (ptr_ == NULL) { //null pointer case 
			ptr_ = NULL;
		}
		else if (offset < (*ptr_).num_elements - 1) { //checks if offset is not at last element 
			offset++;
		}
		else { //if offset at end of value array goes to next node 
			ptr_ = ptr_->next_;
			offset = 0;
		}
		return *this; //returns pointer to new value 
	}
	list_iterator<T> operator++(int) { // post-increment, e.g., iter++
		if (ptr_ == NULL) { //null pointer case
			ptr_ = NULL;
			list_iterator<T> temp(*this); //returns pointer to new value
			return temp;
		}
		else if (offset < (*ptr_).num_elements - 1) { //checks if offset is last value 
			offset++;
		}
		else { //if offset is at last value in value array goes to next node
			list_iterator<T> temp(*this);
			ptr_ = ptr_->next_;
			offset = 0;
			return temp;
		}
		list_iterator<T> temp(*this); //in case no conditional is met 
		return temp;
	}

	list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
		if (offset > 0) { //checks offset is not at beginning of value array
			offset--;
		}
		else { //if at beginning goes to previous node 
			ptr_ = ptr_->prev_;
			offset = 0;
		}
		return *this;
	}
	list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
		if (offset > 0) {
			offset--;
		}
		else {
			list_iterator<T> temp(*this);
			ptr_ = ptr_->prev_;
			offset = 0;
			return temp;
		}
	}

	friend class unrolled<T>; 

	bool operator==(const list_iterator<T>& r) const {
		return (ptr_ == r.ptr_);
	}
	bool operator!=(const list_iterator<T>& r) const {
		return (ptr_ != r.ptr_);
	}

	Node<T>* getPtr() { //accessor funciton 
		return ptr_;
	}

	void incrementOffset() { //modifier functions 
		offset++;
	}

	unsigned int getOffset() {
		return offset;
	}
private:
	// REPRESENTATION
	Node<T>* ptr_; //Node pointer for which iterator is corresponding to
	unsigned int offset; //offset to find which index in value array iterator is at 
};

template <class T>
class UnrolledLL { //class representing an Unrolled Link List 
public:
	UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {} //default constructor 
	UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); } //copy constructor 
	UnrolledLL& operator= (const UnrolledLL<T>&old); //assignment operator 
	~UnrolledLL() { destroy_list(); } //destructor 

	typedef list_iterator<T> iterator;

	//accessor methods 
	unsigned int size() const { return size_; }
	bool empty() const { return head_ == NULL; }
	void clear() { destroy_list(); }

	const T& front() const { return (*head_).value[0]; }
	T& front() { return (*head_).value[0]; }
	const T& back() const { return (*tail_).value[(*tail_).num_elements - 1]; }
	T& back() { return (*tail_).value[(*tail_).num_elements - 1]; }

	//modifier functions 
	void push_front(const T& v);
	void pop_front();
	void push_back(const T& v);
	void pop_back();
	ostream& print(ostream& out);

	iterator erase(iterator itr);
	iterator insert(iterator itr, const T& v);
	iterator begin() { return iterator(head_); }
	iterator end() { return iterator(NULL); }

private:
	// private helper functions
	void copy_list(const UnrolledLL<T>& old); //private function to copy List
	void destroy_list(); //private destructor 

	//REPRESENTATION
	Node<T>* head_; //Node pointer pointing to first Node in list
	Node<T>* tail_; //Node pointer pointing to last node in list 
	unsigned int size_; //size of Unrolled list (includes each value in value array)

};

template <class T>
//This function is used for the copy constructor and assignment operator, 
//takes a Unrolled list as input and creates an exact copy 
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
	size_ = old.size_;
	// Handle the special case of an empty list.
	if (size_ == 0) {
		head_ = tail_ = 0;
		return;
	}
	// Create a new head node.
	head_ = new Node<T>();
	Node<T>* oldHeadP = old.head_;
	//Assigns old values to new List 
	(*head_).editValue((*oldHeadP).value);
	(*head_).editNumElem((*oldHeadP).num_elements);
	
	// tail_ will point to the last node created and therefore will move
	// down the new list as it is built
	tail_ = head_;
	// old_p will point to the next node to be copied in the old list
	Node<T>* old_p = old.head_->next_;
	// copy the remainder of the old list, one node at a time
	while (old_p) {
		tail_->next_ = new Node<T>();
		(*(tail_->next_)).editValue((*old_p).value);
		(*(tail_->next_)).editNumElem((*old_p).num_elements);
		tail_->next_->prev_ = tail_;
		tail_ = tail_->next_;
		old_p = old_p->next_;
	}
}

template <class T>
//This function takes an Unrolled list and creates an exact copy
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
	// check for self-assignment
	if (&old != this) {
		destroy_list(); //destroy current list 
		copy_list(old); //creates copy 
	}
	return *this; //returns pointer to current value 
}


template <class T>
//This function takes a value as input and input the value to the front of the list
void UnrolledLL<T>::push_front(const T& v) {
	if (!head_) { //checks if head node exists 
		Node<T>* newp = new Node<T>(v);
		head_ = tail_ = newp;
		size_++;
	}
	else if ((*head_).num_elements >= NUM_ELEMENTS_PER_NODE) { //if node value array is full and node is head
		//creates new node and puts value at first value in new node 
		Node<T>* newp = new Node<T>(v);
		newp->next_ = head_;
		head_->prev_ = newp;
		head_ = newp;
		//inserts new node to beginning of list with old head after it 
		size_++;
	}
	else { //if node value array not full, inserts to front of node value array 
		(*head_).insertFront(v);
		size_++;
	}
}

template <class T>
//This function takes no input and removes the first value from the list 
void UnrolledLL<T>::pop_front() {
	if (head_) { //checks if head exists 
		if ((*head_).num_elements > 0) { //checks if head has any elements in value array
			if ((*head_).num_elements <= 1) { //if number of elements in head is <= 1 removes node from list
				Node<T>* temp = head_;
				head_ = head_->next_;
				delete temp;
				size_--;
			}
			else { //if node has more then 1 element, removes element from value array 
				T tempArr[NUM_ELEMENTS_PER_NODE];
				unsigned int tempArrIndex = 0;
				for (unsigned int i = 1; i < NUM_ELEMENTS_PER_NODE; i++) {
					tempArr[tempArrIndex] = (*head_).value[i];
					tempArrIndex++;
				}
				(*head_).editValue(tempArr); //replaces old values with new values
				(*head_).num_elements--;
				size_--;
			}
		}
		else { //if head has not elements in it removes head
			Node<T>* temp = head_;
			head_ = head_->next_;
			delete temp;
			size_--;
		}
	}
}

template <class T>
//This function takes a value as input and inserts it to the end of the unrolled list 
void UnrolledLL<T>::push_back(const T& v) {
	// special case: initially empty list
	if (!tail_) { //checks if tail exists, if not creates new node with value at first index 
		Node<T>* newp = new Node<T>(v);
		head_ = tail_ = newp;
		size_++;
	}
	else if ((*tail_).num_elements >= NUM_ELEMENTS_PER_NODE) {
	//if tail node is full, adds new node with value to end of list
		// normal case: at least one node already
		Node<T>* newp = new Node<T>(v);
		newp->prev_ = tail_;
		tail_->next_ = newp;
		tail_ = newp;
		size_++;
	}
	else { //if node is not full adds value to value array for tail node
		(*tail_).insertBack(v);
		size_++;
	}
}


template <class T>
//This function takes no input and removes the last element in the list 
void UnrolledLL<T>::pop_back() {
	if (tail_) { //checks if tail exists 
		if ((*tail_).num_elements > 0) { //if tail has any elements
			if ((*tail_).num_elements <= 1) { //checks if tail has <= 1 element 
				//removes entire node from list 
				Node<T>* temp = tail_; //temp pointer to deallocate memory of erased node
				tail_ = tail_->prev_;
				tail_->next_ = NULL; //frees memory of node removed from list
				delete temp;
				size_--;
			}
			else { //otherwise just removes last value from value array in node 
				T tempArr[NUM_ELEMENTS_PER_NODE]{};
				int tempArrIndex = 0;
				for (unsigned int i = 0; i < (*tail_).num_elements - 1; i++) {
					tempArr[tempArrIndex] = (*tail_).value[i];
					tempArrIndex++;
				}
				(*tail_).editValue(tempArr);
				(*tail_).num_elements--;
				size_--;
			}
		}
		else { //if tail does not have any elements 
			Node<T>* temp = tail_; //temp pointer to deallocate memory of erased node 
			tail_ = tail_->prev_;
			tail_->next_ = NULL;
			delete temp; //frees memory of node erased from node 
			size_--;
		}
	}
}

template <class T>
//This function inserts a value at a given iterator positiion 
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
	++size_;
	Node<T>* ptr_ = itr.getPtr(); //gets Node pointer iterator corresponds to

	if ((*ptr_).num_elements < NUM_ELEMENTS_PER_NODE) { //if node is not full
		//inserts value at index right before iterator position 
		(*ptr_).insertValue(itr.getOffset(), v);
		return itr; //returns position of new position 
	}
	else if ((*ptr_).num_elements >= NUM_ELEMENTS_PER_NODE) { //if node is full 
		//creates new node to be inserted before iterator position 
		Node<T>* p = new Node<T>();
		//Copies first half of values until offset position of iterator
		T tempArray[NUM_ELEMENTS_PER_NODE]{};
		unsigned int tempArrIndex = 0;
		unsigned int newNumElem = 0;
		for (unsigned int i = 0; i < (itr).getOffset(); i++) {
			tempArray[tempArrIndex] = (*ptr_).value[i];
			tempArrIndex++;
			newNumElem++;
		}
		tempArray[itr.getOffset()] = v; //inserts new value before iterator position 
		newNumElem++;
		//updates new Node values and num of elements
		(*p).editValue(tempArray);
		(*p).editNumElem(newNumElem);

		//copies half of values after iterator position
		T tempArray2[NUM_ELEMENTS_PER_NODE]{};
		tempArrIndex = 0;
		newNumElem = 0;
		for (unsigned int i = itr.getOffset(); i < NUM_ELEMENTS_PER_NODE; i++) {
			tempArray2[tempArrIndex] = (*ptr_).value[i];
			tempArrIndex++;
			newNumElem++;
		}

		//updates current pointer position values and num elements 
		(*ptr_).editValue(tempArray2);
		(*ptr_).editNumElem(newNumElem);
		

		//inserts new node before iterator position 
		p->prev_ = ptr_->prev_;
		p->next_ = ptr_;
		ptr_->prev_ = p;

		//checks if new node needs to be inserted at beginning of list
		if (ptr_ == head_)
			head_ = p;
		else //otherwise inserts normally 
			p->prev_->next_ = p;

		itr++;
		return itr; //returns new iterator position 
	}
	return itr;
}

template <class T>
//This function takes an iterator position and erases the value at that position 
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
	assert(size_ > 0); //make sure list is not empty 
	--size_;
	Node<T>* ptr_ = itr.getPtr(); //gets current Node pointer for iterator position 
	// One node left in the list.
	if (ptr_ == head_ && head_ == tail_) { 
		head_ = tail_ = 0;
		iterator result(head_);
	}
	// Removing the head in a list with at least two nodes
	else if (ptr_ == head_) {
		if ((*ptr_).num_elements <= 1) { //checks if node needs to removed
			Node<T>* tempP = head_; //temp pointer to deal with deallocating memory for erased node 
			head_ = head_->next_;
			head_->prev_ = 0;
			iterator result(head_->next_); //updates iterator position before deleting node 
			delete tempP;
			return result;
		}
		else { //otherwise removes value from node at correct offset position 
			(*ptr_).eraseValue(itr.getOffset());
			iterator result(ptr_);
			return result;
		}
		
	}
	// Removing the tail in a list with at least two nodes
	else if (ptr_ == tail_) { //if position is at end of list
		if ((*ptr_).num_elements <= 1) { //checks if node needs to be removed 
			Node<T>* tempP = tail_; //used for deallocating memory of node 
			tail_ = tail_->prev_;
			tail_->next_ = 0;
			iterator result(tail_->next_);
			delete tempP;
			return result;
		}
		else { //otheriwse removes value from offset position of node value array 
			(*ptr_).eraseValue(itr.getOffset());
			iterator result(ptr_);
			return result;
		}
	}
	// Normal remove
	else {
		if ((*ptr_).num_elements <= 1) { //checks if node needs to be removed 
			Node<T>* tempP = ptr_; //deallocates and removes node
			ptr_->prev_->next_ = ptr_->next_;
			ptr_->next_->prev_ = ptr_->prev_;
			iterator result(ptr_->next_);
			delete tempP; 
			
			return result; //returns new position of iterator 
		}
		else { // otherwise removes value from offset position in node 
			(*ptr_).eraseValue(itr.getOffset());
			iterator result(ptr_);
			return result;
		}
	}
	iterator result(ptr_);
	return result;
}


template<class T> 
//Printing function used to see contents of Unrolled Linked List, takes outstream as input 
//returns reference to outstream value 
ostream& UnrolledLL<T>::print(ostream& out) {
	Node<T>* current = head_;
	out << "UnrolledLL, size: " << size_ << endl;
	while (current != NULL) { //loops through list
		out << " node:[" << (*current).num_elements << "] ";
		for (unsigned int i = 0; i < (*current).num_elements; i++) { //loops through each value in value array
			out << (*current).value[i] << " ";
		}
		out << endl;
		current = current->next_;
	}
	return out;
}

template <class T>
//Destructor function to free all allocated memory on heap 
void UnrolledLL<T>::destroy_list() {
	if (empty())
		return;

	Node<T>* ptr = head_;
	Node<T>* next = NULL;

	while (ptr != NULL) {
		next = ptr->next_;
		delete ptr;
		ptr = next;
	}
	size_ = 0;
	head_ = tail_ = NULL;
}
#endif
