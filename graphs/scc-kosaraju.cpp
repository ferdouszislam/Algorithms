/**

    Strongly Connected Components - Kosaraju
    using Topological Sort & DFS

    Time Complexity: O(V+E)

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- algorithm function/s to be placed here start -------------------///


///-------------------------------------- Topological Sort start --------------------------------------///
// maximum number of nodes that is supported
const int MAX_NUMBER_OF_NODES = 1000+5;


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
// used in both dfs_ts() and dfs_scc()
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


void dfs_ts(int source){
// do not call from main code
// dfs for generating 'topologicalList' vertexes list

    visited[source] = true;

    int currentNode = source;

    for(int adjacentNode: edgesOfEachNode[source]){

        if(!visited[adjacentNode])
            dfs_ts(adjacentNode);
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
            dfs_ts(i);
    }

    // must reverse the topologicalList
    reverse(topologicalList.begin(), topologicalList.end());

}
///--------------------------------------  Topological Sort end  --------------------------------------///


///-------------------------------------- Strongly Connected Components - Kosaraju start --------------------------------------///
// reversed edges of the original graph
vector<int> reverse_edges[MAX_NUMBER_OF_NODES];

// list of all strongly connected components
vector<vector<int>> stronglyConnectedComponentsCollection;
// current strongly connected component list that dfs_scc() is building
vector<int> currentStronglyConnectedComponents;

void reset_scc(){

    for(int i=0;i<MAX_NUMBER_OF_NODES;i++)
        reverse_edges[i].clear();

    stronglyConnectedComponentsCollection.clear();
}

void dfs_scc(int source){
// do not call from main code
// dfs for generating 'currentStronglyConnected' vertexes list

    visited[source] = true;

    int currentNode = source;

    currentStronglyConnectedComponents.push_back(currentNode);

    for(int adjacentNode: reverse_edges[currentNode]){

        if(!visited[adjacentNode])
            dfs_scc(adjacentNode);
    }

}

void scc_kosaraju(int numberOfNodes){
// call from main code to get the scc collection list

    topological_sort(numberOfNodes);

    reset_scc();

    for(int i=0;i<numberOfNodes;i++){
        int u = i;
        for(int j=0;j<edgesOfEachNode[u].size();j++){
            int v = edgesOfEachNode[u][j];

            reverse_edges[v].push_back(u);

        }
    }

    reset_visited();

    for(int vertex: topologicalList){

        if(!visited[vertex]){

            currentStronglyConnectedComponents.clear();
            dfs_scc(vertex);

            stronglyConnectedComponentsCollection.push_back(currentStronglyConnectedComponents);
        }
    }

}
///--------------------------------------  Strongly Connected Components - Kosaraju end  --------------------------------------///


///-------------------  algorithm function/s to be placed here end  -------------------///


void simulate(){
// simulate input to test the algorithm being implemented

/** simulation graph:
        -----
        |   |
        v   |
        0-->1<--3
        |\      ^\
        | \    /  \
        v  \  /    \          6<-->7--->8
        4   v/      v
        ^   2------>5
        |           ^              9
        |           |
        -------------
    */

    insertEdgeToGraph(0, 1);
    insertEdgeToGraph(0, 2);
    insertEdgeToGraph(0, 4);

    insertEdgeToGraph(1, 0);

    insertEdgeToGraph(2, 3);
    insertEdgeToGraph(2, 5);

    insertEdgeToGraph(3, 1);
    insertEdgeToGraph(3, 5);

    insertEdgeToGraph(4, 5);

    insertEdgeToGraph(5, 4);

    insertEdgeToGraph(6, 7);

    insertEdgeToGraph(7, 6);
    insertEdgeToGraph(7, 8);

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

    scc_kosaraju(10);

    cout<<"Strongly Connected Components:\n";
    for(vector<int> stronglyConnectedComponent : stronglyConnectedComponentsCollection){

        for(int node: stronglyConnectedComponent)
            cout<<node<<" ";

        cout<<"\n";
    }

}


int main()
{
    exec();

    return 0;
}

