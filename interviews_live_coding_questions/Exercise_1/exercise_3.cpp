// reverse string in place
// The approach here should be that we do swap of the values fro the left to the right

#include <string>

void reverse_string(std::string& str)
{
    int left = 0;
    int right = str.length() - 1;

    while (left < right) {
        std::swap(str[left], str[right]);
        left++;
        right--;
    }
}