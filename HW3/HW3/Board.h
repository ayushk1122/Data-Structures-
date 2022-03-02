#pragma once
#ifndef __Board_h__
#define __Board_h__
#include <string>
#include <array>
#include <iostream>
using namespace std;
class Board {
public:
	Board(string p1_, string p2_, string blank_);
	Board(const Board& b1); //copy constructor 
	Board& operator=(const Board& b1); //assignment operator 

	//Accessor Functions
	int numRows() const;
	int numColumns() const;
	int numTokensInRow(int row) const;
	int numTokensInColumn(int col) const;
	int* getColRowCounts() const;
	string getBlank() const;
	string** getBoard() const;

	//Modifier Functions
	void clear(); 
	void setNumRowInCol(int colNum, int numRows);
	void addNewColToRowCounts(int numRows, int colSize);
	void addNewColToBoard(int colSize);
	string insert(int col, bool player);

	//Win Functionality functions
	bool checkConnectFour();
	bool checkConnectCol(int colNum);
	bool checkConnectRow(int rowNum);

	//Destructor
	~Board();

private:
	//member variables 
	int cols;
	int rows;

	int *colRowCounts; //stores sizes of individual columns

	string **board; //stores string[] of tokens for board
	string p1; //player 1 token
	string p2; //player 2 token
	string blank; //blank space filler
};

ostream& operator<< (ostream& out, const Board& board); //operator to print board instances 

#endif
