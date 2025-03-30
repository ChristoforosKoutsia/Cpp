#include <gtest/gtest.h>
#include "data_structures.hpp"

class StackTest : public testing::Test {
    protected:
    StackTest()
    {
        stack_1.push(1);
        stack_1.push(2);
    }

    MyStack stack_1 = MyStack(100);
    MyStack stack_0 = MyStack(3);

};



class QueueTest : public testing::Test {
    protected:
    QueueTest()
    {
        _q1.enqueue(1);
        _q1.enqueue(2);
    }

    MyQueue _q0 = MyQueue(100);
    MyQueue _q1 = MyQueue(3);

};

TEST_F(StackTest, CheckLIFO) {
  EXPECT_EQ(stack_1.top(), 2);
}

TEST_F(StackTest, PopWorks) {
  stack_1.pop();
  EXPECT_EQ(stack_1.top(), 1);
  EXPECT_EQ(stack_1.get_size(), 1);
  EXPECT_EQ(stack_0.get_size(), 0);
}

TEST_F(StackTest, FullStack) {
  stack_0.push(1);
  stack_0.push(2);
  stack_0.push(3);
  //EXPECT_THROW(stack_0.push(0),std::runtime_error);
  stack_0.push(4);
  EXPECT_EQ(stack_0.top(),4);
}

TEST_F(StackTest, EmptyStack) {
  stack_0.push(1);
  stack_0.push(2);
  stack_0.push(3);
  
  EXPECT_EQ(stack_0.top(),3);
  stack_0.pop();
  stack_0.pop();
  EXPECT_EQ(stack_0.top(),1);
  stack_0.pop();
  EXPECT_THROW(stack_0.pop(),std::runtime_error);
}

TEST_F(StackTest, FullStackHitLimit) {
  for (int i = 0 ; i < MAX_STACK_SIZE  ; ++i)
  {
      stack_0.push(i);
  }

  EXPECT_THROW(stack_0.push(0),std::runtime_error);
}

TEST_F(QueueTest, DequeWorks){
  EXPECT_EQ(*_q1.dequeue(),1);
  EXPECT_EQ(_q1.top(),2);
}


class RingBufferTest : public testing::Test {
protected:
  RingBufferTest() {
    ring_buffer.enqueue(1);
    ring_buffer.enqueue(2);
    ring_buffer.enqueue(3);
  }

  RingBuffer<int> ring_buffer = RingBuffer<int>(5);
};

TEST_F(RingBufferTest, EnqueueWorks) {
  ring_buffer.enqueue(4);
  ring_buffer.enqueue(5);
  EXPECT_EQ(ring_buffer.front(), 1);
  ring_buffer.enqueue(6); // This should overwrite the oldest element (1)
  EXPECT_EQ(ring_buffer.front(), 1);
}

