/**

    Disjoint set union with path compression
    Nodes can be 0 or 1 based
    Amortized time complexity of O(α(n)), where α(n) is the inverse Ackermann function ( i.e close to O(1) )

    courtesy-
    https://cp-algorithms.com/data_structures/disjoint_set_union.html,
    https://github.com/sgtlaugh/algovault/blob/master/code_library/disjoint_set.cpp

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///--------------------------------------------- Disjoint-Set-Union start ---------------------------------------------///

// maximum number of elements/nodes
const int MAX_NUMBER_OF_ELEMENTS = 100000+5;

// parent[v] = direct parent of the element 'v'
int parent[MAX_NUMBER_OF_ELEMENTS];
// counter[v] = number of components the set/tree with root 'v' has
int counter[MAX_NUMBER_OF_ELEMENTS];

// true if graph contains cycles
bool cycleExists;

// number of sub-sets/trees in dsu
int numberOfSubSets;

void reset(){
// reset the DSU
    for(int i=0;i<MAX_NUMBER_OF_ELEMENTS;i++){
        parent[i] = -1;
        counter[i] = 0;
    }
    cycleExists = false;
    numberOfSubSets = 0;
}


void make_set(int v){
// create new set with only element 'v'
// no need to call this from main code (no problem if you do either)

    if(parent[v]==-1){ // if parent[v]!=-1 then the element already exists in the DSU
        parent[v] = v;
        counter[v] = 1;
        numberOfSubSets++;
    }

}


int find_set(int v){
// find the root(absolute parent) of the set/tree that 'v' belongs to
// a set/tree is represented by it's root

    if(v==parent[v]) // parent of the root of the set/tree is the root itself
        return v;

    // parentV = absolute parent of the set/tree 'v' belongs to
    int parentV = find_set(parent[v]);

    // doing this takes all the children of the currently traversing branch to one level down of root
    // for more explanation see example: https://cp-algorithms.com/data_structures/disjoint_set_union.html
    // this reduces time complexity to almost O(1)
    parent[v] = parentV;

    return parentV;

}


void union_sets(int a, int b){
// connect the two sets/trees 'a' and 'b' belong to
// call this from the main code

    // in case 'a' and 'b' dont belong to any sets/trees in dsu
    make_set(a);
    make_set(b);

    int rootOfSetABelongTo = find_set(a);
    int rootOfSetBBelongTo = find_set(b);

    if(rootOfSetABelongTo!=rootOfSetBBelongTo){

        // root of the set that 'b' belongs to = root of the set that 'a' belong to
        parent[rootOfSetBBelongTo] = rootOfSetABelongTo;

        // all of a's set/tree elements now belong to b's set/tree
        counter[rootOfSetABelongTo]+=counter[rootOfSetBBelongTo];
        // there is no set/tree rooted at a's root now
        counter[rootOfSetBBelongTo] = 0;

        // two subsets merged to create one so decrement by 1
        numberOfSubSets--;

    }

    else{
        // connecting 'a' and 'b' that already belong to the same tree creates a cycle
        // for this to work,
        // this function MUST NOT be be called with the pair 'a' and 'b' (not even with 'b', 'a') more than once
        cycleExists = true;
    }
}


bool belongsToSameSet(int a, int b){
// returns true if 'a' and 'b' belong to the same tree
// i.e they are connected

    // 'a', 'b' are not in the dsu
    // probably never the case
    if(parent[a]==-1 || parent[b]==-1) return false;

    // belongs to the same set iff their roots are same
    return find_set(a) == find_set(b);

}

int numberOfNodes(int v){
// return the number of nodes the set/tree containing 'v' has

    // in case 'v' is not in the dsu
    // probably never the case
    if(parent[v]==-1) return 0;

    return counter[find_set(v)];

}

///--------------------------------------------- Disjoint-Set-Union end ---------------------------------------------///


void simulate(){
// simulate input to test the algorithm being implemented

    /**
        simulated graph:

            0-----1          6----7---8     10---11---13
            |      \              |  /      | \    \
            |       4---5         | /       |  15   12
            |      /              9         14
            2-----3

    **/

    vector<pair<int,int>> edges;

    edges.push_back({0,1});
    edges.push_back({0,2});
    edges.push_back({1,4});
    edges.push_back({2,3});
    edges.push_back({3,4});
    edges.push_back({4,5});

    edges.push_back({6,7});
    edges.push_back({7,8});
    edges.push_back({7,9});
    edges.push_back({8,9});

    edges.push_back({10,11});
    edges.push_back({10,15});
    edges.push_back({10,14});
    edges.push_back({11,12});
    edges.push_back({11,13});

    for(int i=0;i<edges.size();i++)
        union_sets(edges[i].first, edges[i].second);

}


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}


void exec(){
// execute the algorithm

    reset();

    simulate();

    pair<int,int> test[3] = { {0, 5}, {10, 12}, {14, 9} };

    for(int i=0;i<3;i++){
        int a = test[i].first, b = test[i].second;

        cout<<a<<" and "<<b<<" are ";
        (belongsToSameSet(a, b)) ? cout<<"connected!(# of nodes in it's tree = "<<numberOfNodes(a)<<")\n" : cout<<"not connected.\n";
    }

    cycleExists ? cout<<"\ncycle found!\n" : cout<<"\nno cycles in graph.\n";

}


int main()
{
    exec();

    return 0;
}
