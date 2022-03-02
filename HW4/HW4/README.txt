HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  Ayush Krishnapa 


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://stackoverflow.com/questions/14544539/linked-lists-in-c

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >
10

ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order

Include a short description of your order notation analysis.

add_order:
O(1) - constant time adds to end of vector - push-back 

add_item:
O(1) - constant time adds to end of vector - push-back

print_orders_by_time:
O(ologo + o + o*p) - O(o*p) since this utilizes the sort function 
o*p since certain number of items per order 

print_orders_by_id:
O(ologo + o + o*p) - O(o*p) also utilizes sort function 

print_kitchen_is_cooking:
O(clogc + c) - O(clogc) uses sorting function

print_kitchen_has_completed:
O(dlogd + d) - O(dlogd) uses sorting functio

run_until_next:
O(ologo + clogc + c + o + o*d) - O(o*d) - largest value
worst case loops through all completed items ready to add to order if an
order can be filled 

run_for_time:
O(ologo + clogc + c + o + o*d) - O(o*d) - largest value
same as run until next, in worst case being an order needs to be filled and all itmes
in food completed list are removed



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






