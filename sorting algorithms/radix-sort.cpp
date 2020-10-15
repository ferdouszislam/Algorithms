/**

    Radix Sort
    Time Complexity: O(N*maxDigit)
    Works only on array of positive integers

**/

#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// array of concern
vector<int> arr;
void printArr(){
    if(arr.empty()) cout<<"array empty!";
    for(int i=0;i<arr.size();i++) cout<<arr[i]<<" ";
    cout<<endl;
}



///---------------------------- Radix sort start ----------------------------///

int getMax(vector<int> arr){
// return maximum element of integer array

    int maxx=arr[0];
    for(int i=1;i<arr.size();i++)
        if(maxx<arr[i]) maxx = arr[i];

    return maxx;
}

bool containsNegative(vector<int> arr){
// returns true if array has negative integers

    for(int i=0;i<arr.size();i++)
        if(arr[i]<0) return true;
    return false;
}

int getMaxDigitCount(vector<int> arr){

    int ret=0;

    for(int i=0;i<arr.size();i++){
        int digitCount = 0;
        while(arr[i]){
            arr[i]/=10;
            digitCount++;
        }
        if(digitCount>ret) ret = digitCount;
    }

    return ret;
}

vector<int> countingSortBasedOnDigitPosition(vector<int> arr, int digitPosition){
// sort 'arr' based on it's 'digitPosition'th digit in O(n)

    // this array will contain 'digitPosition'th digit of arr[i]
    // which will be used for generating prefix sum array and sorting
    vector<int> digitArr(arr.size());

    // digitArr[i] = 'digitPosition'th digit of arr[i]
    int p = (int)pow(10,digitPosition);
    for(int i=0;i<arr.size();i++)
        digitArr[i] = (arr[i]/p)%10;


    int k = getMax(digitArr);

    // prefix sum array of the counts of each digit in 'digitArr'
    int d[k+1] = {0};

    // get counts of each integer in 'digitArr'
    for(int i=0;i<digitArr.size();i++) d[digitArr[i]]++;

    // do prefix array sum
    for(int i=1;i<k+1;i++) d[i]+=d[i-1];


    // main part starts from here


    // initialize the sorted array
    vector<int> sortedArr(arr.size());

    // loop starts from last position of 'digitArr' to maintain stable sort
    for(int i=digitArr.size()-1; i>=0; i--){

        // sorted position is calculated based on 'digitArr'
        int sortedPositionOfArrI = d[digitArr[i]]-1; // -1 for 0-based indexing

        // 'arr[i]' is used here since 'arr' is the actual array that is rearranged by sorting 'digitArr'
        sortedArr[sortedPositionOfArrI] = arr[i];

        // one digitArr[i] put in it's proper position
        // decrement
        d[digitArr[i]]--;
    }


    return sortedArr;

}


vector<int> radixSort(vector<int> arr)
{
// call this method from main code only
// sorts array of POSITIVE integers in O(n*maxDigitCount)

    if(containsNegative(arr)){
        // stop function here
        cout<<"cannot sort array with negative integers!\n";
        return arr;
    }

    int maxDigitCount = getMaxDigitCount(arr);

    for(int i=0;i<maxDigitCount;i++)
        arr = countingSortBasedOnDigitPosition(arr, i);

    return arr;

}


///---------------------------- Radix sort end ----------------------------///



vector<int> getNRandomNumbersInRange(int lower, int upper, int n){
// generate 'n' random numbers in the range- ['lower', 'upper']
    vector<int> randomNumbers;

    srand(time(0));

    while(n--) randomNumbers.push_back( rand()%(upper-lower+1)+lower );

    return randomNumbers;
}

void exec(){

    arr = getNRandomNumbersInRange(1,100000,10);

    cout<<"array: ";
    printArr();

    cout<<"\n(sorting...)\n";
    arr = radixSort(arr);

    cout<<"\nsorted array: ";
    printArr();

}


int main()
{
    exec();

    return 0;
}
