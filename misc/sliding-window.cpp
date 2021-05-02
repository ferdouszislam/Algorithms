/**

    Sliding Window Technique

    Problem: Given an array find maximum sum of 'k' consecutive elements

    Complexity: O(2*N), where N is size of the array

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- algorithm function/s to be placed here start -------------------///

const int MAX_SIZE = 1000000 + 20;

int n, a[MAX_SIZE];

int maximumSumOfKConsecutiveElements(int k) {

    int leftIdx = 0, rightIdx = 0, currentWindowSum = a[0], maxWindowSum = 0;

    while(leftIdx<n && rightIdx<n) {

        int currentWindowLength = rightIdx-leftIdx+1;

        if(currentWindowLength==k) {

            maxWindowSum = max(maxWindowSum, currentWindowSum);

            if(leftIdx==rightIdx) {
                rightIdx++;
                if(rightIdx<n) currentWindowSum+=a[rightIdx];
            }
            leftIdx++;
            currentWindowSum-=a[leftIdx];
        }

        else {

            rightIdx++;
            if(rightIdx<n) currentWindowSum+=a[rightIdx];
        }
    }

    return maxWindowSum;
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
}


void exec(int T){
// execute the algorithm

    simulate();

    int k = getRandomNumberInRange(0, 5);

    cout<<"The array: ";
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<"\n\n";

    cout<<"Maximum sum of "<<k<<" consecutive elements = ";
    cout<<maximumSumOfKConsecutiveElements(k)<<"\n";
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

