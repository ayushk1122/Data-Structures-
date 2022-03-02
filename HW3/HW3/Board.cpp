#include "Board.h"
#include <string>
#include <array>
using namespace std;

Board::Board(string p1_, string p2_, string blank_) {
	//sets columns and rows to minimal values
	cols = 4;
	rows = 5;

	board = new string* [cols]; //points board pointer to array of string pointers
	//initializes string array to NULL to signify empty 
	board[0] = NULL;
	board[1] = NULL;
	board[2] = NULL;
	board[3] = NULL;
	p1 = p1_;
	p2 = p2_;
	blank = blank_;

	//points row Counts pointer to int array
	colRowCounts = new int[cols];
	//initializes all to 0 to signify empty 
	colRowCounts[0] = 0;
	colRowCounts[1] = 0;
	colRowCounts[2] = 0;
	colRowCounts[3] = 0;
}


Board::Board(const Board& copy) { //copy constructor, copies all member variables to new board object
	cols = copy.cols;
	rows = copy.rows;
	p1 = copy.p1;
	p2 = copy.p2;
	blank = copy.blank;
	board = new string * [copy.cols];
	for (int i = 0; i < cols; i++) { //loops through entire copy board to ensure no unaddressable access occure
		board[i] = new string[copy.colRowCounts[i]];
		for (int j = 0; j < copy.colRowCounts[i]; j++) {
			board[i][j] = copy.board[i][j];
		}
	}
	colRowCounts = new int[copy.cols];
	for (int i = 0; i < cols; i++) {
		colRowCounts[i] = copy.colRowCounts[i];
	}
}

Board& Board::operator=(const Board& b1) { //assignment operator, returns reference to new Board object
	cols = b1.cols;
	rows = b1.rows;
	p1 = b1.p1;
	p2 = b1.p2;
	blank = b1.blank;
	board = new string * [b1.cols];
	for (int i = 0; i < cols; i++) { //loops through entire old board to ensure no unaddressable access occure
		board[i] = new string[b1.colRowCounts[i]];
		for (int j = 0; j < b1.colRowCounts[i]; j++) {
			board[i][j] = b1.board[i][j];
		}
	}
	colRowCounts = new int[b1.cols];
	for (int i = 0; i < cols; i++) {
		colRowCounts[i] = b1.colRowCounts[i];
	}
	return *this; //returns pointer to board object 
}

Board::~Board() { //destructor 
	//frees all dynamically allocated memory any time Board object is destroyed 
	for (int i = 0; i < cols; i++) {
		delete[] board[i];
	}
	delete[] board;
	delete[] colRowCounts;
}

void Board::clear() { //clears state of board and sets all member variables back to initial state
	//frees all dynamically allocated memory 
	for (int i = 0; i < cols; i++) {
		delete[] board[i];
	}
	delete[] board;
	delete[] colRowCounts;
	//re-initializes all member variables back to initial values
	//creates new empty arrays for board and row counts pointers
	cols = 4;
	rows = 5;
	board = new string * [cols];
	board[0] = NULL;
	board[1] = NULL;
	board[2] = NULL;
	board[3] = NULL;
	colRowCounts = new int[cols];
	colRowCounts[0] = 0;
	colRowCounts[1] = 0;
	colRowCounts[2] = 0;
	colRowCounts[3] = 0;
}

int Board::numRows() const { //returns int value of max number of rows in board
	return rows;
}

int Board::numColumns() const { //returns int value of number of columns in board
	return cols;
}

string** Board::getBoard() const { //returns pointer pointing to pointer of current board
	return board;
}

int* Board::getColRowCounts() const{ //accessor function returns rowCounts pointer
	return colRowCounts;
}

string Board::getBlank() const { //returns blank space token
	return blank;
}

//function takes row number as input and returns number of tokens in that row
int Board::numTokensInRow(int row) const { //returns int value of number of tokens in specified row 
	int numTokens = 0;
	if (row <= (rows - 1)) { //checks if row num exceeds max number of rows
		for (int i = 0; i < cols; i++) { //loops through each column in board
			if (row < colRowCounts[i]) { //if given row num is less then row count for that column, there is a token in that row
				numTokens++; 
			}
		}
		return numTokens;
	}
	return -1; //returns -1 if row is not valid (exceeds max number of rows)
}

//function takes column number as input and returns number of tokens in specified column
int Board::numTokensInColumn(int col) const { //returns int value of number of tokens in given column 
	if (col <= (cols - 1)) { //checks if given column num is valid/in range
		return colRowCounts[col]; //returns the number of rows in given column since its equivelent to # of tokens in column
	}
	return -1; //returns -1 if column number is invalid 
}


void Board::setNumRowInCol(int colNum, int numRows) { //modifier function to set the number of rows in a given column
	//given column number and number of rows in column
	colRowCounts[colNum] = numRows;
}

//function takes in the number of rows in the new column and the new number of columns in the board as input
void Board::addNewColToRowCounts(int numRows, int colSize) { //adds new Col to row counts array to store its size
	int *temp = new int[colSize]; //temp pointer to copy old values from array of sizes, size of temp = new number of columns

	//loops through old column values and copies over to temp array
	for (int i = 0; i < (cols); i++) {
		temp[i] = colRowCounts[i];
	}

	//loops and initializes rest of temp array to 0, except last value
	for (int j = cols; j < (colSize - 1); j++) {
		temp[j] = 0;
	}
	temp[colSize - 1] = numRows; //sets last value equal to number of rows in the new column

	delete[] colRowCounts; //frees allocated memory for old array of sizes
	colRowCounts = temp; //sets colRowCounts equal to new array of sizes
}

//function takes the new number of columns for the board as input 
void Board::addNewColToBoard(int colSize) { //function adds new columns to the board
	string** temp = new string *[colSize]; //new temp pointer to store old string arrays for current board

	//loops through and copies string arrays in current board over to temp
	for (int i = 0; i < (cols); i++) {
		temp[i] = board[i]; 
	}

	//initializes rest of temp pointers to null to siginfiy empty, except last column
	for (int j = cols; j < (colSize - 1); j++) {
		temp[j] = NULL;
	}

	//sets last column equal to a new string array of 1 token size
	temp[colSize - 1] = new string[1];
	delete[] board; //frees allocated memory for current board
	board = temp; //reassigns board to temp to add new columns
}

//used whenever using cout << to print a board object, returns outstream reference 
ostream& operator<< (ostream& out, const Board& board) { //operator function to print out contents of given Board instance
	//uses accessor methods to get current state of board, since function is outside scope of class
	string** t_board = board.getBoard();
	int* colRowCounts = board.getColRowCounts();
	int rows = board.numRows();
	int cols = board.numColumns();

	//loops though each row in board
	for (int r = (rows - 1); r >= 0; r--) {
		//loops through each column in board 
		for (int i = 0; i < cols; i++) {
			//if row index is greater then number of rows in column, prints blank token
			if (r > (colRowCounts[i]) - 1) {
				//prints space after each column except last
				if (i != (cols - 1)) { out << board.getBlank() << " "; }
				else { out << board.getBlank(); }
			}
			else { //if row index is within number of rows in column, prints value at row index for that column
				//prints space after each column except last
				if (i != (cols - 1)) { out << t_board[i][r] << " "; }
				else { out << t_board[i][r]; }
			}
		}
		out << endl; //new line after each row 
	}
	return out;
}

//this function takes a column number as input and checks if there are 4 tokens of the same player in a row in that given column
bool Board::checkConnectCol(int colNum) { //function used to check win functionality 
	string token = ""; //keeps track of current player token
	int counter = 0; //used to keep track of tokens in a row 
	for (int i = 0; i < colRowCounts[colNum]; i++) { //loops through each row in given column
		if (counter == 4) { break; } //if counter = 4, there is a winner, breaks loop

		if ( counter == 0 ) { //beginning of count
			token = board[colNum][i]; //sets token = to the token at index
			counter = 1;
		}
		else { //checks if next element is the same as the current token
			if (board[colNum][i] == token) { //increments counter if so 
				counter++;
			}
			else { //otherwise resets counter to 1 and stores new token element 
				counter = 1;
				token = board[colNum][i];
			}
		}
	}

	if (counter == 4) { return true; } //if counter = 4 returns true since there is a winner
	else { return false; } //otherwise returns false
}

//this function takes a row number as input and checks if there are 4 tokens of same player in a row in given row
bool Board::checkConnectRow(int rowNum) { //function used to check win functionality 
	string token = "";
	int counter = 0;
	for (int i = 0; i < cols; i++) { //loops through each column in board
		if (counter == 4) { break; } //breaks loop if winner is found

		if (rowNum < colRowCounts[i]) { //checks if row number is within range of number of rows in column
			if (counter == 0) { //begins counting 
				token = board[i][rowNum]; //sets token to given row index
				counter = 1;
			}
			else { //checks next column to see if element is the same as current stored token
				if (board[i][rowNum] == token) { //if so increments counter
					counter++;
				}
				else { //otherwise resets counter to 1 and stores new token element 
					counter = 1;
					token = board[i][rowNum];
				}
			}
		}
		else { //if row number is out of range, resets counter and begins count at next column element 
			counter = 0;
		}
	}

	//returns true if winner is found or false if no winner is found 
	if (counter == 4) { return true; } 
	else { return false; }
}

//function uses the checkConnectCol and checkConnectRow to determine if there is a winner on the board
bool Board::checkConnectFour() { //main driver function for win functionality 
	for (int i = 0; i < cols; i++) { //loops through each column and checks for winners
		if (checkConnectCol(i)) { //if there is winner in column returns true
			return true;
		}
	}

	for (int j = 0; j < rows; j++) { //loops through each row and checks for winners 
		if (checkConnectRow(j)) { //returns true if winner is found in row
			return true;
		}
	}

	return false; //returns false if no winner is found in entire board
}

/*Function takes a column numberand player boolean as inputand inserts the given token into the correct column
*if column number exceeds the number of columns in current board, the board grows in size to be able to insert token
* at given column number. Same functionality if tokens begin to overfill any column, rows will grow as well. 
*Function also checks each time a token is inserted if there is a winner on the board, returns 
* token of winner if there is a winner, otherwise returns token for blank space to signify no winner yet. 
*/
string Board::insert(int col, bool player) { //function inserts a token into the board into the correct column
	string token = "";
	//sets insert token value to correct player token
	if (player) { token = p1; }
	else { token = p2; }

	if (col <= (cols - 1)) { //if given column number is within the range of current # of columns on the board
		colRowCounts[col]++; //increments row size for given column 
		if (colRowCounts[col] > rows) { //checks condition for overflowing column 
			rows = colRowCounts[col]; //if column is overflowed max number of rows increases 
		}

		if (colRowCounts[col] == 0) { //if column is empty
			delete board[col]; //frees column 
			board[col] = new string[colRowCounts[col]]; //assigns new string array of size rowCounts to column
			board[col][0] = token; //sets first value equal to input token
			if (checkConnectFour()) { //checks win condition any time token is inserted 
				return token; 
			}
		}
		else { //if column is not not empty 
			string* temp = new string[colRowCounts[col]]; //temp array to store current tokens in column 
			for (int i = 0; i < (colRowCounts[col] - 1); i++) { //loops through and copies over current tokens
				temp[i] = board[col][i];
			}
			temp[colRowCounts[col] - 1] = token; //last element in temp array is assigned to insert token
			delete[] board[col]; //frees old column in board
			board[col] = temp; //assigns new column with insert token to given column
			if (checkConnectFour()) { //checks win condition 
				return token; 
			}
		}
	}
	else { //new column needs to be added 
		int tempColSize = (col + 1); //temp value to store new # of columns, adds one to col since its an index value
		addNewColToRowCounts(1, tempColSize); //adds new column of size 1 to row counts array
		addNewColToBoard(tempColSize); //adds new empty column to board 
		board[col][0] = token; //inserts new token into given column index
		cols = tempColSize; //sets number of columns = to new number of columns in board
		if (checkConnectFour()) { //checks win condition
			return token; 
		}
	}

	return blank; //returns blank if insertion is complete and no winner is found 
}



