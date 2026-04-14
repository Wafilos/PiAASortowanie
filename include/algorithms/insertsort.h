#ifndef SORTING_ALGORITHMS_INSERTSORT_H
#define SORTING_ALGORITHMS_INSERTSORT_H
#include <vector>

// sortowanie przez wstawianie

template <typename T>
class InsertSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        for (auto i = start + 1; i != end; ++i)  // Przechodzimy przez wektor od drugiego elementu do końca
        {
            T key = *i; // Klucz (wartość bieżącego elementu)
            auto j = i - 1; // Wskaźnik do poprzedniego elementu

            while (j >= start && key < *j)   // Przesuwamy elementy w lewo, jeśli są większe niż klucz
            {
                *(j + 1) = *j; // Przesunięcie elementu w prawo
                --j; // Przesunięcie wskaźnika w lewo
            }

            *(j + 1) = key; // Wstawienie klucza na właściwe miejsce
        }
    };
};

#endif //SORTING_ALGORITHMS_INSERTSORT_H
