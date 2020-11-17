/**

    Topological sort using dfs
    Time complexity: O(V+E)

    concept only applicable for directed, unweighted graphs

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;



///------------------- topological sort with dfs start -------------------///

// maximum number of nodes that is supported
const int MAX_NUMBER_OF_NODES = 10000;


// edgesOfEachNode[u][i] is the i-th edge of the node 'u'
vector<int> edgesOfEachNode[MAX_NUMBER_OF_NODES];

void reset_graph(){
// reset the graph representation variable

    for(int i=0;i<MAX_NUMBER_OF_NODES;i++)
        edgesOfEachNode[i].clear();
}

void insertEdgeToGraph(int u, int v){
// insert edge: 'u' -> 'v' (unweighted)

    edgesOfEachNode[u].push_back(v);
}

void sort_adjacency_list(int n){
// sorts all graph representation adjacency list in ascending order
// so that vertex with equal order in topological list are sorted in ascending order
// call if needed after graph is set up

    for(int i=0;i<n;i++){
        sort(edgesOfEachNode[i].begin(), edgesOfEachNode[i].end());
        // topologicalList is reversed so need to reverse adjacency list as well
        reverse(edgesOfEachNode[i].begin(), edgesOfEachNode[i].end());
    }
}


// vertex visited or not
bool visited[MAX_NUMBER_OF_NODES];

void reset_visited(){

    for(int i=0;i<MAX_NUMBER_OF_NODES;i++)
        visited[i] = false;
}


// stores vertex maintaining their topological order
// vertex reached first is at top, reached last at bottom
vector<int> topologicalList;

void reset_topologicalList(){

    topologicalList.clear();
}



void dfs(int source){
// dfs starting from 'source' vertex

    visited[source] = true;

    int currentNode = source;

    for(int adjacentNode: edgesOfEachNode[source]){

        if(!visited[adjacentNode])
            dfs(adjacentNode);
    }

    // vertex whose children traversal finished first goes at first (but should go last)
    // so this list needs to be reserved
    topologicalList.push_back(currentNode);

}

void topological_sort(int n){
// call this method from main code

    reset_visited();
    reset_topologicalList();

    for(int i=0;i<n;i++){

        if(!visited[i])
            dfs(i);
    }

    // must reverse the topologicalList
    reverse(topologicalList.begin(), topologicalList.end());

}

///-------------------  topological sort with dfs end  -------------------///


void simulate(){
// simulate input to test the algorithm being implemented

/** simulation graph:

        0-->1<--3
        |\      ^\
        | \    /  \
        v  \  /    \
        4   v/      v
            2------>5
    */

    insertEdgeToGraph(0, 1);
    insertEdgeToGraph(0, 2);
    insertEdgeToGraph(0, 4);

    insertEdgeToGraph(2, 3);
    insertEdgeToGraph(2, 5);

    insertEdgeToGraph(3, 1);
    insertEdgeToGraph(3, 5);

}


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}

void exec(){
// execute the algorithm

    reset_graph();

    simulate();

    // optional
    //sort_adjacency_list(6);

    topological_sort(6);

    cout<<"Topologically sorted list:\n";
    for(int i=0;i<topologicalList.size();i++){

        int currV = topologicalList[i];
        cout<<currV<<" ";
    }
    cout<<"\n";
}


int main()
{
    exec();

    return 0;
}

