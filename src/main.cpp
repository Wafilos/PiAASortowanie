#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\quicksort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\mergesort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\shellsort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms/introsort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\shellsort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\heapsort.h"
#include <fstream>

using namespace std;
using namespace chrono;

void averageRaitings(vector<double> array) {
    double sum = 0.0;
    for (const auto& rating : array) {
        sum += rating;
    }
    double average = sum / array.size();
    cout << "Average rating: " << average << "\n";
}

void medianRaitings(vector<double> array) {
    sort(array.begin(), array.end());
    double median;
    size_t n = array.size();
    if (n % 2 == 0) {
        median = (array[n / 2 - 1] + array[n / 2]) / 2.0;
    } else {
        median = array[n / 2];
    }
    cout << "Median rating: " << median << "\n";
}

void mergesort(vector<double>& array) {
    MergeSort<double> mergeSort;
    mergeSort.sort(array, array.begin(), array.end());

}
void shellsort(vector<double>& array) {
    ShellSort<double> shellSort;
    shellSort.sort(array.begin(), array.end());
}

void heapsort(vector<double>& array) {
    HeapSort<double> heapSort;
    heapSort.sort(array);
}


template<typename T, typename Func>
double measureExecutionTime(vector<T> array, Func sortingFunction) {
    auto start = high_resolution_clock::now();
    sortingFunction(array);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

int main() {
    ifstream input("title.ratings.filtered.tsv");
    if (!input) {
        cerr << "Error opening file\n";
        return 1;
    }
    vector<double> allData;
    string line;
    // Pomijamy nagłówek
    getline(input, line);
    while (getline(input, line)) {
        size_t firstTab = line.find('\t');
        size_t secondTab = line.find('\t', firstTab + 1);

        size_t start = firstTab + 1;
        size_t length = secondTab - start;

        double rating = stod(line.substr(start, length));
        allData.push_back(rating);
    }
    vector<double> data10k, data100k, data500k, data1M, dataMax;

    if (allData.size() >= 10000)
        data10k.assign(allData.begin(), allData.begin() + 10000);

    if (allData.size() >= 100000)
        data100k.assign(allData.begin(), allData.begin() + 100000);

    if (allData.size() >= 500000)
        data500k.assign(allData.begin(), allData.begin() + 500000);

    if (allData.size() >= 1000000)
        data1M.assign(allData.begin(), allData.begin() + 1000000);
    
    dataMax = allData;
    cout << "Sorting 10k ratings...\n";
    cout << "time taken for MergeSort: " << measureExecutionTime(data10k, mergesort) << " seconds\n";
    cout << "time taken for ShellSort: " << measureExecutionTime(data10k, shellsort) << " seconds\n";
    cout << "time taken for HeapSort: " << measureExecutionTime(data10k, heapsort) << " seconds\n";
    cout << "Average and median for 10k ratings:\n";
    averageRaitings(data10k);
    medianRaitings(data10k);
    cout<< "\nSorting 100k ratings...\n";
    cout << "time taken for MergeSort: " << measureExecutionTime(data100k, mergesort) << " seconds\n";
    cout << "time taken for ShellSort: " << measureExecutionTime(data100k, shellsort) << " seconds\n";
    cout << "time taken for HeapSort: " << measureExecutionTime(data100k, heapsort) << " seconds\n";
    cout << "Average and median for 100k ratings:\n";
    averageRaitings(data100k);
    medianRaitings(data100k);
    cout<< "\nSorting 500k ratings...\n";
    cout << "time taken for MergeSort: " << measureExecutionTime(data500k, mergesort) << " seconds\n";
    cout << "time taken for ShellSort: " << measureExecutionTime(data500k, shellsort) << " seconds\n";
    cout << "time taken for HeapSort: " << measureExecutionTime(data500k, heapsort) << " seconds\n";
    cout << "Average and median for 500k ratings:\n";
    averageRaitings(data500k);      
    medianRaitings(data500k);
    cout<< "\nSorting 1M ratings...\n";
    cout << "time taken for MergeSort: " << measureExecutionTime(data1M, mergesort) << " seconds\n";
    cout << "time taken for ShellSort: " << measureExecutionTime(data1M, shellsort) << " seconds\n";
    cout << "time taken for HeapSort: " << measureExecutionTime(data1M, heapsort) << " seconds\n";
    cout << "Average and median for 1M ratings:\n";
    averageRaitings(data1M);
    medianRaitings(data1M);
    cout<< "\nSorting all ratings...\n";
    cout << "time taken for MergeSort: " << measureExecutionTime(dataMax, mergesort) << " seconds\n";
    cout << "time taken for ShellSort: " << measureExecutionTime(dataMax, shellsort) << " seconds\n";
    cout << "time taken for HeapSort: " << measureExecutionTime(dataMax, heapsort) << " seconds\n";
    cout << "Average and median for all ratings:\n";
    averageRaitings(dataMax);
    medianRaitings(dataMax);

    return 0;
}