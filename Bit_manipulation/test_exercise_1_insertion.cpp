#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdint.h>

// Include the headers or declarations for the functions to test
int32_t insert_bit_ranges(int32_t M, int32_t N, uint8_t i ,uint8_t j);


// Test for sum_of_dividable_numbers
TEST(InsertBitsTest, Test0) {
    EXPECT_EQ(insert_bit_ranges(0b10011,0b01001111100,2,6), 0b01001001100);
}

TEST(InsertBitsTest, Test1) {
    EXPECT_EQ(insert_bit_ranges(0b10011,0b10000000000,2,6), 0b10001001100);
}

int longest_1s_sequence(int n);

