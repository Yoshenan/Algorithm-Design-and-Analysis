// *********************************************************
// Program: radixsort.cpp
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
#include<vector>
#include <fstream>
#include <chrono>
#include<sstream>
#include <unordered_map>
using namespace std;


long long getMax(vector <long long > &arr){
    long long maxValue = arr[0];
    for(long long num:arr){
        if(num>maxValue){
            maxValue = num;
        }
    }
  return maxValue;

}

void countingSortRadix(vector<long long>&arr,long long exp){
    long long  n= arr.size();
    vector<long long>output(n);
    long long count[10] = {0};

    for(long long i =0 ; i<n;i++){
        count[(arr[i] / exp) % 10]++;
    }
    for(long long i =1 ; i<10;i++){
        count[i] += count[i - 1];
    }
    for(long long i =n-1;i>=0 ;i--){
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (long long i =0 ; i<n ; i++){
        arr[i]=output[i];
    }
}

void radixSort(vector<long long>&arr){
  if (arr.empty())return;
  long long maxValue= getMax(arr);
  for(long long exp=1 ; maxValue/exp;exp*=10){
        countingSortRadix(arr,exp);
  }
}

int  main(){
    vector<long long > data;
    unordered_map<long long, string> stringLookUp;
    string line;

    const string filename = "dataset_10.csv";
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file!\n";
        return 1;
    }
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        size_t comma = line.find(',');
        string numStr = (comma != string::npos) ? line.substr(0, comma) : line;
        string remainingStr = (comma != string::npos) ? line.substr(comma + 1) : "";

        if (!numStr.empty() && isdigit(numStr[0])) {
           long long num = stoll(numStr);
           data.push_back(num);
           stringLookUp[num] = remainingStr;
        }
    }
    inFile.close();

    ofstream MyFile("radix_sorted_" + filename);
    auto start = chrono::high_resolution_clock::now();
    radixSort(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    MyFile << "Radix Sorted:\n";
    for (long long num : data) MyFile << num << ","<<stringLookUp[num]<<"\n";
    MyFile << "\n---\n";
    MyFile << "Execution time," << elapsed.count() << " seconds\n";
    MyFile.close();
    cout << "Output Generated to :" << "radix_sorted_" + filename;
    return 0;
}



