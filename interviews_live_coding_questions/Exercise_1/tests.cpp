#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdint.h>

// Include the headers or declarations for the functions to test
uint32_t sum_of_dividable_numbers();
std::vector<uint8_t> check_bits(uint8_t value);
void reverse_string(std::string& str);

// Test for sum_of_dividable_numbers
TEST(SumOfDividableNumbersTest, CorrectSum) {
    EXPECT_EQ(sum_of_dividable_numbers(), 192517500);
}

// Test for check_bits
TEST(CheckBitsTest, AllBitsZero) {
    std::vector<uint8_t> expected = {};
    EXPECT_EQ(check_bits(0), expected);
}

TEST(CheckBitsTest, AllBitsOne) {
    std::vector<uint8_t> expected = {1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(check_bits(255), expected);
}

TEST(CheckBitsTest, SingleBitSet) {
    std::vector<uint8_t> expected = {1};
    EXPECT_EQ(check_bits(1), expected);

    expected = {1};
    EXPECT_EQ(check_bits(128), expected);
}

TEST(CheckBitsTest, MultipleBitsSet) {
    std::vector<uint8_t> expected = {1, 1};
    EXPECT_EQ(check_bits(3), expected);

    expected = {1, 1, 1};
    EXPECT_EQ(check_bits(7), expected);
}

// Test for reverse_string
TEST(ReverseStringTest, EmptyString) {
    std::string str = "";
    reverse_string(str);
    EXPECT_EQ(str, "");
}

TEST(ReverseStringTest, SingleCharacter) {
    std::string str = "a";
    reverse_string(str);
    EXPECT_EQ(str, "a");
}

TEST(ReverseStringTest, EvenLengthString) {
    std::string str = "abcd";
    reverse_string(str);
    EXPECT_EQ(str, "dcba");
}

TEST(ReverseStringTest, OddLengthString) {
    std::string str = "abcde";
    reverse_string(str);
    EXPECT_EQ(str, "edcba");
}

TEST(ReverseStringTest, PalindromeString) {
    std::string str = "racecar";
    reverse_string(str);
    EXPECT_EQ(str, "racecar");
}
