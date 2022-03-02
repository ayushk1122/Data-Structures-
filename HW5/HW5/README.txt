HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  Ayush Krishnappa 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Dslist lecture file from lecture 11 on submitty 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 20 hours



TESTING & DEBUGGING STRATEGY:
Please be concise!  

Mixed use of printing and visual studio debugger, as well as Dr.Memory to deal with
memory errors. 



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 


push_front() - worst case must insert value to node and loop through all values
in node to shift elements over
O(NUM_ELEMENTS_PER_NODE)

push_back() - worst case must loop through all values in node and insert value
at the end of list
O(NUM_ELEMENTS_PER_NODE)

pop_front() - worst case must remove value from node and shift all node values over one
O(NUM_ELEMENTS_PER_NODE)

push_back() - worst case must remove value from node, needs to loop through and copy value
over to temp array
O(NUM_ELEMENTS_PER_NODE)

pop_back() - worst case must remove value from node, needs to loop through and copy value
over to temp array
O(NUM_ELEMENTS_PER_NODE)

insert() - worst case needs to insert at the very end position of a node value array,
then needs to copy over all but the last value from node to a new node, insert the new node to list,
and change the values of the old node
O(NUM_ELEMENTS_PER_NODE^2)

erase() - worst case needs to remove value from node and shift elements over
O(NUM_ELEMENTS_PER_NODE)

The main differences between the UnrolledLL class and other list classes, is the
method of storing data. Instead of having one pointer for one value like in other
list implementations, an UnrolledLL can have multiple values correspond to one Node*.
This makes it much more efficient. In the worst case, the UnrolledLL would constantly be full, and 
anytime a new value needed to be added a new node would have to be created to store
this new value. For example, consecutivly inserting to a node that is full would create
a new node each time, which would be very expensive in terms of memory. Each time
the node would store one value and it would defeat the purpose of the unrolledLL. To
avoid this we could create a set capacity which makes it so nodes cannot be completely filled.
This would be essentially half the value of the global number of elements per node. This way, anytime a 
new value needs to be added it can be done so in a much more efficient manner. 


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.
Did not implement, explained above however. 


MISC. COMMENTS TO GRADER:  
Optional, please be concise!


