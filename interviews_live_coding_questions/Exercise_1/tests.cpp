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

// Function declaration
int count_minimum_operations(const std::string password);

// Tests for min_operations_to_similar_password
TEST(MinOperationsToSimilarPasswordTest, EqualVowelsAndConsonants) {
    EXPECT_EQ(count_minimum_operations("hack"), 1);
}

TEST(MinOperationsToSimilarPasswordTest, MoreVowels) {
    EXPECT_EQ(count_minimum_operations("aeiou"), -1);
}

TEST(MinOperationsToSimilarPasswordTest, MoreConsonants) {
    EXPECT_EQ(count_minimum_operations("bcdfg"), -1);
}

TEST(MinOperationsToSimilarPasswordTest, AlreadySimilar) {
    EXPECT_EQ(count_minimum_operations("aabb"), 0);
}

TEST(MinOperationsToSimilarPasswordTest, EmptyString) {
    EXPECT_EQ(count_minimum_operations(""), -1);
}


TEST(MinOperationsToSimilarPasswordTest, RandomTest) {
    EXPECT_EQ(count_minimum_operations("cgdpzgae"), 2);
}

TEST(MinOperationsToSimilarPasswordTest, LongBalancedPassword) {
    EXPECT_EQ(count_minimum_operations("abababababababababab"), 0);
}

TEST(MinOperationsToSimilarPasswordTest, LongUnbalancedPasswordMoreVowels) {
    EXPECT_EQ(count_minimum_operations("aaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbb"), 1);
}

TEST(MinOperationsToSimilarPasswordTest, LongUnbalancedPasswordMoreConsonants) {
    EXPECT_EQ(count_minimum_operations("bbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaa"), -1);
}

TEST(MinOperationsToSimilarPasswordTest, SingleCharacterVowel) {
    EXPECT_EQ(count_minimum_operations("a"), -1);
}

TEST(MinOperationsToSimilarPasswordTest, SingleCharacterConsonant) {
    EXPECT_EQ(count_minimum_operations("b"), -1);
}

TEST(MinOperationsToSimilarPasswordTest, LongPasswordAllVowels) {
    EXPECT_EQ(count_minimum_operations("aeiouaeiouaeiouaeiouaeiouaeiou"), -1);
}

TEST(MinOperationsToSimilarPasswordTest, LongPasswordAllConsonants) {
    EXPECT_EQ(count_minimum_operations("bcdfghjklmnpqrstvwxyzbcdfghjklmnpqrstvwxyz"), -1);
}

TEST(MinOperationsToSimilarPasswordTest, AllCharactersConvertibleToVowels) {
    EXPECT_EQ(count_minimum_operations("bcdfgh"), 3);
}

TEST(MinOperationsToSimilarPasswordTest, AllCharactersConvertibleToConsonants) {
    EXPECT_EQ(count_minimum_operations("aeiou"), 2);
}

TEST(MinOperationsToSimilarPasswordTest, MixedCaseWithComplexPattern) {
    EXPECT_EQ(count_minimum_operations("abcdxyzmnopqrs"), -1);
}

// Function declaration
long maximum_revenue(int customers, std::vector<int> quantity);

// // Tests for min_operations_to_similar_password
// TEST(MaximizeRevenueTest, Test0) {
//     EXPECT_EQ(maximum_revenue(4,{1,2,4}), 11);
// }

// TEST(MaximizeRevenueTest, Test1) {
//     EXPECT_EQ(maximum_revenue(6,{10, 10, 8, 9, 1}), 55);
// }

// TEST(MaximizeRevenueTest, Test2) {
//     EXPECT_EQ(maximum_revenue(6,{1, 1, 1, 1, 1,1}), 6);
// }


TEST(MaximizeRevenueTest, Test2) {
    EXPECT_EQ(maximum_revenue(13,{10,7,5,3,1}), 80);
}