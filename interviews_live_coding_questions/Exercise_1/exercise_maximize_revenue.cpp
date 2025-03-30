// // This exercise was part of coding interview
// // There are n types of items in shop, where the numberof items of type
// // i is denoted by quantity[i]. The price of the items is determined dynamically , where
// // the price of the ith item is equal to the remaining number of items of type i.
// // There are m customers in line to buy the items from the shop, and each customer will buy exactly one 
// // item of any type

// // The shopkeeper being greedy , tries to sell the item in a way that maximises the revenue.
// // find the maximum amount the shopkeeper can earn by selling exactly m items to the customers optimally


// // The idea could be the following
// // 1. sort the array
// // 2. Begin to sell the first product until it becomes cheaper than the second
// // 3. Move on until the customers are finished

// The priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, 
// at the expense of logarithmic insertion and extraction.

// A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top().

// Working with a priority_queue is similar to managing a heap in some random access container, with the benefit of not being able to accidentally invalidate the heap.

#include <vector>
#include <algorithm>
#include <queue>

long maximum_revenue(int customers, std::vector<int> quantity)
{
    // Max heap to store quantities in descending order
    std::priority_queue<int> max_heap(quantity.begin(), quantity.end());

    long max_revenue = 0;

    // Serve customers one by one
    while (customers > 0 && !max_heap.empty()) {
        // Get the item with the highest quantity
        int current_quantity = max_heap.top();
        max_heap.pop();

        // Add its price (equal to its quantity) to the revenue
        max_revenue += current_quantity;

        // Decrease the quantity and push it back if still available
        if (current_quantity > 1) {
            max_heap.push(current_quantity - 1);
        }

        customers--;
    }

    return max_revenue;
}
