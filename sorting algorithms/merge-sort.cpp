/**

    Merge sort
    Time complexity: O(NlogN)

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct st{

    int n;

    st(){}

    st(int nn){
        n = nn;
    }

};

// array to be sorted
vector<st> arr;
void printArr(){
    if(arr.empty()) cout<<"array empty!";
    for(int i=0;i<arr.size();i++) cout<<arr[i].n<<" ";
    cout<<endl;
}


///------------------Merge Sort------------------///

st getSentinel(){
// returns largest possible value of 'st' element
    return st(INT_MAX);
}

bool isGreater(st a, st b){
// return true if a > b

    if (a.n>b.n) return true;

    return false;
}



void mergee(int l, int m, int r)
{
// merge the two sub-arrays arr[l..m] and arr[m+1...r] in a sorted manner

    int n1 = m-l+1;
    int n2 = r-m;

    st L[n1+1], R[n2+1]; // +1 for the sentinel(infinity)

    for(int i=0;i<n1;i++)
        L[i] = arr[l+i];

    for(int i=0;i<n2;i++)
        R[i] = arr[m+1+i];

    // sentinel = largest possible value
    L[n1] = getSentinel();
    R[n2] = getSentinel();

    int Li=0, Ri=0;

    for(int i=l;i<=r;i++){

        if( !isGreater(L[Li], R[Ri]) ){
            arr[i] = L[Li];
            Li++;
        }

        else{
            arr[i] = R[Ri];
            Ri++;
        }

    }

}

void mergeSort(int l, int r)
{
// call only this function from main

    if(l<r){
        int m = (l+r)/2;
        mergeSort(l, m);
        mergeSort(m+1, r);
        mergee(l, m, r);
    }
}


///------------------Merge Sort End------------------///

void simulate(){

    for(int i=10;i>=1;i--)
        arr.push_back(st(i));

}

void exec(){

    cout<<"plain array: ";
    printArr();

    cout<<"\n(sorting...)\n\n";
    mergeSort(0, arr.size()-1);

    cout<<"sorted array: ";
    printArr();

}


int main()
{
    exec();

    return 0;
}
