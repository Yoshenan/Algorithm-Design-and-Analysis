#include <iostream>
#include<vector>
#include <fstream>
#include<time.h>
#include<sstream>
#include <chrono>
using namespace std;


int getMax(vector <int> &arr){
    int maxValue = arr[0];
    for(int num:arr){
        if(num>maxValue){
            maxValue = num;
        }
    }
  return maxValue;

}

void countingSortRadix(vector<int>&arr,int exp){
    int  n= arr.size();
     vector<int>output(n);
    int count[10] = {0};

    for(int i =0 ; i<n;i++){
        int digit = (arr[i]/exp)%10;
        count[digit]= count[digit]+1;
    }

    for(int i =1 ; i<10;i++){
        count[i]= count[i]+count[i-1];

    }

    for(int i =n-1;i>=0 ;i--){
        int digit = (arr[i]/exp)%10;
        output[count[digit]-1]=arr[i];
        count[digit]=count[digit]-1;
    }

    for (int i =0 ; i<n ; i++){
        arr[i]=output[i];
    }

}

void radixSortStep(vector<int>& arr, int n, int startRow, int endRow, ofstream& outputFile) {
    long long placement = 1;

    for (int d = 1; d <= 10; d++) {
        outputFile << "(processing from the rightmost character)\n";
        outputFile << "[";
        for (int i = startRow; i <= endRow && i < n; i++) {
            outputFile << arr[i];
            if (i < endRow && i < n - 1) outputFile << ", ";
        }
        outputFile << "] original\n";
        countingSortRadix(arr, placement);
        placement *= 10;
        outputFile << "[";
        for (int i = startRow; i <= endRow && i < n; i++) {
            outputFile << arr[i];
            if (i < endRow && i < n - 1) outputFile << ", ";
        }
        outputFile << "] d=" << (11 - d) << "\n";
    }
}


int main(){

   vector<int> data;


    ifstream inputFile("dataset_1000.csv");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open dataset_1000.csv!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
    stringstream ss(line);
    string value;
    while (getline(ss, value, ',')) {
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);

        if (!value.empty() && (isdigit(value[0]) || value[0] == '-')) {
            try {
                data.push_back(stoi(value));
            } catch (const std::exception& e) {
                cerr << "Skipping invalid value: " << value << endl;
            }
        }
    }
}
    inputFile.close();
    if (data.empty()) {
        cerr << "Warning: The dataset is empty!" << endl;
        return 1;
    }



    ofstream MyFile("radix_sorted_steps_1000000.csv");

    MyFile << "Before Sorting: ";
    for(int num:data){
        MyFile<<num<<",";
    }
    MyFile<<"\n";
    auto start = chrono::high_resolution_clock::now();

    radixSortStep(data, data.size(), 0 ,6, MyFile );

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> executionTime = end - start;


    MyFile<< "After Radix Sort: ";
    for(int num:data){
        MyFile<<num<<",";
    }
    MyFile<<"\n";
    MyFile << "Execution time: " << fixed << executionTime.count() << " seconds" << endl;

    MyFile.close();

    return 0;

}



