#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\shellsort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\avltree.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\mergesort.h"
#include "C:\Users\dru-b\OneDrive\Pulpit\PiAASortowanie\include\algorithms\heapsort.h"

using namespace std;
using namespace chrono;

// STRUKTURY

struct BasicsData {
    string titleType;
    string primaryTitle;
    string originalTitle;
    string isAdult;
    string startYear;
    string endYear;
    string runtimeMinutes;
    string genres;

    BasicsData() : isAdult("0"), startYear("0"), endYear("0"), runtimeMinutes("0") {}
    BasicsData(string tType, string pTitle, string oTitle, string adult, string sYear, string eYear, string runtime, string gen)
        : titleType(tType), primaryTitle(pTitle), originalTitle(oTitle), isAdult(adult), startYear(sYear), endYear(eYear), runtimeMinutes(runtime), genres(gen) {}
};

        // Struktura do przechowywania oceny z dodatkowymi danymi
struct RatingRecord {
    string tconst;
    double rating;
    int votes;
            
    bool operator<(const RatingRecord& other) const {
                return this->rating > other.rating; // Malejąco
    }

    bool operator>(const RatingRecord& other) const {
                return this->rating < other.rating;
    }

    bool operator<=(const RatingRecord& other) const {
    return this->rating >= other.rating;
        }

    bool operator>=(const RatingRecord& other) const {
        return this->rating <= other.rating;
        }

    bool operator==(const RatingRecord& other) const {
        return this->rating == other.rating;
        }
     };

struct MergedRecord {
    string tconst;
    string titleType;
    string primaryTitle;
    string originalTitle;
    string isAdult;
    string startYear;
    string endYear;
    string runtimeMinutes;
    string genres;
    double averageRating;
    int numVotes;

    MergedRecord() : isAdult("0"), startYear("0"), endYear("0"), runtimeMinutes("0"), averageRating(0.0), numVotes(0) {}

    // Porównanie oparte na ocenie (malejąco)
    bool operator<(const MergedRecord& other) const {
        return this->averageRating > other.averageRating;
    }

    bool operator>(const MergedRecord& other) const {
        return this->averageRating < other.averageRating;
    }

    bool operator<=(const MergedRecord& other) const {
        return this->averageRating >= other.averageRating;
    }

    bool operator>=(const MergedRecord& other) const {
        return this->averageRating <= other.averageRating;
    }

    bool operator==(const MergedRecord& other) const {
        return this->averageRating == other.averageRating;
    }
};

// FUNKCJE STATYSTYCZNE

void averageRatings(const vector<double>& array) {
    if (array.empty()) return;
    double sum = 0.0;
    for (const auto& rating : array) {
        sum += rating;
    }
    double average = sum / array.size();
    cout << "Average rating: " << average << "\n";
}

void medianRatings(vector<double> array) {
    if (array.empty()) return;
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

// FUNKCJE TESTOWE SORTOWANIA

template<typename T>
void shellsortTest(vector<T> array) {
    ShellSort<T> shellSort;
    shellSort.sort(array.begin(), array.end());
}

template<typename T>
void mergesortTest(vector<T> array) {
    MergeSort<T> mergeSort;
    mergeSort.sort(array, array.begin(), array.end() - 1);
}

template<typename T>
void heapsortTest(vector<T> array) {
    HeapSort<T> heapSort;
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
    
    try {
        string line;
        cout << "Testing sorting algorithms on complete title.ratings.tsv file...\n\n";
        
        cout << "Loading all rating records from title.ratings.tsv...\n";

        auto avlStart = high_resolution_clock::now();

        vector<RatingRecord> sortedRatings;
        int ratingCount = 0;

        ifstream ratingsFile("title.ratings.tsv");
        if (!ratingsFile) {
            cerr << "Error opening ratings file\n";
            return 1;
        }

        getline(ratingsFile, line); // Pomiń nagłówek
        while (getline(ratingsFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string tconst;
            double rating;
            int votes;

            if (getline(ss, tconst, '\t') &&
                ss >> rating &&
                ss.ignore() &&
                ss >> votes) {
                sortedRatings.push_back({tconst, rating, votes});
                ratingCount++;
                if (ratingCount % 100000 == 0) {
                    cout << "Loaded " << ratingCount << " ratings\n";
                }
            }
        }
        ratingsFile.close();

        auto avlEnd = high_resolution_clock::now();
        double avlTime = duration<double>(avlEnd - avlStart).count();

        cout << "Total ratings loaded: " << ratingCount << "\n";
        cout << "Ratings loading time: " << avlTime << " seconds\n\n";
        
        if (sortedRatings.size() >= 10000) {
            cout << "--- Testing 10k ratings records ---\n";
            vector<RatingRecord> data10k(sortedRatings.begin(), sortedRatings.begin() + 10000);
            cout << "time taken for MergeSort: " << measureExecutionTime(data10k, mergesortTest<RatingRecord>) << " seconds\n";
            data10k.clear();
            data10k.shrink_to_fit();
            
            vector<RatingRecord> data10k_shell(sortedRatings.begin(), sortedRatings.begin() + 10000);
            cout << "time taken for ShellSort: " << measureExecutionTime(data10k_shell, shellsortTest<RatingRecord>) << " seconds\n";
            data10k_shell.clear();
            data10k_shell.shrink_to_fit();
            
            vector<RatingRecord> data10k_heap(sortedRatings.begin(), sortedRatings.begin() + 10000);
            cout << "time taken for HeapSort: " << measureExecutionTime(data10k_heap, heapsortTest<RatingRecord>) << " seconds\n";
            data10k_heap.clear();
            data10k_heap.shrink_to_fit();
            cout << "\n";
        }

        if (sortedRatings.size() >= 100000) {
            cout << "--- Testing 100k ratings records ---\n";
            vector<RatingRecord> data100k(sortedRatings.begin(), sortedRatings.begin() + 100000);
            cout << "time taken for MergeSort: " << measureExecutionTime(data100k, mergesortTest<RatingRecord>) << " seconds\n";
            data100k.clear();
            data100k.shrink_to_fit();
            
            vector<RatingRecord> data100k_shell(sortedRatings.begin(), sortedRatings.begin() + 100000);
            cout << "time taken for ShellSort: " << measureExecutionTime(data100k_shell, shellsortTest<RatingRecord>) << " seconds\n";
            data100k_shell.clear();
            data100k_shell.shrink_to_fit();
            
            vector<RatingRecord> data100k_heap(sortedRatings.begin(), sortedRatings.begin() + 100000);
            cout << "time taken for HeapSort: " << measureExecutionTime(data100k_heap, heapsortTest<RatingRecord>) << " seconds\n";
            data100k_heap.clear();
            data100k_heap.shrink_to_fit();
            cout << "\n";
        }

        if (sortedRatings.size() >= 500000) {
            cout << "--- Testing 500k ratings records ---\n";
            vector<RatingRecord> data500k(sortedRatings.begin(), sortedRatings.begin() + 500000);
            cout << "time taken for MergeSort: " << measureExecutionTime(data500k, mergesortTest<RatingRecord>) << " seconds\n";
            data500k.clear();
            data500k.shrink_to_fit();
            
            vector<RatingRecord> data500k_shell(sortedRatings.begin(), sortedRatings.begin() + 500000);
            cout << "time taken for ShellSort: " << measureExecutionTime(data500k_shell, shellsortTest<RatingRecord>) << " seconds\n";
            data500k_shell.clear();
            data500k_shell.shrink_to_fit();
            
            vector<RatingRecord> data500k_heap(sortedRatings.begin(), sortedRatings.begin() + 500000);
            cout << "time taken for HeapSort: " << measureExecutionTime(data500k_heap, heapsortTest<RatingRecord>) << " seconds\n";
            data500k_heap.clear();
            data500k_heap.shrink_to_fit();
            cout << "\n";
        }

        if (sortedRatings.size() >= 1000000) {
            cout << "--- Testing 1M ratings records ---\n";
            vector<RatingRecord> data1M(sortedRatings.begin(), sortedRatings.begin() + 1000000);
            cout << "time taken for MergeSort: " << measureExecutionTime(data1M, mergesortTest<RatingRecord>) << " seconds\n";
            data1M.clear();
            data1M.shrink_to_fit();
            
            vector<RatingRecord> data1M_shell(sortedRatings.begin(), sortedRatings.begin() + 1000000);
            cout << "time taken for ShellSort: " << measureExecutionTime(data1M_shell, shellsortTest<RatingRecord>) << " seconds\n";
            data1M_shell.clear();
            data1M_shell.shrink_to_fit();
            
            vector<RatingRecord> data1M_heap(sortedRatings.begin(), sortedRatings.begin() + 1000000);
            cout << "time taken for HeapSort: " << measureExecutionTime(data1M_heap, heapsortTest<RatingRecord>) << " seconds\n";
            data1M_heap.clear();
            data1M_heap.shrink_to_fit();
            cout << "\n";
        }

        if (sortedRatings.size() > 0) {
            cout << "--- Testing ALL ratings records (" << sortedRatings.size() << " records) ---\n";
            vector<RatingRecord> dataMax = sortedRatings;
            cout << "time taken for MergeSort: " << measureExecutionTime(dataMax, mergesortTest<RatingRecord>) << " seconds\n";
            dataMax.clear();
            dataMax.shrink_to_fit();
            
            vector<RatingRecord> dataMax_shell = sortedRatings;
            cout << "time taken for ShellSort: " << measureExecutionTime(dataMax_shell, shellsortTest<RatingRecord>) << " seconds\n";
            dataMax_shell.clear();
            dataMax_shell.shrink_to_fit();
            
            vector<RatingRecord> dataMax_heap = sortedRatings;
            cout << "time taken for HeapSort: " << measureExecutionTime(dataMax_heap, heapsortTest<RatingRecord>) << " seconds\n";
            dataMax_heap.clear();
            dataMax_heap.shrink_to_fit();
            cout << "\n";
        }

        cout << "Preparing final sorted dataset for merging...\n";
        cout << "\nChoose which sorting algorithm to use for final sorting:\n";
        cout << "1. ShellSort\n";
        cout << "2. HeapSort\n";
        cout << "3. MergeSort\n";
        cout << "Enter your choice (1-3): ";
        
        int choice;
        cin >> choice;
        
        auto finalSortStart = high_resolution_clock::now();
        
        switch(choice) {
            case 1: {
                cout << "Using ShellSort for final sorting...\n";
                ShellSort<RatingRecord> ratingSort;
                ratingSort.sort(sortedRatings.begin(), sortedRatings.end());
                break;
            }
            case 2: {
                cout << "Using HeapSort for final sorting...\n";
                HeapSort<RatingRecord> ratingSort;
                ratingSort.sort(sortedRatings);
                break;
            }
            case 3: {
                cout << "Using MergeSort for final sorting...\n";
                MergeSort<RatingRecord> ratingSort;
                ratingSort.sort(sortedRatings, sortedRatings.begin(), sortedRatings.end() - 1);
                break;
            }
            default: {
                cout << "Invalid choice. Using ShellSort by default...\n";
                ShellSort<RatingRecord> ratingSort;
                ratingSort.sort(sortedRatings.begin(), sortedRatings.end());
                break;
            }
        }
        
        auto finalSortEnd = high_resolution_clock::now();
        double finalSortTime = duration<double>(finalSortEnd - finalSortStart).count();
        cout << "Final sort time: " << finalSortTime << " seconds\n\n";

        cout << "Loading basics data into AVL tree...\n";
        
        AVLTree<string, BasicsData> basicsTree;
        
        ifstream basicsInput("title.basics.tsv");
        if (!basicsInput.is_open()) {
            cerr << "Error opening basics file\n";
            return 1;
        }

        getline(basicsInput, line); // Pomiń nagłówek
        int basicsCount = 0;
        while (getline(basicsInput, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string tconst, titleType, primaryTitle, originalTitle, genresStr;
            string isAdult, startYear, endYear, runtimeMinutes;

            if (getline(ss, tconst, '\t') &&
                getline(ss, titleType, '\t') &&
                getline(ss, primaryTitle, '\t') &&
                getline(ss, originalTitle, '\t') &&
                ss >> isAdult &&
                ss.ignore() &&
                ss >> startYear &&
                ss.ignore() &&
                ss >> endYear &&
                ss.ignore() &&
                ss >> runtimeMinutes &&
                ss.ignore() &&
                getline(ss, genresStr, '\t')) {
                
                basicsTree.insert(tconst, BasicsData(titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genresStr));
                basicsCount++;
                if (basicsCount % 100000 == 0) {
                    cout << "Loaded " << basicsCount << " basics records into AVL tree\n";
                }
            }
        }
        basicsInput.close();
        cout << "Total basics records loaded into AVL tree: " << basicsCount << "\n\n";

        cout << "Merging sorted ratings with basics data...\n";
        
        ofstream sortedOutput("merged_output_sorted.tsv");
        if (!sortedOutput.is_open()) {
            cerr << "Error creating sorted output file\n";
            return 1;
        }

        // Zapisz nagłówek
        sortedOutput << "tconst\ttitle\trating\n";

        int mergedCount = 0;
        for (const auto& ratingRecord : sortedRatings) {
            // Szukaj danych podstawowych w drzewie AVL
            BasicsData basics;
            if (basicsTree.find(ratingRecord.tconst, basics)) {
                // Zapisz połączony wiersz z posortowaną oceną
                sortedOutput << ratingRecord.tconst << "\t"
                            << basics.primaryTitle << "\t"
                            << ratingRecord.rating << "\n";
                mergedCount++;
            }
        }

        sortedOutput.close();

        cout << "Successfully merged " << mergedCount << " sorted records\n";
        cout << "Output written to: merged_output_sorted.tsv\n\n";

        cout << "Final output file: merged_output_sorted.tsv\n";
        cout << "Records processed and sorted: " << mergedCount << "\n";
        cout << "Data sorted by RATING (descending)\n";

        return 0;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}