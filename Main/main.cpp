/**

    template for testing/using the algorithms

    import(copy-paste the methods ;v) algorithm/s and use here

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- algorithm function/s to be placed here start -------------------///



///------------------- algorithm function/s to be placed here end -------------------///


void simulate(){
// simulate input to test the algorithm being implemented
}


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}


void exec(int T){
// execute the algorithm



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
