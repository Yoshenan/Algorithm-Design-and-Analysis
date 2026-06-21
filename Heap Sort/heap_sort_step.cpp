// *********************************************************
// Program: YOUR_FILENAME.cpp
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
#include <utility>   // std::swap

struct Record {
    uint64_t key;       // 10-digit integer  <- sorted by this
    std::string label;  // 5-letter string   <- travels with its key
};

// Identical heap engine to heap_sort.cpp.
void siftDown(std::vector<Record>& a, int64_t i, int64_t heapSize) {
    while (true) {
        int64_t largest = i;
        int64_t left  = 2 * i + 1;
        int64_t right = 2 * i + 2;
        if (left  < heapSize && a[left].key  > a[largest].key) largest = left;
        if (right < heapSize && a[right].key > a[largest].key) largest = right;
        if (largest == i) break;
        std::swap(a[i], a[largest]);
        i = largest;
    }
}

// Print one snapshot, e.g.  [1000000197/ufnja, 1000000155/gslag, ...] initial
void printArray(std::ofstream& out, const std::vector<Record>& a, const std::string& tag) {
    out << "[";
    for (std::size_t i = 0; i < a.size(); ++i) {
        out << a[i].key << "/" << a[i].label;
        if (i + 1 < a.size()) out << ", ";
    }
    out << "] " << tag << "\n";
}

// Heap sort, but logging the array at each stage instead of staying silent.
void heapSortStep(std::vector<Record>& a, std::ofstream& out) {
    int64_t n = static_cast<int64_t>(a.size());

    // Phase 1: build the max-heap, then log the result as "initial".
    for (int64_t i = n / 2 - 1; i >= 0; --i)
        siftDown(a, i, n);
    printArray(out, a, "initial");

    // Phase 2: move the max to the back, shrink, re-heapify, log each pass.
    for (int64_t end = n - 1; end > 0; --end) {
        std::swap(a[0], a[end]);
        siftDown(a, 0, end);
        printArray(out, a, "i = " + std::to_string(end));
    }
}

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
        if (!r.label.empty() && r.label.back() == '\r') r.label.pop_back();
        records.push_back(r);
    }
    return records;
}

int main(int argc, char** argv) {
    // Usage: ./heap_sort_step dataset_1000.csv <startRow> <endRow>
    // Defaults reproduce the assignment's documented 1..7 sample.
    std::string inputFile = (argc > 1) ? argv[1] : "dataset_1000.csv";
    int startRow = (argc > 2) ? std::stoi(argv[2]) : 1;   // 1-indexed, inclusive
    int endRow   = (argc > 3) ? std::stoi(argv[3]) : 7;

    std::vector<Record> all = readDataset(inputFile);
    if (all.empty()) {
        std::cerr << "No records read. Check the filename.\n";
        return 1;
    }
    int n = static_cast<int>(all.size());

    // Validate / clamp the requested row range.
    if (startRow < 1) startRow = 1;
    if (endRow > n)  endRow = n;
    if (startRow > endRow) {
        std::cerr << "Invalid range: start row > end row.\n";
        return 1;
    }

    // Slice out rows [startRow, endRow] and trace the sort on just that slice.
    std::vector<Record> slice(all.begin() + (startRow - 1), all.begin() + endRow);

    std::string outName = "dataset_" + std::to_string(n) + "_heap_sorted_step_"
                          + std::to_string(startRow) + "_" + std::to_string(endRow) + ".txt";
    std::ofstream out(outName);

    heapSortStep(slice, out);

    std::cout << "Heap sort step trace (rows " << startRow << ".." << endRow
              << ") written to: " << outName << "\n";
    return 0;
}
