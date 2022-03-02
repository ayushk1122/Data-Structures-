#include <iostream>
#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}

////////STUDENT CODE//////

//Write your own test cases here
void StudentTest(){

	std::cout << "Test 1:" << endl;
	std::cout << "-----------------" << endl;
	Board b("G", "B", "-");
	std::cout << "Initial Board" << endl;
	std::cout << b << endl;

	b.insert(0, false);
	b.insert(1, false);
	b.insert(2, false);
	string result = b.insert(3, true);
	b.insert(4, false);
	
	Board b1 = b;
	Board b2(b);

	std::cout << "Full row inserted: " << endl;
	std::cout << b << endl;
	std::cout << "Tokens in Row 0: " << b.numTokensInRow(0) << endl;
	std::cout << "Tokens in Col 0: " << b.numTokensInColumn(0) << endl;
	std::cout << endl;
	std::cout << "Testing assignment operator:" << endl;
	std::cout << b1 << endl;
	std::cout << "Tokens in Row 0: " << b1.numTokensInRow(0) << endl;
	std::cout << "Tokens in Col 0: " << b1.numTokensInColumn(0) << endl;
	std::cout << "Testing copy constructor:" << endl;
	std::cout << b2 << endl;
	std::cout << "tokens in row 0: " << b2.numTokensInRow(0) << endl;
	std::cout << "tokens in col 0: " << b2.numTokensInColumn(0) << endl;
	std::cout << "winner: " << result << endl;
	b.clear();

	std::cout << endl;
	std::cout << "Cleared Board" << endl;
	std::cout << b << endl;
	std::cout << endl;


	std::cout << "Test 2:" << endl;
	std::cout << "-----------------" << endl;
	Board b3("Dog", "Cat", "###");
	b3.insert(0, true);
	b3.insert(0, true);
	b3.insert(0, true);
	string result2 = b3.insert(0, true);

	std::cout << "Full column inserted: " << endl;
	std::cout << b3 << endl;
	std::cout << "Winner: " << result2 << endl;
	std::cout << "Tokens in Row 0: " << b3.numTokensInRow(0) << endl;
	std::cout << "Tokens in Col 0: " << b3.numTokensInColumn(0) << endl;
	std::cout << endl;

	b3.clear();
	b3.insert(0, true);
	b3.insert(1, false);
	b3.insert(1, false);
	b3.insert(10, false);
	b3.insert(0, false);
	b3.insert(2, false);
	b3.insert(2, false);
	b3.insert(3, false);
	b3.insert(0, true);
	b3.insert(0, false);
	b3.insert(0, true);
	b3.insert(0, false);
	string result3 = b3.insert(3, false);
	std::cout << "Testing column and row adding functionality: " << endl;
	std::cout << b3 << endl;
	std::cout << "Winner: " << result3 << endl;
	std::cout << "Tokens in Row 1: " << b3.numTokensInRow(1) << endl;
	std::cout << "Tokens in Col 10: " << b3.numTokensInColumn(10) << endl;
	std::cout << endl;

	
	std::cout << endl;
	std::cout << "Test 3:" << endl;
	std::cout << "-----------------" << endl;
	b3.clear();

	b3.insert(0, true);
	b3.insert(1, false);
	b3.insert(2, true);
	b3.insert(3, true);
	b3.insert(4, true);
	string result4 = b3.insert(5, true);
	std::cout << "Testing win functionality in row" << endl;
    std::cout << b3 << endl;
	std::cout << "Winner: " << result4 << endl;

	
	std::cout << endl;
	std::cout << "Test 4" << endl;
	std::cout << "-----------------" << endl;
	b3.clear();

	b3.insert(4, true);
	b3.insert(5, false);
	b3.insert(6, false);
	b3.insert(7, false);
	string result5 = b3.insert(8, false);
	std::cout << "Testing win functionality and creating new columns simultaneously" << endl;
	std::cout << b3 << endl;
	std::cout << "Winner: " << result5 << endl;



	std::cout << endl;
	std::cout << "Test 5" << endl;
	std::cout << "-----------------" << endl;
	b3.clear();

	b3.insert(1, true);
	b3.insert(1, true);
	b3.insert(1, true);
	b3.insert(1, false);
	b3.insert(1, false);
	b3.insert(1, false);
	string result6 = b3.insert(1, false);
	
	std::cout << "Testing win functionality and creating new rows simultaneously" << endl;
	std::cout << b3 << endl;
	std::cout << "Winner: " << result6 << endl;



	std::cout << endl;
	std::cout << "Test 6" << endl;
	std::cout << "-----------------" << endl;
	b3.clear();

	b3.insert(1, true);
	b3.insert(1, true);
	b3.insert(3, true);
	b3.insert(3, true);
	b3.insert(4, true);
	b3.insert(4, true);
	b3.insert(6, false);
	b3.insert(6, false);
	b3.insert(7, false);
	b3.insert(8, false);
	string result7 = b3.insert(9, false);

	std::cout << "Testing win functionality with blank columns in between" << endl;
	std::cout << b3 << endl;
	std::cout << "Winner: " << result7 << endl;


	std::cout << endl;
	std::cout << "Test 7" << endl;
	std::cout << "-----------------" << endl;
	b3.clear();

	b3.insert(2, false);
	b3.insert(2, true);
	b3.insert(3, false);
	b3.insert(3, true);
	b3.insert(3, false);
	b3.insert(4, false);
	b3.insert(4, true);
	b3.insert(5, true);
	string result8 = b3.insert(5, true);
	

	std::cout << "Testing win functionalityin middle of board" << endl;
	std::cout << b3 << endl;
	std::cout << "Winner: " << result8 << endl;

}

