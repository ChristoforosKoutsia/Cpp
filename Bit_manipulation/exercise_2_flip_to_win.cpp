/*Flip Bit to Win: You have an integer and you can flip exactly one bit from a 0 to a 1. Write code to
find the length of the longest sequence of Is you could create.
EXAMPLE
Input: 1775 (or: 11011101111)
Output: 8
*/ // From cracking the coding interview book

#include <stdint.h>
#include <algorithm>

int longest_1s_sequence(int n)
{
    // initialize the current sub sum and the previous sub sum
    int current_sub_sum = 0;
    int previous_sub_sum = 0;
    int longest_sequence = 0;

    // iterate through bits

    for (int i =0 ; i < (sizeof(n)) * 8 ; ++i)
    {
        // retrieve current bit
        int bit = n & (1 << i);

        if (bit)
        {
            ++current_sub_sum;
        }
        else{
            longest_sequence = std::max(longest_sequence,previous_sub_sum + current_sub_sum + 1);
            previous_sub_sum = current_sub_sum;

            // clear current sub_sum
            current_sub_sum = 0;
        }

    }

    return longest_sequence;
}