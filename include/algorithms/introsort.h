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
    void introsort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, int depthLimit)
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
            HeapSort<int> heapSort;
            heapSort.sort(start, end);
            return;
        }

        // Użyj sortowania szybkiego
        QuickSort<int> quickSort;
        quickSort.sort(start,end);
    }

public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        int depthLimit = 2 * std::log(std::distance(start, end));
        introsort(start, end, depthLimit);
    }
};

#endif //SORTING_ALGORITHMS_INTROSORT_H