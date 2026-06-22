// *********************************************************
// Program: heap_sort.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T15L
// Trimester: 2610
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD.KAMALr@student.mmu.edu.my  | 012-418-8300
// Member_2: 242UC244GD | Yoshenan A/L Shanker |YOSHENAN.SHANKER@student.mmu.edu.my  | 011-3310-7367
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my  | 017-322-0572
// Member_4: 243UC247BQ | HEMARAJ A/L RAJAN  | HEMARAJ.RAJAN@student.mmu.edu.my   | 014-377-3108
// *********************************************************
// Task Distribution
// Member_1: Implementation of dataset generator
// Member_2:Implementation of radix sort and radix sort step
// Member_3:Implementation of heap sort and heap sort step
// Member_4:Implementation of hash table and hash table search
// *********************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <chrono>
#include <utility>   // std::swap (a swap is NOT a sorting library function)

// Each dataset row is a (10-digit integer, 5-letter string) pair.
// IMPORTANT: the integers go up to 9,999,999,999, which is LARGER than a
// 32-bit int can hold (max ~4.29 billion). So the key MUST be 64-bit.
struct Record {
    uint64_t key;       // the 10-digit integer  <- we sort by THIS
    std::string label;  // the 5-letter string   <- travels with its key
};

// ---------------------------------------------------------------
// siftDown: restore the max-heap property for the subtree rooted at i.
// Compares a node with its two children and, if a child is bigger,
// swaps down and keeps going. heapSize lets us "shrink" the heap
// during the sort phase so the already-placed elements are ignored.
// 64-bit indices are used so this stays correct for very large n.
// ---------------------------------------------------------------
void siftDown(std::vector<Record>& a, int64_t i, int64_t heapSize) {
    while (true) {
        int64_t largest = i;
        int64_t left  = 2 * i + 1;   // left child  (0-indexed array)
        int64_t right = 2 * i + 2;   // right child

        if (left  < heapSize && a[left].key  > a[largest].key) largest = left;
        if (right < heapSize && a[right].key > a[largest].key) largest = right;

        if (largest == i) break;        // subtree already a valid max-heap
        std::swap(a[i], a[largest]);    // swaps key AND label together
        i = largest;                    // follow the element down
    }
}

// ---------------------------------------------------------------
// heapSort: in-place, two phases.
//   Phase 1 (BUILD): turn the array into a max-heap, O(n).
//   Phase 2 (SORT) : repeatedly move the root (the max) to the back,
//                    shrink the heap, and re-heapify. O(n log n).
// ---------------------------------------------------------------
void heapSort(std::vector<Record>& a) {
    int64_t n = static_cast<int64_t>(a.size());

    // Phase 1: start at the last internal node (n/2 - 1). Everything
    // past that index is a leaf, and a single leaf is already a valid heap.
    for (int64_t i = n / 2 - 1; i >= 0; --i)
        siftDown(a, i, n);

    // Phase 2: the largest element is always at index 0. Park it at the
    // end, then re-heapify the (now smaller) heap.
    for (int64_t end = n - 1; end > 0; --end) {
        std::swap(a[0], a[end]);
        siftDown(a, 0, end);
    }
}

// ---------------------------------------------------------------
// CSV input. Each line looks like:  1000000038,uoren
// (NOT timed in main, per requirement 7a.)
// ---------------------------------------------------------------
std::vector<Record> readDataset(const std::string& filename) {
    std::vector<Record> records;
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return records;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        Record r;
        r.key   = std::stoull(line.substr(0, comma));
        r.label = line.substr(comma + 1);

        // Strip a trailing '\r' so Windows-created files don't corrupt labels.
        if (!r.label.empty() && r.label.back() == '\r') r.label.pop_back();

        records.push_back(r);
    }
    return records;
}

// CSV output (NOT timed).
void writeDataset(const std::string& filename, const std::vector<Record>& records) {
    std::ofstream out(filename);
    for (const auto& r : records)
        out << r.key << "," << r.label << "\n";
}

// ---------------------------------------------------------------
int main(int argc, char** argv) {
    // Usage: ./heap_sort dataset_1000000.csva
    std::string inputFile = (argc > 1) ? argv[1] : "dataset_1000.csv";

    // ---- READ (not timed) ----
    std::vector<Record> data = readDataset(inputFile);
    if (data.empty()) {
        std::cerr << "No records read. Check the filename.\n";
        return 1;
    }

    // ---- SORT (this is the ONLY thing the clock measures) ----
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(data);
    auto stop  = std::chrono::high_resolution_clock::now();
    double seconds = std::chrono::duration<double>(stop - start).count();

    // ---- WRITE (not timed) ----
    std::string outputFile = "heap_sorted_" + inputFile;
    writeDataset(outputFile, data);

    // ---- REPORT (screenshot this console output for your proof) ----
    std::cout << "Heap sort | input: " << inputFile
              << " | records: " << data.size() << "\n";
    std::cout << "Running time (sort only): " << seconds << " seconds\n";
    std::cout << "Sorted output written to: " << outputFile << "\n";
    return 0;
}
