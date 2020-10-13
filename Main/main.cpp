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

// array of concern
vector<st> arr;
void printArr(){
    if(arr.empty()) cout<<"array empty!";
    for(int i=0;i<arr.size();i++) cout<<arr[i].n<<" ";
    cout<<endl;
}



int main()
{
    cout<<"Hello world!";

    return 0;
}
