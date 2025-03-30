#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdint.h>

// Include the headers or declarations for the functions to test
int find_the_second_largest(std::vector<int> arr);

// Test case 1: General case with distinct numbers
TEST(SecondLargest, GeneralCase) {
    EXPECT_EQ(find_the_second_largest({3, 1, 4, 2, 5}), 4);
}

// Test case 2: Array with duplicate numbers
TEST(SecondLargest, WithDuplicates) {
    EXPECT_EQ(find_the_second_largest({3, 3, 5, 5, 2}), 3);
}

// // Test case 3: Array with all identical numbers
// TEST(SecondLargest, AllIdentical) {
//     EXPECT_EQ(find_the_second_largest({1, 1, 1, 1}), -1); // Assuming -1 indicates no second largest
// }

// Test case 4: Array with negative and positive numbers
TEST(SecondLargest, NegativeAndPositive) {
    EXPECT_EQ(find_the_second_largest({-2, -1, -3, 0, 4}), 0);
}

// // Test case 5: Array with fewer than two elements
// TEST(SecondLargest, NotEnoughElements) {
//     EXPECT_EQ(find_the_second_largest({1}), -1); // Assuming -1 indicates no second largest
// }

