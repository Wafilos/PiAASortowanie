#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>
#include <iterator>
#include <stack>
#include <algorithm>
#include <random>

template <typename T>
class QuickSort {
public:
    void sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
        if (begin >= end || std::distance(begin, end) < 2) return;

        std::stack<std::pair<decltype(begin), decltype(end)>> stack;
        stack.push({begin, end});

        std::random_device rd;
        std::mt19937 gen(rd());

        while (!stack.empty()) {
            auto [left, right] = stack.top();
            stack.pop();

            if (std::distance(left, right) < 2) continue;

            // Losowy pivot
            std::uniform_int_distribution<> dis(0, std::distance(left, right) - 1);
            auto pivot_it = left + dis(gen);
            std::iter_swap(pivot_it, right - 1); // przenieś pivot na koniec

            auto pivotValue = *(right - 1);
            auto i = left;

            for (auto j = left; j < right - 1; ++j) {
                if (*j < pivotValue) {
                    std::iter_swap(i, j);
                    ++i;
                }
            }
            std::iter_swap(i, right - 1); // przenieś pivot na właściwe miejsce

            // Zakresy do posortowania
            stack.push({left, i});
            stack.push({i + 1, right});
        }
    }
};

#endif // SORTING_ALGORITHMS_QUICKSORT_H

