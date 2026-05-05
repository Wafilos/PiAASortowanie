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
    int isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
    string genres;

    BasicsData() : isAdult(0), startYear(0), endYear(0), runtimeMinutes(0) {}
    BasicsData(string tType, string pTitle, string oTitle, int adult, int sYear, int eYear, int runtime, string gen)
        : titleType(tType), primaryTitle(pTitle), originalTitle(oTitle), isAdult(adult), startYear(sYear), endYear(eYear), runtimeMinutes(runtime), genres(gen) {}
};

struct MergedRecord {
    string tconst;
    string titleType;
    string primaryTitle;
    string originalTitle;
    int isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
    string genres;
    double averageRating;
    int numVotes;

    MergedRecord() : isAdult(0), startYear(0), endYear(0), runtimeMinutes(0), averageRating(0.0), numVotes(0) {}

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

void shellsortTest(vector<double> array) {
    ShellSort<double> shellSort;
    shellSort.sort(array.begin(), array.end());
}

void mergesortTest(vector<double> array) {
    MergeSort<double> mergeSort;
    mergeSort.sort(array, array.begin(), array.end());
}

void heapsortTest(vector<double> array) {
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
    auto programStart = high_resolution_clock::now();


    try {
        ifstream input("title.ratings.tsv");
        if (!input) {
            cerr << "Error opening title.ratings.tsv\n";
            return 1;
        }

        vector<double> allRatings;
        string line;
        getline(input, line); // Pomiń nagłówek

        while (getline(input, line)) {
            size_t firstTab = line.find('\t');
            size_t secondTab = line.find('\t', firstTab + 1);

            if (firstTab == string::npos || secondTab == string::npos) continue;

            size_t start = firstTab + 1;
            size_t length = secondTab - start;
            if (length == 0) continue;

            try {
                double rating = stod(line.substr(start, length));
                allRatings.push_back(rating);
            } catch (...) {
                continue;
            }
        }
        input.close();
        cout << "Total ratings loaded: " << allRatings.size() << "\n\n";

        vector<double> data10k, data100k, data500k, data1M, dataMax;

        if (allRatings.size() >= 10000)
            data10k.assign(allRatings.begin(), allRatings.begin() + 10000);

        if (allRatings.size() >= 100000)
            data100k.assign(allRatings.begin(), allRatings.begin() + 100000);

        if (allRatings.size() >= 500000)
            data500k.assign(allRatings.begin(), allRatings.begin() + 500000);

        if (allRatings.size() >= 1000000)
            data1M.assign(allRatings.begin(), allRatings.begin() + 1000000);

        dataMax = allRatings;

        
        if (!data10k.empty()) {
            cout << "--- Testing 10k ratings ---\n";
            cout << "time taken for MergeSort: " << measureExecutionTime(data10k, mergesortTest) << " seconds\n";
            cout << "time taken for ShellSort: " << measureExecutionTime(data10k, shellsortTest) << " seconds\n";
            cout << "time taken for HeapSort: " << measureExecutionTime(data10k, heapsortTest) << " seconds\n";
            cout << "Average and median for 10k ratings:\n";
            averageRatings(data10k);
            medianRatings(data10k);
            cout << "\n";
        }

        
        if (!data100k.empty()) {
            cout << "--- Testing 100k ratings ---\n";
            cout << "time taken for MergeSort: " << measureExecutionTime(data100k, mergesortTest) << " seconds\n";
            cout << "time taken for ShellSort: " << measureExecutionTime(data100k, shellsortTest) << " seconds\n";
            cout << "time taken for HeapSort: " << measureExecutionTime(data100k, heapsortTest) << " seconds\n";
            cout << "Average and median for 100k ratings:\n";
            averageRatings(data100k);
            medianRatings(data100k);
            cout << "\n";
        }

        
        if (!data500k.empty()) {
            cout << "--- Testing 500k ratings ---\n";
            cout << "time taken for MergeSort: " << measureExecutionTime(data500k, mergesortTest) << " seconds\n";
            cout << "time taken for ShellSort: " << measureExecutionTime(data500k, shellsortTest) << " seconds\n";
            cout << "time taken for HeapSort: " << measureExecutionTime(data500k, heapsortTest) << " seconds\n";
            cout << "Average and median for 500k ratings:\n";
            averageRatings(data500k);
            medianRatings(data500k);
            cout << "\n";
        }

        
        if (!data1M.empty()) {
            cout << "--- Testing 1M ratings ---\n";
            cout << "time taken for MergeSort: " << measureExecutionTime(data1M, mergesortTest) << " seconds\n";
            cout << "time taken for ShellSort: " << measureExecutionTime(data1M, shellsortTest) << " seconds\n";
            cout << "time taken for HeapSort: " << measureExecutionTime(data1M, heapsortTest) << " seconds\n";
            cout << "Average and median for 1M ratings:\n";
            averageRatings(data1M);
            medianRatings(data1M);
            cout << "\n";
        }

        
        if (!dataMax.empty()) {
            cout << "--- Testing ALL ratings (" << dataMax.size() << " records) ---\n";
            cout << "time taken for MergeSort: " << measureExecutionTime(dataMax, mergesortTest) << " seconds\n";
            cout << "time taken for ShellSort: " << measureExecutionTime(dataMax, shellsortTest) << " seconds\n";
            cout << "time taken for HeapSort: " << measureExecutionTime(dataMax, heapsortTest) << " seconds\n";
            cout << "Average and median for all ratings:\n";
            averageRatings(dataMax);
            medianRatings(dataMax);
            cout << "\n";
        }

        cout << "\nLoading and sorting ratings by rating value...\n";

        auto avlStart = high_resolution_clock::now();

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

        // Sortuj oceny po wartości oceny (malejąco)
        cout << "Sorting " << ratingCount << " ratings by rating value...\n";
        ShellSort<RatingRecord> ratingSort;
        ratingSort.sort(sortedRatings.begin(), sortedRatings.end());

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
            int isAdult, startYear, endYear, runtimeMinutes;

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

        // FAZA 6: Łączenie posortowanych ocen z danymi podstawowymi
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

        auto programEnd = high_resolution_clock::now();
        double totalTime = duration<double>(programEnd - programStart).count();

        cout << "Total execution time: " << totalTime << " seconds\n";
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