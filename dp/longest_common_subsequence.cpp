/**
    Find LCS length: https://onlinejudge.org/external/104/10405.pdf

    solved using recursive DP
**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- algorithm function/s to be placed here start -------------------///

const int MAX = 1000 + 20;

string s1, s2;

int dp[MAX][MAX];

void resetDp(){

    for(int i=0;i<MAX;i++)
    for(int j=0;j<MAX;j++) dp[i][j] = -1;
}

int maxOfThree(int a, int b, int c) {

    int maxx = max(a, b);
    maxx = max(maxx, c);
    return maxx;
}

int maxOfFour(int a, int b, int c, int d) {

    int maxx = max(a, b);
    maxx = max(maxx, c);
    maxx = max(maxx, d);

    return maxx;
}

int findLCS(int s1Idx, int s2Idx){

    if(dp[s1Idx][s2Idx]!=-1) return dp[s1Idx][s2Idx];

    if(s1Idx>=s1.size() || s2Idx>=s2.size()) dp[s1Idx][s2Idx] = 0;

    else if(s1[s1Idx]==s2[s2Idx]) dp[s1Idx][s2Idx] = maxOfFour( 1+findLCS(s1Idx+1, s2Idx+1), findLCS(s1Idx, s2Idx+1), findLCS(s1Idx+1, s2Idx), findLCS(s1Idx+1, s2Idx+1) );

    else dp[s1Idx][s2Idx] = maxOfThree( findLCS(s1Idx, s2Idx+1), findLCS(s1Idx+1, s2Idx), findLCS(s1Idx+1, s2Idx+1) );

    return dp[s1Idx][s2Idx];
}

///------------------- algorithm function/s to be placed here end -------------------///


void exec(int T){
// execute the algorithm

    while(getline(cin,s1)){
        getline(cin,s2);

        resetDp();

        cout<<findLCS(0, 0)<<"\n";
    }
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int t=1;

    //cin>>t;

    for(int T=1;T<=t;T++){

        exec(T);
    }

    return 0;
}
