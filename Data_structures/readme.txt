1 . Question Prompt:
Design and implement a Stack data structure in C++ from scratch. A stack is a linear data structure that follows the Last In, First Out (LIFO) principle, where the last element added to the stack is the first one to be removed. Your implementation should support the following operations:

Core Methods:
push(int value):

Adds an element to the top of the stack.
Should handle edge cases, such as attempting to push when the stack is at maximum capacity (for fixed-size stacks).
pop():

Removes the top element from the stack.
Returns the removed element.
Should handle edge cases, such as attempting to pop when the stack is empty.
top():

Returns the element at the top of the stack without removing it.
Should handle edge cases when the stack is empty.
isEmpty():

Returns true if the stack is empty and false otherwise.
isFull() (optional for fixed-size stacks):

Returns true if the stack has reached its maximum capacity and false otherwise.
Additional Requirements (Optional):
Dynamic Memory Support:

Implement the stack with dynamic memory allocation (e.g., using a dynamically resizable array).
Allow the stack to grow in size as needed.
Size Functionality:

Implement a size() method to return the current number of elements in the stack.
Exception Handling:

Throw exceptions or return error codes for invalid operations, such as popping or peeking from an empty stack.
Generic Implementation:

If possible, implement the stack to work with any data type (use templates in C++).


2. Question Prompt:
Design and implement a Queue data structure in C++ from scratch. A queue is a linear data structure that follows the First In, First Out (FIFO) principle, where the first element added to the queue is the first one to be removed. Your implementation should support the following operations:

Core Methods:
enqueue(int value):

Adds an element to the back (end) of the queue.
Should handle edge cases, such as attempting to enqueue when the queue is at maximum capacity (for fixed-size queues).

dequeue():
Removes and returns the element from the front of the queue.
Should handle edge cases, such as attempting to dequeue when the queue is empty.

front():
Returns the element at the front of the queue without removing it.
Should handle edge cases, such as calling front() on an empty queue.

isEmpty():
Returns true if the queue is empty and false otherwise.

isFull() (optional for fixed-size queues):
Returns true if the queue has reached its maximum capacity and false otherwise.