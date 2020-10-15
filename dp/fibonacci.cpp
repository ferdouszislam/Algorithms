/**

    fibonacci(n) using Dynamic Programming in O(n)

**/

#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


///------------------------ fibonacci using DP start ------------------------///

int F[100000];

int dpFibo(int n)
{
// calculate nCr using 'C' matrix using dp

    if(F[n]!=(-1*INT_MAX)) return F[n];

    if(n==1 || n==2) F[n] = 1;

    else F[n] = dpFibo(n-1) + dpFibo(n-2);

    return F[n];

}

int fibo(int n){
// initialize 'C' matrix and do dp
// call this method from main

    if(n>39){ // fibonacci(>39) does not fit in int datatype
        // stop here
        cout<<"\nfibonacci("<<n<<") is out of range!\n";
        return -1;
    }

    for(int i=0;i<=n;i++)
        F[i] = (-1*INT_MAX);

    return dpFibo(n);

}


///------------------------ fibonacci using DP end ------------------------///

int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']

    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}

void exec(){

    int n = getRandomNumberInRange(1, 39);

    cout<<"fibonacci("<<n<<") = "<<fibo(n)<<"\n";

}


int main()
{
    exec();

    return 0;
}
