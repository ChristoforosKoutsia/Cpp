// write a function to sum all the positive integers including 35000 which are divided by 5 or 7

// The key idea here is NOT to use any if statement and just use two for loops and increment the i by 5 and 7 
// everytime accordignly. However, we need to make sure that we do not count the numbers that are divisible by both 5 and 7 twice. So we need to subtract the numbers that are divisible by 35.
// By just adding a new for loop that increments i by 35 we can achieve this.
#include <stdint.h>

uint32_t sum_of_dividable_numbers()
{
    uint32_t res = 0;

    for (int i = 0 ; i <= 35000 ; i+= 5)
    {
        res += i;
    }

    for (int i = 0 ; i <= 35000 ; i+= 7)
    {
        res += i;
    }

    for (int i = 0; i <= 35000; i += 35)
    {
        res -= i;
    }

    // res = 0;
    // for (int i = 0 ; i <= 35000 ; ++i)
    // {
    //     if (i % 5 == 0 || i % 7 == 0){
    //         res += i;
    //     }
        
    // }

    return res;
}
