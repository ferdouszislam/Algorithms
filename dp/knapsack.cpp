/**
    Knapsack problem: https://www.spoj.com/problems/LKS/
    
    solved using recursive DP and Map
    
**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- algorithm function/s to be placed here start -------------------///

const int MAX_WEIGHT = 2000000 + 5, MAX_ITEM_NUMBERS = 500 + 5;

map<int, int> dp[MAX_ITEM_NUMBERS];

void resetDp(){

    for(int i=0;i<MAX_ITEM_NUMBERS;i++) dp[i].clear();
}

struct Item{

    int value, weight;

    Item(){}

    Item(int _value, int _weight){

        value = _value;
        weight = _weight;
    }
};

vector<Item> items;

int findMaxValue(int itemIdx, int capacity){

    if(itemIdx>=items.size() || capacity<=0) return 0;

    else if(dp[itemIdx].find(capacity)!=dp[itemIdx].end()) return dp[itemIdx][capacity];

    else{

        int capacityAfterTakingItemAtIdx = capacity - items[itemIdx].weight;
        int valueAfterTakingItemAtIdx = items[itemIdx].value + findMaxValue(itemIdx+1, capacityAfterTakingItemAtIdx);
        int valueAfterNotTakingItemAtIdx = findMaxValue(itemIdx+1, capacity);

        if(capacityAfterTakingItemAtIdx>=0) dp[itemIdx][capacity] = max(valueAfterTakingItemAtIdx, valueAfterNotTakingItemAtIdx);

        else dp[itemIdx][capacity] = valueAfterNotTakingItemAtIdx;
    }

    return dp[itemIdx][capacity];
}

///------------------- algorithm function/s to be placed here end -------------------///


void exec(int T){
// execute the algorithm

    int n, k;
    cin>>k>>n;

    while(n--){
        int v, w;
        cin>>v>>w;
        items.push_back(Item(v, w));
    }

    resetDp();

    cout<<findMaxValue(0, k)<<"\n";
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
