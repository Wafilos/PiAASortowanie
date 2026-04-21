#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "../include/algorithms/shellsort.h"

using namespace std;
using namespace chrono;

// Structure to hold merged data
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

    // Comparison operators for shell sort (sort by rating in descending order)
    bool operator<(const MergedRecord& other) const {
        return this->averageRating > other.averageRating;  // Descending order
    }

    bool operator>(const MergedRecord& other) const {
        return this->averageRating < other.averageRating;  // Descending order
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

// Function to load merged TSV file into vector
vector<MergedRecord> loadMergedData(const string& filename) {
    vector<MergedRecord> records;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << "\n";
        return records;
    }

    string line;
    getline(file, line); // Skip header

    int recordCount = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        MergedRecord record;

        if (getline(ss, record.tconst, '\t') &&
            getline(ss, record.titleType, '\t') &&
            getline(ss, record.primaryTitle, '\t') &&
            getline(ss, record.originalTitle, '\t') &&
            ss >> record.isAdult &&
            ss.ignore() &&
            ss >> record.startYear &&
            ss.ignore() &&
            ss >> record.endYear &&
            ss.ignore() &&
            ss >> record.runtimeMinutes &&
            ss.ignore() &&
            getline(ss, record.genres, '\t') &&
            ss >> record.averageRating &&
            ss.ignore() &&
            ss >> record.numVotes) {
            records.push_back(record);
            recordCount++;
            if (recordCount % 100000 == 0) {
                cout << "Loaded " << recordCount << " records\n";
            }
        }
    }

    file.close();
    cout << "Total records loaded: " << recordCount << "\n";
    return records;
}

// Function to sort using shell sort by rating
void sortByRatingShellSort(vector<MergedRecord>& records) {
    if (records.empty()) {
        cerr << "No records to sort\n";
        return;
    }

    cout << "\nSorting " << records.size() << " records by rating (descending) using Shell Sort...\n";
    auto start = high_resolution_clock::now();

    ShellSort<MergedRecord> shellSort;
    shellSort.sort(records.begin(), records.end());

    auto end = high_resolution_clock::now();
    double elapsed = duration<double>(end - start).count();
    cout << "Shell Sort completed in " << elapsed << " seconds\n";
}

// Function to write sorted data to output file
void writeSortedData(const string& filename, const vector<MergedRecord>& records) {
    ofstream output(filename);
    if (!output.is_open()) {
        cerr << "Error creating output file: " << filename << "\n";
        return;
    }

    // Write header
    output << "tconst\ttitleType\tprimaryTitle\toriginalTitle\tisAdult\tstartYear\tendYear\truntimeMinutes\tgenres\taverageRating\tnumVotes\n";

    int recordCount = 0;
    for (const auto& record : records) {
        output << record.tconst << "\t"
               << record.titleType << "\t"
               << record.primaryTitle << "\t"
               << record.originalTitle << "\t"
               << record.isAdult << "\t"
               << record.startYear << "\t"
               << record.endYear << "\t"
               << record.runtimeMinutes << "\t"
               << record.genres << "\t"
               << record.averageRating << "\t"
               << record.numVotes << "\n";
        recordCount++;
    }

    output.close();
    cout << "Successfully wrote " << recordCount << " sorted records to: " << filename << "\n";
}

int main() {
    auto startTime = high_resolution_clock::now();

    cout << "=== Sort merged_output.tsv using Shell Sort ===\n\n";

    // Load merged data
    cout << "Step 1: Loading merged data...\n";
    vector<MergedRecord> mergedData = loadMergedData("merged_output.tsv");

    if (mergedData.empty()) {
        cerr << "No data to sort\n";
        return 1;
    }

    // Sort by rating using shell sort
    cout << "\nStep 2: Sorting by rating...\n";
    sortByRatingShellSort(mergedData);

    // Write sorted data
    cout << "\nStep 3: Writing sorted output...\n";
    writeSortedData("merged_output_sorted.tsv", mergedData);

    auto endTime = high_resolution_clock::now();
    double elapsed = duration<double>(endTime - startTime).count();

    cout << "\n=== Operation complete ===\n";
    cout << "Total execution time: " << elapsed << " seconds\n";
    cout << "Output file: merged_output_sorted.tsv\n";

    return 0;
}