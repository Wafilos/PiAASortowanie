#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H
#include <vector>
#include <algorithm> // potrzebne do std::make_heap i std::pop_heap

template <typename T>
class Heap
{
  public:
    // Konstruktor – zapisujemy przekazany zakres w prywatnych polach, a następnie budujemy kopiec.
    Heap(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
      : heap_begin(start), heap_end(end)
    {
        std::make_heap(heap_begin, heap_end);
    }

    void removeMax();
    std::size_t size();
    bool empty();
    T& operator[](int index);

  private:
    // Prywatne pola przechowujące zakres – dzięki nim możemy modyfikować (skracając) aktualny obszar kopca.
    typename std::vector<T>::iterator heap_begin;
    typename std::vector<T>::iterator heap_end;
};


template <typename T>
void Heap<T>::removeMax()
{
    if (empty()) return; // Jeśli kopiec jest pusty, zakończ

    // Zamień korzeń (największy element) z ostatnim elementem
    std::iter_swap(heap_begin, heap_end - 1);

    // Zmniejsz zakres kopca
    --heap_end;

    // Ponowne zbudowanie kopca dla pozostałego zakresu
    std::make_heap(heap_begin, heap_end);
}


template <typename T>
std::size_t Heap<T>::size()
{
    // Rozmiar kopca to różnica pomiędzy aktualnym końcem a początkiem zakresu.
    return heap_end - heap_begin;
}

template <typename T>
bool Heap<T>::empty()
{
    // Kopiec jest pusty, gdy początek zakresu zrówna się z końcem.
    return heap_begin == heap_end;
}

template <typename T>
T& Heap<T>::operator[](int index)
{
    // Uwzględniamy, że indeksowanie ma być od 1 – więc przeliczamy na indeks 0-indeksowany.
    return heap_begin[index - 1];
}


// sortowanie przez kopcowanie

template <typename T>
class HeapSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        Heap<T> heap(start, end);
        while (!heap.empty()){
            heap.removeMax();
        }
    }
};

#endif //SORTING_ALGORITHMS_HEAPSORT_H