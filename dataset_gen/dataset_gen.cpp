// *********************************************************
// Program: dataset_gen.cpp
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
// Member_2: Implementation of radix sort and radix sort step
// Member_3: Implementation of heap sort and heap sort step
// Member_4: Implementation of hash table and hash table search
// *********************************************************

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <chrono>

using namespace std;

class UniqueLCG { // to ensure unique random numbers
public:
    static const uint64_t RANGE  = 9000000000ULL;
    static const uint64_t OFFSET = 1000000000ULL;
    static const uint64_t A      = 1000000021ULL;
    static const uint64_t C      = 1013904223ULL;

    explicit UniqueLCG(uint64_t seed) : state_(seed % RANGE), count_(0) {}

    // Returns next unique integer
    long long next() {
        state_ = (A * state_ + C) % RANGE;
        ++count_;
        return static_cast<long long>(state_ + OFFSET);
    }
    bool hasNext() const { return count_ < RANGE; }

private:
    uint64_t state_;
    uint64_t count_;
};

// Combines three rand() calls cus rand() does not have enough range
static uint64_t rand64() {
    return ((uint64_t)rand() << 30)
         | ((uint64_t)rand() << 15)
         |  (uint64_t)rand();
}

// --- Global variables ---
long long minVal = 1000000000;
int inputNum;

char charArr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                'h', 'i', 'j', 'k', 'l', 'm', 'n',
                'o', 'p', 'q', 'r', 's', 't',
                'u', 'v', 'w', 'x', 'y', 'z'};
string fiveChar = "";

string firstSevenInt[] = {"1000000038",
                        "1000000009",
                        "1000000048",
                        "1000000037",
                        "1000000155",
                        "1000000197",
                        "1000000065"};
string firstSevenChar[] = {"uoren",
                        "igerk",
                        "qouez",
                        "sitew",
                        "gslag",
                        "ufnja",
                        "rezop"};

string fileName = "";

// --- Funcs ---
string charRand() { // Generates a random string of 5 characters
    fiveChar = "";
    for (int i = 0; i < 5; i++){
        fiveChar += charArr[rand() % 26];
    }
    return fiveChar;
}

string createFile(string fileName) { // File creation
    ofstream datasetFile(fileName + ".csv");
    datasetFile.close();
    return fileName;
}

void writeTo(ofstream &file, string data1, string data2) {
    file << data1 << "," << data2 << "\n";
}

int main() {

    srand((unsigned int)2431324736); // rand() seed

    // Input
    inputNum = 1000;
    // inputNum = 2000;
    // inputNum = 5000;
    // inputNum = 10000;
    // inputNum = 25000;
    // inputNum = 50000;
    // inputNum = 100000;
    // inputNum = 250000;
    // inputNum = 500000;
    // inputNum = 1000000;
    // inputNum = 5000000;
    // inputNum = 25000000;
    cout << "Generating " << inputNum << " random numbers..." << endl;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Creating the file
    string datasetName = createFile("dataset_" + to_string(inputNum));
    ofstream datasetFile(datasetName + ".csv", ios::app);
    if (!datasetFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    auto start = std::chrono::system_clock::now(); // Generation start time

    // Write the first seven fixed entries
    for (int i = 0; i < 7; i++) {
        writeTo(datasetFile, firstSevenInt[i], firstSevenChar[i]);
    }

    // Seeds LCG with rand64 which is seeded by srand
    UniqueLCG lcg(rand64());

    // Generate remaining entries
    for (int i = 7; i < inputNum; i++) {
        long long uniqueNum = lcg.next();
        writeTo(datasetFile, to_string(uniqueNum), charRand());
    }

    datasetFile.close();

    auto end = chrono::system_clock::now();
    auto genTime = chrono::duration_cast<std::chrono::milliseconds>(end - start); // Generation end time
    

    cout << "Dataset generated, written to: " << datasetName << ".csv" << "\n";
    cout << "Runtime: " << genTime.count() << " ms" << endl;
}


/* -- References -- */
// https://cplusplus.com/reference/cstdlib/rand/
// https://en.wikipedia.org/wiki/Linear_congruential_generator
// https://stackoverflow.com/questions/4859089/always-repeated-numbers-given-by-rand
// https://www.w3schools.com/cpp/cpp_files.asp
