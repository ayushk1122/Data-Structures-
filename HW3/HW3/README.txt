HOMEWORK 3: CONNECT FOUR


NAME:  Ayush Krishnappa

COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://stackoverflow.com/questions/2168201/what-is-a-copy-constructor-in-c
https://stackoverflow.com/questions/4509730/class-assignment-operators
https://stackoverflow.com/questions/33866858/stack-overflow-in-c-destructor
Stack overflow used for learning more about copy constructor, assignment operator,
and destructor 

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >
20


ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
O(4n + 1) -> O(n) - worst case has to make new column to insert 
calls addToColumn and addToColRowCount which loop through n

insert (including checking for connected four)
O(4n + m*n + 1) -> O(m*n) - worst case has to check every single element in board 

numTokensInColum
O(1) - returned column index in colRowCounts array as it stores number of rows in given column

numTokensInRow
O(N) - worst case, every column has a token in that row

numColumns
O(1) - returns member variable which stores number of columns

numRows
O(1) - returns member variable which stores number of rows

print
O(M*N) - worst loops through all elements in board = rows * columns


clear
O(4n + (n*m)) -> O(n*m) - worst case deletes dynamic memory for each column and whole board is filled

TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used visual studio for most of the program debugging for my class design by using breakpoints. I used Dr.Memory in
Ubuntu for memory debugging. For testing, I mainly made my own manual print testing in the studentTests function
in the main file. For other logic and such I used pen and paper to map out the logic visually. 
 
MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

