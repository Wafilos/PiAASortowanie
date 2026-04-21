#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include <vector>

// sortowanie przez scalanie

template <typename T>
class MergeSort
{
private: 
    // Funkcja scalająca dwie posortowane części wektora
    void merge(std::vector<T>& array, typename std::vector<T>::iterator start, typename std::vector<T>::iterator mid, typename std::vector<T>::iterator end)
    {
        auto n1 = std::distance(start, mid);
        auto n2 = std::distance(mid, end);

        std::vector<T> L(start, mid);
        std::vector<T> R(mid, end);

        for(size_t i=0 ; i < n1; ++i)
            L[i] = *(start + i);
        for(size_t j=0 ; j < n2; ++j)
            R[j] = *(mid + 1 + j);

        size_t i = 0, j = 0;
        auto k = start;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                *k = L[i];
                i++;
            }
            else {
                *k = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            *k = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            *k = R[j];
            j++;
            k++;
        }

    }
public:
    void sort(std::vector<T>& array, typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (std::distance(start, end) <= 1)
            return;

        auto mid = start + std::distance(start, end) / 2;

        sort(array, start, mid);
        sort(array, mid + 1, end);

        merge(array, start, mid, end);

    };


};
#endif //SORTING_ALGORITHMS_MERGESORT_H
