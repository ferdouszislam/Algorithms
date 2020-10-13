/**

    nCr using Dynamic Programming in O(n*r)

**/

#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


///------------------------ nCr using DP start ------------------------///

int C[100][100];

int dpNCR(int n, int r)
{
// calculate nCr using 'C' matrix using dp

    if(C[n][r]!=(-1*INT_MAX)) return C[n][r];

    if(r==0 || n==r) C[n][r] = 1;

    else if(r==1) C[n][r] = n;

    else C[n][r] = dpNCR(n-1, r) + dpNCR(n-1, r-1);

    return C[n][r];

}

int nCr(int n, int r){
// initialize 'C' matrix and do dp
// call this method from main

    if(r>n){
        // stop here
        cout<<"\n"<<n<<"C"<<r<<" is not calculable!\n";
        return -1;
    }

    for(int i=0;i<=n;i++)
        for(int j=0;j<=r;j++)
            C[i][j] = (-1*INT_MAX);

    return dpNCR(n, r);

}


///------------------------ nCr using DP end ------------------------///

int getRandomNumbersInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']

    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}

void exec(){

    int n = getRandomNumbersInRange(6, 10);
    int r = getRandomNumbersInRange(1, 6);

    cout<<n<<"C"<<r<<" = "<<nCr(n, r)<<"\n";

}


int main()
{
    exec();

    return 0;
}
