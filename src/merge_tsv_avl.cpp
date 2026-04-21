#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include "../include/algorithms/avltree.h"

using namespace std;
using namespace chrono;

// Structure to hold title ratings data
struct RatingsData {
    string tconst;
    double averageRating;
    int numVotes;

    RatingsData() : averageRating(0.0), numVotes(0) {}
    RatingsData(string t, double rating, int votes)
        : tconst(t), averageRating(rating), numVotes(votes) {}
};

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
};

// Function to parse and read ratings TSV file into AVL tree
void loadRatingsIntoAVL(const string& filename, AVLTree<string, RatingsData>& tree) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening ratings file: " << filename << "\n";
        return;
    }

    string line;
    getline(file, line); // Skip header

    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string tconst;
        double rating;
        int votes;

        if (getline(ss, tconst, '\t') &&
            ss >> rating &&
            ss.ignore() &&
            ss >> votes) {
            tree.insert(tconst, RatingsData(tconst, rating, votes));
            count++;
            if (count % 100000 == 0) {
                cout << "Loaded " << count << " ratings records into AVL tree\n";
            }
        }
    }
    file.close();
    cout << "Total ratings loaded into AVL tree: " << count << "\n";
}

// Function to read basics TSV file and merge with AVL tree
void mergeBasicsWithRatings(const string& basicsFile, const string& outputFile,
                            const AVLTree<string, RatingsData>& ratingsTree) {
    ifstream basicsInput(basicsFile);
    if (!basicsInput.is_open()) {
        cerr << "Error opening basics file: " << basicsFile << "\n";
        return;
    }

    ofstream output(outputFile);
    if (!output.is_open()) {
        cerr << "Error creating output file: " << outputFile << "\n";
        return;
    }

    // Write header
    output << "tconst\ttitleType\tprimaryTitle\toriginalTitle\tisAdult\tstartYear\tendYear\truntimeMinutes\tgenres\taverageRating\tnumVotes\n";

    string line;
    getline(basicsInput, line); // Skip header

    int mergedCount = 0;
    int processedCount = 0;

    while (getline(basicsInput, line)) {
        if (line.empty()) continue;

        processedCount++;
        stringstream ss(line);
        string tconst, titleType, primaryTitle, originalTitle, genresStr;
        int isAdult, startYear, endYear, runtimeMinutes;

        // Parse basics line
        if (!(getline(ss, tconst, '\t') &&
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
              getline(ss, genresStr, '\t'))) {
            continue;
        }

        // Search for matching ratings in AVL tree
        RatingsData ratings;
        if (ratingsTree.find(tconst, ratings)) {
            // Write merged line
            output << tconst << "\t"
                   << titleType << "\t"
                   << primaryTitle << "\t"
                   << originalTitle << "\t"
                   << isAdult << "\t"
                   << startYear << "\t"
                   << endYear << "\t"
                   << runtimeMinutes << "\t"
                   << genresStr << "\t"
                   << ratings.averageRating << "\t"
                   << ratings.numVotes << "\n";
            mergedCount++;
        }

        if (processedCount % 10000 == 0) {
            cout << "Processed: " << processedCount << " records, Merged: " << mergedCount << "\n";
        }
    }

    basicsInput.close();
    output.close();

    cout << "Successfully merged records: " << mergedCount << "\n";
    cout << "Output written to: " << outputFile << "\n";
}

int main() {
    auto startTime = high_resolution_clock::now();

    // Create AVL tree for ratings data
    AVLTree<string, RatingsData> ratingsTree;

    // Load ratings data into AVL tree
    cout << "Step 1: Loading ratings data...\n";
    loadRatingsIntoAVL("title.ratings.tsv", ratingsTree);

    // Merge basics with ratings using AVL tree lookups
    cout << "\nStep 2: Merging basics data with ratings...\n";
    mergeBasicsWithRatings("title.basics.tsv", "merged_output.tsv", ratingsTree);

    auto endTime = high_resolution_clock::now();
    double elapsed = duration<double>(endTime - startTime).count();

    cout << "Total execution time: " << elapsed << " seconds\n";

    return 0;
}
