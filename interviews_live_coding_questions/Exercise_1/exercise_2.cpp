// write a function that checks which bits of a byte or of and integer are 1

// The idea should be here to go through a loop and check every bit of a word and maybe store them in a vector?
// In every step of the loop we may use bitwise shift right so the value has the correct state

#include <vector>
#include <stdint.h>

std::vector<uint8_t> check_bits(uint8_t value)
{
    std::vector<uint8_t> res;

    while(value)
    {
        if(value & 1)
        {
            res.push_back(1);
        }

        value >>= 1 ; // shift right by 1 bit. x >>= 1 means "set x to itself shifted by one bit to the right". 
        // The expression evaluates to the new value of x after the shift
    }
    return res;
}
