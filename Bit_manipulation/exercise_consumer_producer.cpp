/*
Prompt:
Design and implement a Ring Buffer (Circular Buffer) in C that supports the following operations:

Push: Add an element to the buffer. If the buffer is full, overwrite the oldest element.
Pop: Remove the oldest element from the buffer. If the buffer is empty, indicate that the operation cannot proceed.
Requirements:
Implement the ring buffer as a fixed-size array.
Maintain indices for the head (where elements are removed) and tail (where elements are added).
Handle edge cases:
Overwriting elements when the buffer is full during a push.
Returning an error or indicating failure if pop is called on an empty buffer.
The buffer should work for integers (int type).
Demonstrate the implementation with an example.

Problem Statement: Synchronize Producer and Consumer Threads
Prompt:
Write a program in C to demonstrate synchronization between a producer thread and a consumer thread. The producer thread generates data and adds it to a shared buffer. The consumer thread processes data from the shared buffer. Use appropriate synchronization primitives to ensure safe access to the shared buffer and avoid race conditions.

Requirements:
The shared buffer is implemented as a fixed-size circular queue.
The producer adds integers to the buffer, and the consumer removes integers from the buffer.
Synchronization should prevent the producer from adding data when the buffer is full and the consumer from removing data when the buffer is empty.
Use POSIX threads (pthread) and synchronization primitives like mutexes and condition variables.
Functionality:
Producer Thread:

Continuously generates integers and adds them to the shared buffer.
Waits if the buffer is full.
Consumer Thread:

Continuously removes integers from the shared buffer and processes them (e.g., prints them).
Waits if the buffer is empty.

*/

// Ok lets first do the circular buffer array
#include <stdio.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#define MAX_BUFFER_SIZE 100

struct RingBuffer
{
    int arr[MAX_BUFFER_SIZE]; // initialize the buffer
    int buffer_size;
    int front = -1;       // this is the index to the front element
    int rear = -1;        // this is the index to the front element
    bool is_full = false; // boolean to indicate whether the ring buffer is ful or not
    bool is_empty = false;

    RingBuffer(int n)
    {

        buffer_size = n;

        for (int i = 0; i < buffer_size; ++i)
        {
            arr[i] = 0;
        }
    };

    void push(int elem)
    {
        if (is_empty)
            front++;
        rear = (rear + 1) % buffer_size; // since we have circular buffer we want to ensure that we add in that matter

        arr[rear] = elem;
    }
    int pop()
    {
        if (is_empty)
        {
            throw std::runtime_error("Circular buffer is empty, cannot pop any element!");
        }

        int temp_value = arr[front];

        if (front == rear)
        {
            front = rear = -1; // we will pop the last element
            is_empty = true;
        }
        else
        {
            front = (front + 1) % buffer_size;
        }

        return temp_value;
    }

    bool is_empty_func()
    {
        return is_empty;
    }

    bool is_full_func()
    {
        return ((rear - front) == buffer_size);
    }

};

std::mutex _mtx_ring_buffer;             // we will use this to lock the shared resource
std::condition_variable _cv_ring_buffer; // conditional variable to signal as soon as resource is ready for read write

void consumer(RingBuffer &ring_buffer)
{
    int item = 0;
    // the idea is that this thread consumes and does it the whole time
    while (true)
    {
        // check if is empty , if it is we should wait
        // since it is a shared resource the ring buffer we should wait until it is released
        
        std::unique_lock<std::mutex> lock(_mtx_ring_buffer); // here we locked the buffer
        // This boils down to understanding how std::condition_variable works and the behavior of std::unique_lock during cv.wait().
        // When a thread calls cv.wait(lock, predicate), it does the following:

        // // Automatically unlocks the mutex (lock in this case) if the predicate evaluates to false and the thread needs to wait.
        // // The mutex remains unlocked while the thread is waiting on the condition variable. This allows other threads to acquire the mutex and perform their operations.
         // // When the condition variable is notified (via cv.notify_all() or cv.notify_one()), the waiting thread reacquires the mutex, reevaluates the predicate,
        // // and proceeds if the predicate is true.
        _cv_ring_buffer.wait(lock,[&ring_buffer]{return !ring_buffer.is_empty_func();});

        // now we are ready to pop
        item = ring_buffer.pop();
        std::cout<<"Consumed item " << item << std::endl;

        // unlock and notify
        lock.unlock();
        _cv_ring_buffer.notify_all(); // notify the producer that we have done with the consuming and can acquire the resource now
    }
}

void producer(RingBuffer &ring_buffer)
{
    int item = 0;
    while(true)
    {

        // the idea is that we lock in order to acquire the resource
        std::unique_lock<std::mutex> lock(_mtx_ring_buffer);

        // we wait until buffer is not full
        _cv_ring_buffer.wait(lock,[&ring_buffer]{return !(ring_buffer.is_full_func());});

        // now we push
        ring_buffer.push(item);
        std::cout<<"Item pushed was " << item << std::endl;
        ++item;
    }
}

/// testing
#include <gtest/gtest.h>



class RingBufferTest : public ::testing::Test {
protected:
    RingBufferTest() : ring_buffer(5) {} // Create a RingBuffer with a capacity of 5

    RingBuffer ring_buffer; // The ring buffer we will test
};

// Test for push and pop methods
TEST_F(RingBufferTest, PushPopTest) {
    // Test pushing and popping items from the buffer

    // Push 5 items into the buffer
    for (int i = 0; i < 5; ++i) {
        ring_buffer.push(i);
    }

    // Pop 5 items from the buffer and verify that the correct elements are returned
    for (int i = 0; i < 5; ++i) {
        int popped_item = ring_buffer.pop();
        EXPECT_EQ(popped_item, i);  // Verify the item popped matches the expected item
    }
}

// Test for overwriting elements when full
TEST_F(RingBufferTest, OverwriteWhenFull) {
    // Push 5 items into the buffer
    for (int i = 0; i < 5; ++i) {
        ring_buffer.push(i);
    }

    // The buffer should now be full
    // Push one more item, which should overwrite the oldest one (0)
    ring_buffer.push(5);

    // Pop the buffer and check that the oldest item was overwritten
    EXPECT_EQ(ring_buffer.pop(), 1);  // 0 should have been overwritten by 5
    EXPECT_EQ(ring_buffer.pop(), 2);
    EXPECT_EQ(ring_buffer.pop(), 3);
    EXPECT_EQ(ring_buffer.pop(), 4);
    EXPECT_EQ(ring_buffer.pop(), 5);  // 5 should be the last item
}

// Test for buffer underflow (pop from empty buffer)
TEST_F(RingBufferTest, PopEmptyBuffer) {
    EXPECT_THROW(ring_buffer.pop(), std::runtime_error);  // Should throw an exception on pop from an empty buffer
}

// Test for producer-consumer synchronization
TEST_F(RingBufferTest, ProducerConsumerTest) {
    std::thread producer_thread(producer, std::ref(ring_buffer));  // Create a producer thread
    std::thread consumer_thread(consumer, std::ref(ring_buffer));  // Create a consumer thread

    // Allow the threads to run for a while
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // After some time, stop the threads by setting a flag, for example
    producer_thread.join();
    consumer_thread.join();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); // Initialize Google Test
    return RUN_ALL_TESTS(); // Run all tests
}