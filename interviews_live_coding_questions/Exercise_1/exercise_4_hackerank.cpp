/*
Given an array of integers, calculate the ratios of its elements that are positive, negative, and zero. Print the decimal value of each fraction on a new line with  places after the decimal.

Note: This challenge introduces precision problems. The test cases are scaled to six decimal places, though answers with absolute error of up to  are acceptable.

Example

There are  elements, two positive, two negative and one zero. Their ratios are ,  and . Results are printed as:

0.400000
0.400000
0.200000
Function Description

Complete the plusMinus function in the editor below.

plusMinus has the following parameter(s):

int arr[n]: an array of integers
Print
Print the ratios of positive, negative and zero values in the array. Each value should be printed on a separate line with  digits after the decimal. The function should not return a value.

Input Format

The first line contains an integer, , the size of the array.
The second line contains  space-separated integers that describe .

Constraints



Output Format

Print the following  lines, each to  decimals:

proportion of positive values
proportion of negative values
proportion of zeros
Sample Input

STDIN           Function
-----           --------
6               arr[] size n = 6
-4 3 -9 0 4 1   arr = [-4, 3, -9, 0, 4, 1]
Sample Output

0.500000
0.333333
0.166667
Explanation

There are  positive numbers,  negative numbers, and  zero in the array.
The proportions of occurrence are positive: , negative:  and zeros: 
*/
#include <vector>
#include <iostream>

void plusMinus(std::vector<int> arr) {
    // the idea here is to get the total size then go through the
    // vector and store its value accordingly. This will result in complexity
    // O(n)
    
    int total_size = arr.size();
    int positives = 0;
    int negatives = 0;
    int zeros = 0;
    
    for (auto it = arr.begin(); it < arr.end() ; ++it )
    {
        if ( *it > 0 ){
            positives++;
        }
        else if (*it < 0 ){
            negatives++;
        }
        else{
            zeros++;
        }
    }

    std::cout<<std::setprecision(6)<<std::fixed;
    std::cout<<static_cast<float>(positives)/total_size<<std::endl;
    std::cout<<static_cast<float>(negatives)/total_size<<std::endl;
    std::cout<<static_cast<float>(zeros)/total_size<std::<std::endl;

}