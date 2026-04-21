#ifndef SORTING_ALGORITHMS_INTROSORT_H
#define SORTING_ALGORITHMS_INTROSORT_H
#include <vector>
#include <cmath>
#include "quicksort.h"
#include "heapsort.h"
#include "insertsort.h"

// sortowanie introspektywne

template <typename T>
class IntroSort
{
private:
    void introsort(std::vector<T>& arr, typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, int depthLimit)
    {
        if (std::distance(start, end) <= 1)
            return;
        
        // Użyj sortowania przez wstawianie dla małych podzbiorów
        if (std::distance(start, end) <= 20)
        {
            InsertSort<T> insertSort;
            insertSort.sort(start, end);
            return;
        }

        if (depthLimit == 0)
        {
            // Gdy osiągnięto limit rekurencji, użyj sortowania kopcowego
            HeapSort<T> heapSort;
            heapSort.sort(start, end);
            return;
        }

        // Użyj sortowania szybkiego
        QuickSort<T> quickSort;
        quickSort.sort(arr, std::distance(arr.begin(), start), std::distance(arr.begin(), end) - 1);
    }

public:
    void sort(std::vector<T>& arr, typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        int depthLimit = 2 * std::log(std::distance(start, end));
        introsort(arr, start, end, depthLimit);
    }
};

#endif //SORTING_ALGORITHMS_INTROSORT_H