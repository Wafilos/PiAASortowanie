#ifndef SORTING_ALGORITHMS_SHELLSORT_H
#define SORTING_ALGORITHMS_SHELLSORT_H
#include <vector>

// sortowanie Shella

template <typename T>
class ShellSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        // Oblicz liczbę elementów do posortowania
        auto n = std::distance(start, end);
        
        // Ustalanie początkowej wartości luki (gap)
        for (auto gap = n / 2; gap > 0; gap /= 2)
        {
            // Dla każdego elementu zaczynając od 'gap'
            for (auto i = gap; i < n; i++)
            {
                // Przechowaj wartość aktualnego elementu
                auto temp = *(start + i);
                auto j = i;
                
                // Przesuwanie elementów, które są większe od temp, o gap do przodu
                while (j >= gap && *(start + j - gap) > temp)
                {
                    *(start + j) = *(start + j - gap);
                    j -= gap;
                }
                
                // Wstaw temp na właściwe miejsce
                *(start + j) = temp;
            }
        }
    };
};
#endif //SORTING_ALGORITHMS_SHELLSORT_H
