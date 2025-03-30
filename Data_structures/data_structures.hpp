
#include <vector>
#include <iostream>
#define MAX_STACK_SIZE 100000
#define MAX_QUEUE_SIZE 100000

class MyStack
{
private:
    int top_index; // index that shows the top of the stack
    int stack_size;
    int *stack;

public:
    MyStack(int sz);
    MyStack();
    void push(const int val);
    void pop();
    int top();
    bool is_full();
    bool is_empty();
    int get_size();
    void resize();
    ~MyStack();
};

class MyQueue
{
private:
    // indexes for keeping track of rear and front index
    int front;
    int rear;
    int *queue;     // the dynamic array to keep track
    int queue_size; // this will indicate the current maximum_size of the queue
public:
    MyQueue();
    MyQueue(int sz);
    ~MyQueue() noexcept;
    void enqueue(int value);
    int *dequeue(); // returns pointer to the element
    bool is_full();
    bool is_empty();
    int top();
    void resize();
};

template <typename T>
class RingBuffer
{
private:
    // indexes for keeping track of rear and front index
    int front_index;
    int rear_index;
    T *ring_buffer;                  // the dynamic array to keep track
    int buffer_current_maximum_size; // this will indicate the current maximum_size of the queue
    int count_elements;              // indicate how many elements exist in buffer
public:
    RingBuffer() : front_index(-1),
                   rear_index(-1),
                   buffer_current_maximum_size(100),
                   count_elements(0)
                    {
                        ring_buffer = new T[buffer_current_maximum_size];
                    }
    RingBuffer(int sz): front_index(-1),
                   rear_index(-1),
                   buffer_current_maximum_size(sz),
                   count_elements(0)
                    {
                        ring_buffer = new T[buffer_current_maximum_size];
                    }
    ~RingBuffer() noexcept
    {
        delete[] ring_buffer;
        ring_buffer = nullptr;
    }
    void enqueue(T value)
    {
        // we should use the modulo operation
        if (is_full())
            resize();
        else if (buffer_current_maximum_size == MAX_QUEUE_SIZE) throw std::runtime_error("Ring buffer is full cannot push any further");

        if (is_empty())
            front_index = 0; 
        rear_index = (rear_index + 1) % buffer_current_maximum_size;
        ring_buffer[rear_index] = value;
        ++count_elements;
    }
    void dequeue() 
    {
        if (is_empty()) throw std::runtime_error("Ring buffer is empty cannot dequeue");

        // if before the deque the two indexes are equal -> set them both to -1 to indicate empty buffer
        if (front_index == rear_index  )
            front_index = rear_index = -1; // indicate empty buffer
        else
            front_index = (front_index + 1) % buffer_current_maximum_size;
        
        --count_elements;
    }
    bool is_full()
    {
        return ((rear_index - front_index + 1) == buffer_current_maximum_size);
    }

    int count_current_elements()
    {
        //return the current items in the buffer
        return (count_elements);
    }
    bool is_empty()
    {
        return ( count_elements == 0);
    }

    T front(){
        if (is_empty()) throw std::runtime_error("Ring buffer is empty cannot retrieve the front element");
        return (ring_buffer[front_index]);
    }

    void resize()
    {
        if ( 2 * buffer_current_maximum_size > MAX_QUEUE_SIZE )
            buffer_current_maximum_size = MAX_QUEUE_SIZE;
        else
            buffer_current_maximum_size = buffer_current_maximum_size * 2; 
        
        T * temp_buffer = new T[buffer_current_maximum_size];
        
        for (int i = 0 ; i < count_elements ; ++i)
        {
            temp_buffer[i] = ring_buffer[(front_index + i) % buffer_current_maximum_size];
        }

        delete [] ring_buffer;
        ring_buffer = temp_buffer;
    }
};
