#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include <vector>

// sortowanie przez scalanie

template <typename T>
class MergeSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if(std::distance(start, end)<=1)
            return; // już zostało posortowane
        auto mid = start + std::distance(start, end)/2; // Znalezienie środka przedziału
        sort(start, mid); // Sortowanie lewej połowy
        sort(mid, end); // Sortowanie prawej połowy
        merge(start, mid, end); // Scalanie posortowanych połówek

    };

private: 
    // Funkcja scalająca dwie posortowane części wektora
    void merge(typename std::vector<T>::iterator start, typename std::vector<T>::iterator mid, typename std::vector<T>::iterator end){
        std::vector<T> left(start,mid); // Kopiowanie lewej połowy
        std::vector<T> right(mid,end); // Kopiowanie prawej połowy

        auto itLeft = left.begin(), itRight = right.begin();
        auto it = start;

        while(itLeft != left.end() && itRight != right.end()){
            if(*itLeft <= *itRight)
                *it++ = *itLeft++;
            else
                *it++ = *itRight++;
        }
        // Dodanie pozostałych elementów z lewej części (jeśli są)
        while(itLeft!= left.end())
            *it++ = *itLeft++;
        // Dodanie pozostałych elementów z prawej części (jeśli są)
        while(itRight!= right.end())
            *it++ = *itRight++;

    }
};
#endif //SORTING_ALGORITHMS_MERGESORT_H
