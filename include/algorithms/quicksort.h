#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>
#include <iterator>
#include <stack>
#include <algorithm>
#include <random>
#include <cassert>

template <typename T>
class QuickSort {
private:
    size_t partition(std::vector<T>& arr, size_t low, size_t high) {
  
    // choose the pivot
    T pivot = arr[high];
  
    // undex of smaller element and indicates 
    // the right position of pivot found so far
    size_t i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements on left side. Elements from low to 
    // i are smaller after every iteration
    assert(low >= 0);
    assert(high >= 0);
    assert(high < arr.size());
    for (size_t j = low; j < high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    // move pivot after smaller elements and
    // return its position
    std::swap(arr[i + 1], arr[high]);  
    return i + 1;
}
public:
    void sort(std::vector<T>& arr, size_t low, size_t high) {
        if (low >= high) return;

        size_t pi = partition(arr, low, high);

        if (pi > 0) { // ✅ prevents underflow
        sort(arr, low, pi - 1);
        }

        sort(arr, pi + 1, high);
    }  
};



#endif // SORTING_ALGORITHMS_QUICKSORT_H

