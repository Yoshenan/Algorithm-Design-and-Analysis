#include <iostream>
#include<vector>
#include <fstream>
#include<time.h>
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

    vector<int> data;

    clock_t  start , end;
    double time;

    start = clock();

    ofstream MyFile("radix_sorted_dataset_1000000.csv");

    MyFile << "Before Sorting: ";
    for(int num:data){
        MyFile<<num<<",";
    }
    MyFile<<"\n";

    radixSort(data);

    end = clock();

    time= (double) (end-start)/CLOCKS_PER_SEC;

    MyFile<< "After Radix Sort: ";
    for(int num:data){
        MyFile<<num<<",";
    }
    MyFile<<"\n";
    MyFile<<"Execution time: "<<time<<endl;

    MyFile.close();

    return 0;


}



