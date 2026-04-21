#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std::chrono;

int main() {
    std::ifstream input("title.ratings.tsv");
    std::ofstream output("title.ratings.filtered.tsv");

    if (!input || !output) {
        std::cerr << "Error opening files\n";
        return 1;
    }

    std::string line;

    // Copy header
    if (std::getline(input, line)) {
        output << line << '\n';
    }
    auto start = high_resolution_clock::now();
    while (std::getline(input, line)) {
        // Find first and second tab positions
        size_t firstTab = line.find('\t');
        if (firstTab == std::string::npos) continue;

        size_t secondTab = line.find('\t', firstTab + 1);
        if (secondTab == std::string::npos) continue;

        // Extract averageRating (middle column) WITHOUT creating substr (optional optimization)
        size_t start = firstTab + 1;
        size_t length = secondTab - start;

        // Check if empty
        if (length == 0) continue;
        
        // Write whole line (fastest — no rebuilding)
        output << line << '\n';
    }
    auto end = high_resolution_clock::now();
    std::cout << "Filtering completed in " << duration<double>(end - start).count() << " seconds.\n";

    std::cout << "Done.\n";
    return 0;
}