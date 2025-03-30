/*
• Find the maximum of two numbers without using any if-else statements, branching, or direct comparisons.

• Reverse bits of an integer.

• Count the number of sets of bits in a given bit stream.

• Implement a Count Leading Zero (CLZ) bit algorithm, but don't use the assembler instruction. 
  What optimizations to make it faster? What are some uses of CLZ?

• Write a function that swaps the highest bits in each nibble of the byte

• Given an 8-bit pattern, find the pattern in the bitstream and return the bit offset.

• What is the size of the integer variable on 32bit and 64bit machines?

• Write a function that swaps the highest bits in each nibble of the byte.

• Write a function to convert Big Endian to Little Endian System.

How to read a 128-bit timestamp on 64-bit architecture?*/
#include <stdint.h>

int reverse_bits (uint8_t a)
{
    for (int i = 0 ; i < 8 ; ++i)
    {
        uint8_t mask = 0xFF;
        // if current bit is 1
        if ((a & (1 << i)))
        {
            // lets determine the correct mask ( clear ith bit)
            mask = mask  & (~(1 << i));

            // now do & in the a 
            a &= mask;
            
        }
    }

}