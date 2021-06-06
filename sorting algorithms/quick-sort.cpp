/**
    (Randomized) Quick sort

    best case time complexity: O(nlogn)
    BUT, worst case time complexity: O(n^2)

    requires less memory than merge sort,
    because no need to merge two array segments
**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/**
 Generate random number in given range
 courtesy- https://codeforces.com/blog/entry/61587
**/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    return uniform_int_distribution<int>(lower, upper)(rng);
}

///------------------- algorithm function/s to be placed here start -------------------///

// arrayt to be sorted
vector<int> arr;

void print_arr(){

    for(auto val : arr) cout<<val<<" ";
}

void reset() {

    arr.clear();
}

int partitionn(int l, int r) {

    int pivot_val = arr[r];

    int i = l-1;

    for(int j=l;j<r;j++){

        if(pivot_val>=arr[j]){

            i++;

            // swap positions i, j
            //swap(arr[i], arr[j]);
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    int pivot_val_idx = i+1;

    // swap positions pivot_val_idx, r
    //swap(arr[pivot_val_idx], arr[r]);
    int tmp = arr[pivot_val_idx];
    arr[pivot_val_idx] = arr[r];
    arr[r] = tmp;

    return pivot_val_idx;
}

// improves chances of avoiding worst case time complexity- O(n^2)
int randomized_partition(int l, int r) {

    int random_pos = getRandomNumberInRange(l, r);

    // swap random_pos with r
    int tmp = arr[r];
    arr[r] = arr[random_pos];
    arr[random_pos] = tmp;

    return partitionn(l, r);
}

void quick_sort(int l, int r) {

    if(l<r){

        int pivot_val_idx = randomized_partition(l, r);
        quick_sort(l, pivot_val_idx-1);
        quick_sort(pivot_val_idx+1, r);
    }
}

///------------------- algorithm function/s to be placed here end -------------------///

void simulate(){
// simulate input to test the algorithm being implemented

    int arr_size = getRandomNumberInRange(5, 10);
    for(int i=0;i<arr_size;i++){

        int val = getRandomNumberInRange(1, 20);

        arr.push_back(val);
    }
}

void exec(int T){
// execute the algorithm

    reset();

    simulate();

    cout<<"The array = ";
    print_arr();
    cout<<"\n\n";

    quick_sort(0, arr.size()-1);

    cout<<"Sorted array = ";
    print_arr();
    cout<<"\n\n";
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
