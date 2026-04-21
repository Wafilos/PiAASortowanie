#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H
#include <vector>
#include <algorithm>

template <typename T>
class HeapSort
{
private:
    void heapify(std::vector<T>& arr, size_t n, size_t i)
    {
        size_t largest = i; // Inicjalizuj największy jako korzeń
        size_t left = 2 * i + 1; // lewy = 2*i + 1
        size_t right = 2 * i + 2; // prawy = 2*i + 2

        // Jeśli lewy jest większy niż korzeń
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // Jeśli prawy jest większy niż największy do tej pory
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // Jeśli największy nie jest korzeniem
        if (largest != i) {
            std::swap(arr[i], arr[largest]); // Zamień

            // Rekurencyjnie heapify poddrzewo dotknięte zamianą
            heapify(arr, n, largest);
        }
    }
public:
    void sort(std::vector<T>& arr)
    {
        size_t n = arr.size();

        // Budowanie kopca
        for (size_t i = n / 2; i > 0; ) {
            --i;
            heapify(arr, n, i);
        }
        // Wyodrębnianie elementów z kopca
        for (size_t i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

#endif //SORTING_ALGORITHMS_HEAPSORT_H