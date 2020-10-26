/**

    Bellman-Ford Algorithm to find shortest path from source to each node
    Works with negative edged, can detect negative cycle
    Time complexity: O(V*E) where, V = # of nodes, E = # of edges

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- bellman-ford start -------------------///

// number of nodes this supported by the implementation
const int MAX_NUMBER_OF_NODES = 1000;


// representation of the graph
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


// flag for existence of negative cycle
bool negativeCycleExists;


void bellmanFord(int source, int numberOfNodes)
{
// call this function from the main code

    // initially nodes are unreachable(distance is infinity)
    for(int i=0;i<numberOfNodes;i++) dist[i] = INT_MAX;

    // set negative cycle flag to false
    negativeCycleExists = false;


    dist[source] = 0;

    // in extreme case there might be maximum n-1 edges between source and another node
    // do edge relaxation n-1 times to get all the shortest distances (even the ones that are reachable through n-1 edges)
    for(int step=1;step<=numberOfNodes-1;step++){

        // relax all edges
        for(int i=0;i<MAX_NUMBER_OF_NODES;i++){
            for(int j=0;j<edgesOfEachNode[i].size();j++){

                int u = i, v = edgesOfEachNode[i][j], costFromUtoV = distanceOfEachEdge[i][j];
                int currCostOfU = dist[u], currCostOfV = dist[v];


                // 'u' is currently unreachable
                if(currCostOfU == INT_MAX) continue;


                if(currCostOfV > currCostOfU+costFromUtoV){

                    dist[v] = currCostOfU+costFromUtoV;

                }

            }
        }

    }


    // there is a negative cycle if at even the nth relaxation some distance updgrades
    for(int i=0;i<MAX_NUMBER_OF_NODES;i++){
        for(int j=0;j<edgesOfEachNode[i].size();j++){

            int u = i, v = edgesOfEachNode[i][j], costFromUtoV = distanceOfEachEdge[i][j];
            int currCostOfU = dist[u], currCostOfV = dist[v];


            // 'u' is currently unreachable
            if(currCostOfU == INT_MAX) continue;


            if(currCostOfV > currCostOfU+costFromUtoV){

                negativeCycleExists = true;

            }

        }
    }

}


///------------------- bellman-ford end -------------------///


void simulate(){
// simulate input to test the algorithm being implemented

    /** simulation graph(directed):

                  (10)    (1)
                0------>1---->2
                ^\(-6) ^      |
             (5)| \   /(2)    |(12)
                |  v /        v
                5<--3-------->4
                 (1)    (16)
    */

    // 0 -> 1
    insertToGraph(0, 1, 10);
    // 0 -> 3
    insertToGraph(0, 3, -6);


    // 1 -> 2
    insertToGraph(1, 2, 1);


    // 2 -> 4
    insertToGraph(2, 4, 12);


    // 3 -> 1
    insertToGraph(3, 1, 2);
    // 3 -> 4
    insertToGraph(3, 4, 16)
    // 3 -> 5
    insertToGraph(3, 5, 1);


    // 5 -> 0
    insertToGraph(5, 0, 5);


}


void exec(){
// execute the algorithm

    clearGraph();

    simulate();

    int src= 0, n=6;

    simulate();

    bellmanFord(src, n);

    for(int i=0;i<n;i++){
        cout<<src<<" -> "<<i<<" shortest distance = "<<dist[i]<<"\n";
    }

    if(negativeCycleExists)
        cout<<"\nnegative cycle exists in graph...\n";
    else
        cout<<"\nno negative cycles found\n";

}


int main()
{
    exec();

    return 0;
}
