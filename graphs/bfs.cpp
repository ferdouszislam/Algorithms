/**

    BFS (0-1 BFS)
    shortest path traversal 0 or, 1 weight graph
    Time Complexity: O(V+E)

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- BFS start -------------------///

// maximum number of nodes that is supported
const int MAX_NUMBER_OF_NODES = 10000;


// variables used for graph representation
// edgesOfEachNode[u][i] is the i-th edge of the node 'u'
// distanceOfEachEdge[u][i] is the distance between node 'u' and it's i-th edge
vector<int> edgesOfEachNode[MAX_NUMBER_OF_NODES];
vector<int> distanceOfEachEdge[MAX_NUMBER_OF_NODES];
// distance of each node in the graph while traversing from 'source'
int dist[MAX_NUMBER_OF_NODES];

void insertToGraph(int u, int v, int c){
// insert new edge u->v at cost c to graph
    edgesOfEachNode[u].push_back(v);
    distanceOfEachEdge[u].push_back(c);
}

void clearGraph(){
// clears/resets graph representation variables
// must be called in main code before each new graph
    for(int i=0;i<MAX_NUMBER_OF_NODES;i++){
        edgesOfEachNode[i].clear();
        distanceOfEachEdge[i].clear();
    }
}


void bfs(int source, int numberOfNodes)
{
// call this from the main code

    // initially nodes are unreachable(distance is infinity)
    for(int i=0;i<numberOfNodes;i++) dist[i] = INT_MAX;

    deque<int> q;

    q.push_back(source);
    dist[source] = 0;

    while(!q.empty()){

        int currNode = q.front();
        q.pop_front();

        for(int i=0;i<edgesOfEachNode[currNode].size();i++){

            int adjNode, cost;

            adjNode = edgesOfEachNode[currNode][i];
            cost = distanceOfEachEdge[currNode][i];

            if( dist[adjNode] > dist[currNode] + cost ){

                dist[adjNode] = dist[currNode] + cost;

                // to enable 0-1 bfs
                (cost == 0) ? q.push_front(adjNode) : q.push_back(adjNode);
            }

        }

    }

}



///------------------- BFS end -------------------///


void simulate(){
// simulate input to test the algorithm being implemented

/** simulation graph:

                   (1)    (1)
                0-------1-----2
                |\(0)  /      |
             (1)| \   /(0)    |(0)
                |  \ /        |
                5---3---------4
                 (1)    (0)
    */

    // 0 -> 1
    insertToGraph(0, 1, 1);
    // 0 -> 3
    insertToGraph(0, 3, 0);
    // 0 -> 5
    insertToGraph(0, 5, 1);

    // 1 -> 0
    insertToGraph(1, 0, 1);
    // 1 -> 2
    insertToGraph(1, 2, 1);
    // 1 -> 3
    insertToGraph(1, 3, 0);

    // 2 -> 1
    insertToGraph(2, 1, 1);
    // 2 -> 4
    insertToGraph(2, 4, 0);


    // 3 -> 0
    insertToGraph(3, 0, 0);
    // 3 -> 1
    insertToGraph(3, 1, 0);
    // 3 -> 4
    insertToGraph(3, 4, 0);
    // 3 -> 5
    insertToGraph(3, 5, 1);

    // 4 -> 2
    insertToGraph(4, 2, 0);
    // 4 -> 3
    insertToGraph(4, 3, 0);

    // 5 -> 0
    insertToGraph(5, 0, 1);
    // 5 -> 3
    insertToGraph(5, 3, 1);

}


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}


void exec(){
// execute the algorithm

    clearGraph();

    int src= getRandomNumberInRange(0,5), n=6;

    simulate();

    bfs(src, n);

    for(int i=0;i<n;i++){
        cout<<src<<" -> "<<i<<" shortest distance = "<<dist[i]<<"\n";
    }

}


int main()
{
    exec();

    return 0;
}
