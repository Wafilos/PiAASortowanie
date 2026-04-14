#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\quicksort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\mergesort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\shellsort.h"
#include <fstream>

using namespace std;
using namespace chrono;

// Funkcja do generowania losowej tablicy
std::vector<int> generateRandomArray(size_t size, float percentage) {
    std::vector<int> array(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-10000, 10000);

    size_t sorted = static_cast<size_t>(size * percentage);

    // Wypełnij cały wektor losowymi liczbami
    for (size_t i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }

    // Posortuj tylko część
    std::sort(array.begin(), array.begin() + sorted);

    return array;
}

std::vector<int> reverseSortedArray(const std::vector<int>& arr) {
    std::vector<int> tmp = arr;
    std::sort(tmp.begin(), tmp.end());
    std::reverse(tmp.begin(), tmp.end());
    return tmp;
}

void quicksort(vector<int>& array) {
    QuickSort<int> quickSort;
    quickSort.sort(array.begin(), array.end() - 1);
}

void mergesort(vector<int>& array) {
    MergeSort<int> mergeSort;
    mergeSort.sort(array.begin(), array.end() - 1);

}
void shellsort(vector<int>& array) {
    ShellSort<int> shellSort;
    shellSort.sort(array.begin(), array.end() - 1);
}

// Funkcja do mierzenia czasu wykonania
template<typename Func>
double measureExecutionTime(vector<int>& array, Func sortingFunction) {
    auto start = high_resolution_clock::now();
    sortingFunction(array);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

int main() {
    vector<size_t> sizes = {10000, 50000, 100000, 500000, 1000000};
    int numExperiments = 100;
    vector<float> percenteges = {0, 0.25, 0.50, 0.75, 0.90, 0.99, 0.997};

    for (size_t size : sizes) {

        ofstream outputFile("results_" + to_string(size) + ".txt");
        if (!outputFile.is_open()) {
            cerr << "Nie można otworzyć pliku dla rozmiaru: " << size << endl;
            continue;
        }

        std::cout << "\nRozmiar tablicy: " << size << endl;

        for (float percentage : percenteges){
            double totalTimeQuickSort = 0.0;
            double totalTimeMergeSort = 0.0;
            double totalTimeIntroSort = 0.0;

             for(int i = 0; i < numExperiments; ++i){
                vector<int> array = generateRandomArray(size,percentage);

                vector<int> arrayCopy4 = array; // Kopia tablicy
                totalTimeQuickSort += measureExecutionTime(arrayCopy4, quicksort);
                
                vector<int> arrayCopy5 = array; // Kopia tablicy
                totalTimeMergeSort += measureExecutionTime(arrayCopy5, mergesort);
                
                vector<int> arrayCopy6 = array; // Kopia tablicy
                totalTimeIntroSort += measureExecutionTime(arrayCopy6, shellsort);
                
            }
            outputFile << "quciksort;"<<percentage<<";"<< totalTimeQuickSort << ";sekundy" << endl;
            outputFile << "mergesort;"<<percentage<<";"<< totalTimeMergeSort << ";sekundy" << endl;
            outputFile << "shellsort;"<<percentage<<";"<< totalTimeIntroSort << ";sekundy" << endl;

        }

        double totalTimeShellRev = 0, totalTimeQuickRev = 0, totalTimeMergrRev = 0;
        std::cout << "  Tablica posortowana malejąco:\n";
        for (int trial = 0; trial < numExperiments; trial++) {
            std::vector<int> arr = generateRandomArray(size, 0);
            arr = reverseSortedArray(arr);

            std::vector<int> arrShell = arr;
            std::vector<int> arrQuick = arr;
            std::vector<int> arrMerge = arr;

            totalTimeShellRev += measureExecutionTime(arrShell, shellsort);
            totalTimeQuickRev += measureExecutionTime(arrQuick, quicksort);
            totalTimeMergrRev += measureExecutionTime(arrMerge, mergesort);
        }
        outputFile << "quciksort;"<<"reversed"<<";"<< totalTimeQuickRev<< ";sekundy" << endl;
        outputFile << "mergesort;"<<"reversed"<<";"<< totalTimeMergrRev<< ";sekundy" << endl;
        outputFile << "shellsort;"<<"reversed"<<";"<< totalTimeShellRev<< ";sekundy" << endl;

        outputFile.close();
        std::cout<<"Zakończono dla rozmiaru: "<<size<<endl;
    }

    return 0;
}