#include <iostream>
#include<vector>
#include <fstream>
#include <chrono>
#include<sstream>
using namespace std;


long long  getMax(vector <long long > &arr){
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
        long long digit = (arr[i]/exp)%10;
        count[digit]= count[digit]+1;
    }

    for(long long i =1 ; i<10;i++){
        count[i]= count[i]+count[i-1];

    }

    for(long long i =n-1;i>=0 ;i--){
        long long digit = (arr[i]/exp)%10;
        output[count[digit]-1]=arr[i];
        count[digit]=count[digit]-1;
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

    vector<long long> data;
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

    ofstream MyFile("radix_sorted_" + filename);

    MyFile << "Before Sorting:\n";

    for (long long num : data) MyFile << "=\"" << num << "\"\n";

    auto start = chrono::high_resolution_clock::now();
    radixSort(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> executionTime = end - start;

    std::chrono::duration<double> elapsed = end - start;

    MyFile << "\nAfter Radix Sort:\n";
    for (long long num : data) MyFile << "=\"" << num << "\"\n";

    MyFile << "\n---\n";
    MyFile << "Execution time," << elapsed.count() << " seconds\n";
    MyFile.close();

    cout << "Success! Clean output generated without scientific notation.\n";
    return 0;


}



