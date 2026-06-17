#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct DataRow {
    long long intKey;
    string strKey;
};

int countLines(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return 0;
    int lines = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) lines++;
    }
    return lines;
}

void countingSortRadix(DataRow arr[], int n, long long exp) {
    DataRow* output = new DataRow[n];
    int count[10] = {0};

    for(int i = 0; i < n; i++) {
        int digit = (arr[i].intKey / exp) % 10;
        count[digit]++;
    }

    for(int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for(int i = n - 1; i >= 0; i--) {
        int digit = (arr[i].intKey / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output;
}

void radixSortStep(DataRow arr[], int n, int startRow, int endRow, const string& outputFilename) {
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) return;

    long long placement = 1;
    for (int d = 1; d <= 10; d++) {
        outputFile << "(processing from the rightmost character)\n";

        outputFile << "[";
        for (int i = startRow; i <= endRow && i < n; i++) {
            outputFile << arr[i].intKey << "/" << arr[i].strKey;
            if (i < endRow && i < n - 1) outputFile << ", ";
        }
        outputFile << "] original\n";

        countingSortRadix(arr, n, placement);
        placement *= 10;

        outputFile << "[";
        for (int i = startRow; i <= endRow && i < n; i++) {
            outputFile << arr[i].intKey << "/" << arr[i].strKey;
            if (i < endRow && i < n - 1) outputFile << ", ";
        }
        outputFile << "] d=" << (11 - d) << "\n";
    }
    outputFile.close();
}

int main() {
    string csvFilename;
    int startRow, endRow;

    cout << "Enter target dataset CSV file name: ";
    cin >> csvFilename;
    cout << "Enter tracking start row index: ";
    cin >> startRow;
    cout << "Enter tracking end row index: ";
    cin >> endRow;

    int maxLines = countLines(csvFilename);
    if (maxLines == 0) {
        cerr << "Error: File empty or not found.\n";
        return 1;
    }

    DataRow* dataset = new DataRow[maxLines];
    ifstream inFile(csvFilename);
    string line;
    int idx = 0;

    // Clean, natural loop that parses generated datasets perfectly
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        if (line.back() == '\r') line.pop_back();

        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string part1 = line.substr(0, commaPos);
            string part2 = line.substr(commaPos + 1);

            // Simple verification: make sure it's not a text header row
            if (part1[0] >= '0' && part1[0] <= '9') {
                dataset[idx].intKey = stoll(part1);
                dataset[idx].strKey = part2;
                idx++;
            }
        }
    }
    inFile.close();

    int n = idx;
    if (n == 0) {
        cerr << "Error: No valid elements loaded.\n";
        delete[] dataset;
        return 1;
    }

    if (endRow >= n) endRow = n - 1;

    string stepOutputName = csvFilename.substr(0, csvFilename.find_last_of('.'))
                             + "_radix_sort_step_"
                             + to_string(startRow) + "_"
                             + to_string(endRow) + ".txt";

    radixSortStep(dataset, n, startRow, endRow, stepOutputName);
    delete[] dataset;

    return 0;
}
