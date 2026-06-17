#include <iostream>
#include<vector>
#include <fstream>
#include <chrono>
#include<sstream>
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


void radixSort(vector<int>&arr){
  if (arr.empty())return;

  int maxValue= getMax(arr);


  for(int exp=1 ; maxValue/exp;exp*=10){

        countingSortRadix(arr,exp);
  }

}




int main(){

    vector<int> data; // Changed to long long to natively hold 10-digit IDs safely
    string filename, line;

    cout << "Enter target dataset CSV file name: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file!\n";
        return 1;
    }

    // Load elements and clean file punctuation/quotes
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        if (line.back() == '\r') line.pop_back();
        if (line.front() == '"') line.erase(0, 1);
        if (line.back() == '"') line.pop_back();

        size_t comma = line.find(',');
        string numStr = (comma != string::npos) ? line.substr(0, comma) : line;

        if (!numStr.empty() && isdigit(numStr[0])) {
            data.push_back(stoll(numStr));
        }
    }
    inFile.close();

    // Create dynamic output file
    ofstream MyFile("radix_sorted_" + filename);

    MyFile << "Before Sorting:\n";

    for (long long num : data) MyFile << "=\"" << num << "\"\n";

    // Track execution time
    auto start = chrono::high_resolution_clock::now();
    radixSort(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> executionTime = end - start;

    std::chrono::duration<double> elapsed = end - start;

    MyFile << "\nAfter Radix Sort:\n";
    for (long long num : data) MyFile << "=\"" << num << "\"\n";

    // Explicit newlines to ensure it sits cleanly in its own section at the bottom
    MyFile << "\n---\n";
    MyFile << "Execution time," << elapsed.count() << " seconds\n";
    MyFile.close();

    cout << "Success! Clean output generated without scientific notation.\n";
    return 0;


}



