/* 
Hakeem - 243UC247CZ
Seed   - 2431324736
Dataset generator for algorithm testing
12 June 2026
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// --- Global variables ---
int minVal = 1000000000;
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

void writeTo(string fileName, string data) { // Writes data to the file
    ofstream datasetFile(fileName + ".csv", ios::app);
    datasetFile << data << endl;
    datasetFile.close();
}

int main() {
    srand((unsigned int)2431324736); // rand() seed

    // Input
    cout << "Enter the number of random numbers to generate: ";
    cin >> inputNum;
    cout << "Generating random numbers" << endl;

    // Creating the file
    string datasetName = createFile("dataset_" + to_string(inputNum));

    //  Writing data to file
    for (int i = 0; i < 7; i++) { // Writes the first seven fixed numbers
        writeTo(datasetName, firstSevenInt[i] + "," + firstSevenChar[i]);
    }
    for (int i = 7; i <= inputNum; i++) { // writes the rest to file
        writeTo(datasetName, to_string(rand() % 10000000000 + minVal) + "," + charRand());
        }

    cout << "Random numbers generated and written to file: " << datasetName << ".csv" << endl;
}

/* -- References -- */
// https://cplusplus.com/reference/cstdlib/rand/
// https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand
// https://stackoverflow.com/questions/4859089/always-repeated-numbers-given-by-rand
// https://www.w3schools.com/cpp/cpp_files.asp