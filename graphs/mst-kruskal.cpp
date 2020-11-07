/**

    Kruskal's Algorithm for Minimum Spanning Tree (using DSU)

    Time Complexity- O(MlogN); M: number of edges, N: number of vertices

    works with undirected graphs only

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// maximum number of elements/nodes
const int MAX_NUMBER_OF_ELEMENTS = 100000+5;

///------------------- dsu start -------------------///

// parent[v] = direct parent of the element 'v'
int parent[MAX_NUMBER_OF_ELEMENTS];
// counter[v] = number of components the set/tree with root 'v' has
int counter[MAX_NUMBER_OF_ELEMENTS];

// true if graph contains cycles
bool cycleExists;

// number of sub-sets/trees in dsu
int numberOfSubSets;

void reset_dsu(){
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

///-------------------  dsu end  -------------------///



///------------------- MST-Kruskal start -------------------///

struct Edge{

    int u, v, cost;

    Edge(){}

    Edge(int _u, int _v, int _c){
        u = _u;
        v = _v;
        cost = _c;
    }

    // when sorting edge with less cost should come before
    bool operator < (const Edge& other) const { return cost < other.cost; }

};

// all edges of the graph
vector<Edge> graph;

void resetGraph(){ graph.clear(); }

void insertToGraph_Undirected(int u, int v,int c){
    graph.push_back(Edge(u, v, c));
    graph.push_back(Edge(v, u, c));
}

// cost of full mst
int mstTotalCost;
// edges that the mst contains
vector<Edge> mstEdges;

void mst_Kruskal(int numberOfNodes){
// call this from main code after graph has been setup

    reset_dsu();
    mstTotalCost = 0;
    mstEdges.clear();

    for(int i=0;i<numberOfNodes;i++)
        make_set(i);

    sort(graph.begin(), graph.end());

    for(Edge e: graph){

        if( !belongsToSameSet(e.u, e.v) ){

            mstTotalCost+=e.cost;

            mstEdges.push_back(e);

            union_sets(e.u, e.v);

        }

    }

}

///-------------------  MST-Kruskal end  -------------------///


void simulate(){
// simulate input to test the algorithm being implemented

    /** simulation graph:

                  (10)    (1')  (20)  (1')
                0-------1-----2----6------7
                |\(6)  /(2')  |   /
            (3')| \   /  (12')|  /(3')
                |  \ /        | /
                5---3---------4
                 (1')   (16)
    */

    // 0---1
    insertToGraph_Undirected(0, 1, 10);
    // 0---3
    insertToGraph_Undirected(0, 3, 6);
    // 0---5
    insertToGraph_Undirected(0, 5, 3);
    // 1---2
    insertToGraph_Undirected(1, 2, 1);
    // 1---3
    insertToGraph_Undirected(1, 3, 2);
    // 2---6
    insertToGraph_Undirected(2, 6, 20);
    // 2---4
    insertToGraph_Undirected(2, 4, 12);
    // 3---4
    insertToGraph_Undirected(3, 4, 16);
    // 4---6
    insertToGraph_Undirected(4, 6, 3);
    // 5---3
    insertToGraph_Undirected(5, 3, 1);
    // 6---7
    insertToGraph_Undirected(6, 7, 1);

}


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}


void exec(){
// execute the algorithm

    resetGraph();

    simulate();

    mst_Kruskal(8);

    cout<<"\nMST full path cost = "<<mstTotalCost<<"\n";

    cout<<"\nEdges in MST:\n";
    for(Edge e: mstEdges)
        cout<<e.u<<" --- "<<e.v<<" ("<<e.cost<<")\n";

}


int main()
{
    exec();

    return 0;
}

