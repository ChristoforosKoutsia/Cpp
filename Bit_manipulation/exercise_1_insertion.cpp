// This comes from the book Cracking the coding interview
/*You are given two 32-bit numbers, N and M, and two bit positions, i and
j. Write a method to insert M into N such that M starts at bit j and ends at bit i. You
can assume that the bits j through i have enough space to fit all of M. That is, if
M = 10011, you can assume that there are at least 5 bits between j and i. You would not, for
example, have j = 3 and i = 2, because M could not fully fit between bit 3 and bit 2.*/

#include <stdint.h>

int32_t insert_bit_ranges(int32_t M, int32_t N, uint8_t i ,uint8_t j)
{

 // The idea is as below
 // 1. we clear from the ith to jth bit of N ( this is crucial in order to use or operation)
 // 2. we shift to left M ith bits so it is aligned with M
 // 3. we do M | N

   int32_t mask = ~(0); // all ones 32 bit
   
   uint8_t begin_index = i;
   uint8_t end_index = j;
   if ( i > j) 
   {
      begin_index = j;
      end_index = i;
   }

  M = M << begin_index;
   
   while (begin_index <= end_index)
   {
      mask = mask & (~(1<<begin_index)); // we clear the ith bit in every iteration
      ++begin_index;
   }
   

   int32_t cleared_N  = mask & N;
   

   int32_t result = M | cleared_N; 

   // finally we have the result
   return ( result );
}