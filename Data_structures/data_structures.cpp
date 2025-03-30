/*
Here will be all the data structures, implemented from scratch, given some requirements.
All will be implemented with integers (also templates could be used) and 
based on some requirements
*/

/*
1. Stack
*/

#include "data_structures.hpp"
#include <iostream>

MyStack::MyStack(int sz): stack_size(sz) , top_index(-1) {
    stack = new int[stack_size];
}

MyStack::MyStack() : stack_size(100), top_index(-1){
    stack = new int[100];
}

void MyStack::push(const int val)
{
    // cannot push to a full stack
    if (is_full()) resize();
    
    ++top_index;
    stack[top_index] = val;
}

void MyStack::pop()
{
    if (is_empty()) throw std::runtime_error("Stack is empty, cannot pop any item");
    --top_index; // point to another element
}

bool MyStack::is_empty()
{
    return (top_index == -1);
}

bool MyStack::is_full()
{
    return (top_index == (stack_size - 1));
}

int MyStack::top()
{
    if (is_empty()) throw std::runtime_error("Stack is empty, cannot show any item"); 
    return stack[top_index];
}

int MyStack::get_size()
{
    return (top_index + 1);
}

void MyStack::resize()
{
    // here we want to resize the stack when it hits the limit
    // this could be a follow up question
    stack_size = stack_size * 2;
    if (stack_size > MAX_STACK_SIZE ) stack_size = MAX_STACK_SIZE;
    if (top_index == MAX_STACK_SIZE -1 ) throw std::runtime_error("Stack hit the limit. Cannot resize any further"); 
    int* temp_stack = new int[stack_size]; // lets allocate twice the stack
    int temp_top_index = top_index;
    for (int i = top_index; i >= 0 ; --i )
    {
        temp_stack[i] = stack[i];
        
    }
    top_index = temp_top_index; // re assign the top index
    delete [] stack;

    // update the stack pointer
    stack = temp_stack;
   
}

MyStack::~MyStack() {
delete [] stack;
stack = nullptr;
} 


MyQueue::MyQueue(int sz) :
queue_size(sz),
rear(-1),
front(-1) {
queue = new int[queue_size];// allocate space
}

void MyQueue::enqueue(int val)
{
    // we should add to the rear of course
    if (is_empty()) front = 0; // set correctly the index
    
    if (is_full()) resize();

    ++rear;
    queue[rear] = val;
}

int* MyQueue::dequeue()
{
    // we should add to the rear of course
    if (is_empty()) throw std::runtime_error("Queue is empty cannot dequeue any further. Consider to enqueue");

    int* current_front_ptr = (queue + front);
    ++front;
    // in case queue is empty let's make the counters invalid and begin from the beggining
    if (front > rear) 
    {
        front = -1;
        rear = -1;
    }
    return (current_front_ptr);
}

bool MyQueue::is_empty()
{
    return  (front == -1 && rear == -1);
}

bool MyQueue::is_full()
{
    return (rear == queue_size - 1);
}

void MyQueue::resize()
{
    
    // will resize in case we hit the limit
    if ( 2*queue_size > MAX_QUEUE_SIZE)
    {
        queue_size = MAX_QUEUE_SIZE;
    } 
    else{
        queue_size= queue_size*2;
    }

    int* temp_queue = new int[queue_size]; // allocate enough space
    // now we will not only resize but also reallocate the elements

    int temp_index = front;
    for (int i = 0; i < (rear - front) ; ++i){
        temp_queue[i] = queue[temp_index];
        ++temp_index;
    }

    // re assign the indexes
    rear = (rear - front);
    front = 0;

    // delete the queue
    delete [] queue;
    queue = temp_queue;
}

MyQueue::~MyQueue() noexcept{
    delete [] queue;
    queue = nullptr; // avoiding dangling pointer
}

int MyQueue::top(){
    if (is_empty()) throw std::runtime_error("Queue is empty cannot dequeue any further. Consider to enqueue");
    return (queue[front]);
}

   