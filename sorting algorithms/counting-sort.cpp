/**

    Counting Sort
    Time Complexity: O(maxElement)
    Works only on array of positive integers

    (used mainly to apply radix sort)

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



///---------------------------- Counting sort start ----------------------------///

int getMax(vector<int> arr){
// return maximum element of integer array

    int maxx=arr[0];
    for(int i=0;i<arr.size();i++)
        if(maxx<arr[i]) maxx = arr[i];

    return maxx;
}

bool containsNegative(vector<int> arr){
// returns true if array has negative integers

    for(int i=1;i<arr.size();i++)
        if(arr[i]<0) return true;
    return false;
}


vector<int> countingSort(vector<int> arr)
{
// call this method from main code only
// sort array of POSIITVE integer in O(maxElement)

    if(containsNegative(arr)){
        // stop function here
        cout<<"cannot sort array with negative integers!\n";
        return arr;
    }

    int k = getMax(arr);

    // prefix sum array of the counts of each digit in 'arr'
    int d[k+1] = {0};

    // get counts of each integer in 'arr'
    for(int i=0;i<arr.size();i++) d[arr[i]]++;

    // do prefix array sum
    for(int i=1;i<k+1;i++) d[i]+=d[i-1];


    // main part starts from here


    // initialize the sorted array
    vector<int> sortedArr(arr.size());

    // loop starts from last position of 'arr' to maintain stable sort
    for(int i=arr.size()-1; i>=0; i--){

        int sortedPositionOfArrI = d[arr[i]]-1; // -1 for 0-based indexing

        sortedArr[sortedPositionOfArrI] = arr[i];

        // one arr[i] put in it's proper position
        // decrement
        d[arr[i]]--;
    }


    return sortedArr;

}

///---------------------------- Counting sort end ----------------------------///



vector<int> getNRandomNumbersInRange(int lower, int upper, int n){
// generate 'n' random numbers in the range- ['lower', 'upper']
    vector<int> randomNumbers;

    srand(time(0));

    while(n--) randomNumbers.push_back( rand()%(upper-lower+1)+lower );

    return randomNumbers;
}

void test(){

    arr = getNRandomNumbersInRange(0,100,10);

    cout<<"array: ";
    printArr();

    cout<<"\n(sorting...)\n";
    arr = countingSort(arr);

    cout<<"\nsorted array: ";
    printArr();

}


int main()
{
    test();

    return 0;
}
