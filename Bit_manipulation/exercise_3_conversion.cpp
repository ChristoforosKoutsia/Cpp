/*
Write a function to determine the number of bits you would need to flip to convert
integer A to integer B.
EXAMPLE
Input: 29 (or: 11101), 15 (or: 01111)
Output: 2
*/

// the solution could be that we just do an Xor between the two numbers and 
// the new number will reveal how many flips we want ( by just counting the 1s)

#include <stdint.h>
int conversion(int a, int b)
{
    int mask = (a ^ b); // xor and take exactly the 1s when the two bits are diffrent

    int count_flips = 0;

    for (int i = 0 ; i < sizeof(int)*8 ; ++i )
    {
        uint8_t bit = mask & ( 1 << i);
        
        if (bit) ++count_flips;
    }
    return count_flips;
}