/**

    Binary Search

    Problem: Given a SORTED array find the position of 'x' in the array. I
             If 'x' does not exist then find the value just smaller than 'x'

    Complexity: O(logN), where N is size of the array

    N.B- Array sorting time = O(NlogN)

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- algorithm function/s to be placed here start -------------------///

const int MAX_SIZE = 1000000 + 20;

int n, a[MAX_SIZE];

int bin_search(int x) {
// using binary search return position of x
// if 'x' does not exist, return position of element just smaller than 'x'
// array 'a[]' must be sorted

    sort(a, a+n);

    int left = 0, right = n-1, mid, resultPos = -1;

    while(left<=right) {

        mid = (left+right)/2;

        if(a[mid]==x){

            resultPos = mid;
            break;
        }

        else if(a[mid] < x) {

            resultPos = mid;
            left = mid+1;
        }

        else right = mid-1;
    }

    return resultPos;
}

///------------------- algorithm function/s to be placed here end -------------------///


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
// courtesy: https://codeforces.com/blog/entry/61587

    return uniform_int_distribution<int>(lower, upper)(rng);
}


void simulate(){
// simulate input to test the algorithm being implemented

    n = getRandomNumberInRange(5, 10);

    for(int i=0;i<n;i++){

        a[i] = getRandomNumberInRange(0, 100);
    }

    sort(a, a+n);
}


void exec(int T){
// execute the algorithm

    simulate();

    int x = getRandomNumberInRange(0, 100);

    cout<<"The array: ";
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<"\n\n";

    cout<<"Position of "<<x<<" or, element just smaller than "<<x<<" = ";
    cout<<bin_search(x)<<"\n";
}


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int t=1;

    //cin>>t;

    for(int T=1;T<=t;T++){

        exec(T);

    }

    return 0;
}

