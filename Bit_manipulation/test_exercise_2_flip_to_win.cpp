#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdint.h>

// Include the headers or declarations for the functions to test
int longest_1s_sequence(int n);


// Test for sum_of_dividable_numbers
TEST(FlipToWin, Test0) {
    EXPECT_EQ(longest_1s_sequence(0b11011101111), 8);
}

// TEST(FlipToWin, Test1) {
//     EXPECT_EQ(longest_1s_sequence(0b10011,0b10000000000,2,6), 0b10001001100);
// }

// int longest_1s_sequence(int n);

