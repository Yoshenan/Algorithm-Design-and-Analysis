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
#include <cstdlib>
#include <string>

using namespace std;

// --- Global variables ---
long long  minVal = 1000000000;
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
    cout << "Enter the number of random numbers to generate: ";
    cin >> inputNum;
    cout << "Generating random numbers" << endl;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Creating the file
    string datasetName = createFile("dataset_" + to_string(inputNum));
    ofstream datasetFile(datasetName + ".csv", ios::app);
    if (!datasetFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    for (int i = 0; i < 7; i++) { // Writes the first seven fixed numbers

        writeTo(datasetFile, firstSevenInt[i] , firstSevenChar[i]);
    }
    for (int i = 7; i < inputNum; i++) {
        long long uniqueNum = (((long long)rand() * rand()) % (999999999 - 10000000 + 1) + minVal);

        writeTo(datasetFile, to_string(uniqueNum), charRand());
    }

    datasetFile.close();

    cout << "Random numbers generated and written to file: " << datasetName << ".csv" <<"\n" ;
}


/* -- References -- */
// https://cplusplus.com/reference/cstdlib/rand/
// https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand
// https://stackoverflow.com/questions/4859089/always-repeated-numbers-given-by-rand
// https://www.w3schools.com/cpp/cpp_files.asp
