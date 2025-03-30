/*
Here I will try to solve all the technical coding examples found on internet
*/

// #############################################//
/*
Problem 1: Finding the Second Highest Number in an Array
Problem Statement:
You are given an array of integers. Write a function to find the second highest number in the array.

Requirements:

The array can contain both positive and negative numbers.
The array may have duplicate values, but the second highest number must be distinct from the highest.
If the array does not have at least two distinct numbers, return an appropriate value or error message.
*/
#include <algorithm>
#include <vector>
#include <iostream>

int find_the_second_largest(std::vector<int> arr)
{
    if (arr.size() < 2) throw std::runtime_error("Vector is empty\n");

    int max_value = arr[0];
    int second_max = arr[0];

    for (int i = 1 ; i < arr.size() ; ++i)
    {
        if ( arr[i] == max_value) continue;
        if ( arr[i] > max_value) {
            second_max = max_value;
            max_value = arr[i];
        }
        else if ( second_max == max_value) second_max = arr[i];
        else second_max = std::max(arr[i],second_max);
    }

    if (second_max != max_value) return second_max;
    else throw std::runtime_error("No distinct values in the given array\n");
}

/*Problem 2 
You are given the head of a singly linked list and an integer k (obtained from standard input). 
Write a function to rotate the list to the right by k places.
E.g [1,2,3,4,5], k=2 -> [4,5,1,2,3]
*/

// Solution 
// if k is dividable with the length of the list then we can just return the linked list
// else we should rotate it by n = k % length times
// for the trivial situation where we need to do it 1 time we just need to do the following
// find the tail and assign tail->next = head and then find the new last element 
// and new_last_element->next = nullptr;


struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* rotate_linked_list(ListNode* head, int k)
{

    ListNode *tail = head;
    int length = 0 ;

    while (tail->next != nullptr)
    {
        tail = tail->next;
        length++;
    }

    int num_rotates = k % length;

    if ( num_rotates == 0) return head;

    while (num_rotates > 0)
    {
        
    }

    
}