#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include <vector>

// sortowanie przez scalanie

template <typename T>
class MergeSort
{
private:
    std::vector<T> tempBuffer;
    
    // Optimized merge function that reuses a temporary buffer
    void merge(std::vector<T>& array, size_t start, size_t mid, size_t end)
    {
        size_t i = start;
        size_t j = mid + 1;
        size_t k = start;

        // Copy elements to temp buffer
        for (size_t idx = start; idx <= end; ++idx) {
            tempBuffer[idx] = array[idx];
        }

        i = start;
        j = mid + 1;
        k = start;

        // Merge back into array
        while (i <= mid && j <= end) {
            if (tempBuffer[i] <= tempBuffer[j]) {
                array[k++] = tempBuffer[i++];
            } else {
                array[k++] = tempBuffer[j++];
            }
        }

        // Copy remaining elements
        while (i <= mid) {
            array[k++] = tempBuffer[i++];
        }

        while (j <= end) {
            array[k++] = tempBuffer[j++];
        }
    }

    void sortHelper(std::vector<T>& array, size_t start, size_t end)
    {
        if (start >= end)
            return;

        size_t mid = start + (end - start) / 2;

        sortHelper(array, start, mid);
        sortHelper(array, mid + 1, end);

        merge(array, start, mid, end);
    }

public:
    void sort(std::vector<T>& array, typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (std::distance(start, end) <= 1)
            return;

        size_t size = std::distance(start, end);
        size_t startIdx = std::distance(array.begin(), start);
        size_t endIdx = startIdx + size - 1;

        // Allocate temporary buffer once
        tempBuffer.resize(array.size());

        sortHelper(array, startIdx, endIdx);

        tempBuffer.clear();
        tempBuffer.shrink_to_fit();
    }
};

#endif //SORTING_ALGORITHMS_MERGESORT_H
