/**

    Dijkstra's Algorithm to find shortest path from source to each node
    Time complexity: O(VlogV + E) where, V = # of nodes, E = # of edges

**/

#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


///------------------- Dijkstra start -------------------///


// number of nodes this supported by the implementation
const int MAX_NUMBER_OF_NODES = 10000;


// nodes in the graph o keep in the priority queue
struct node{

    int u; // node value
    int cost; // cost to reach this node

    node(){}

    node(int _u, int _cost){
        u = _u;
        cost = _cost;
    }

    // operator overloading
    // if this.cost > p.cost then 'this' node is smaller than p
    // so 'this' should come later in priority_queue
    bool operator < (const node& p) const { return cost > p.cost; }

};



// representation of the graph
// edgesOfEachNode[u][i] is the i-th edge of the node 'u'
// distanceOfEachEdge[u][i] is the distance between node 'u' and it's i-th edge
vector<int> edgesOfEachNode[MAX_NUMBER_OF_NODES];
vector<int> distanceOfEachEdge[MAX_NUMBER_OF_NODES];
// distance of each node in the graph while traversing from 'source'
int dist[MAX_NUMBER_OF_NODES];
// parents of each node for shortest path from 'source'
vector<int> parent[MAX_NUMBER_OF_NODES];

void insertToGraph(int u, int v, int c){
// insert new edge u->v at cost c to graph
    edgesOfEachNode[u].push_back(v);
    distanceOfEachEdge[u].push_back(c);
}

void showParents(int n){
// print parents stored as adjacency list
// must be called in the main code AFTER dijkstra() is called
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(int j=0;j<parent[i].size();j++) cout<<parent[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void clearGraph(){
// clears/resets graph representation variables
// must be called in main code before each new graph
    for(int i=0;i<MAX_NUMBER_OF_NODES;i++){
        edgesOfEachNode[i].clear();
        distanceOfEachEdge[i].clear();
        parent[i].clear();
    }
}


void dijstkra(int source, int numberOfNodes)
{
// call this function from the main code

    // initially nodes are unreachable(distance is infinity)
    for(int i=0;i<numberOfNodes;i++) dist[i] = INT_MAX;

    // priority_queue based on each node's cost (heart of dijstkra)
    priority_queue<node> q;

    q.push(node(source, 0));
    dist[source] = 0; // distance to reach source node=0

    while(!q.empty()){

        node curr = q.top();
        q.pop();

        int currNode = curr.u;
        int distanceOfCurrNode = curr.cost;

        for(int i=0;i<edgesOfEachNode[currNode].size();i++){

            int adjNode = edgesOfEachNode[currNode][i];
            int distanceOfAdjNodeFromCurrNode = distanceOfEachEdge[currNode][i];

            if( distanceOfCurrNode + distanceOfAdjNodeFromCurrNode < dist[adjNode] ){

                dist[adjNode] = distanceOfCurrNode + distanceOfAdjNodeFromCurrNode;

                q.push( node(adjNode, dist[adjNode]) );

                parent[adjNode].clear();
                parent[adjNode].push_back(currNode);

            }

            else if(distanceOfCurrNode + distanceOfAdjNodeFromCurrNode == dist[adjNode]){
                parent[adjNode].push_back(currNode);
            }

        }

    }

}


///------------------- Dijkstra end -------------------///


void simulate(){

    /** simulation graph:

                  (10)    (1)
                0-------1-----2
                |\(6)  /      |
             (3)| \   /(2)    |(12)
                |  \ /        |
                5---3---------4
                 (1)    (16)
    */

    // 0 -> 1
    insertToGraph(0, 1, 10);
    // 0 -> 3
    insertToGraph(0, 3, 6);
    // 0 -> 5
    insertToGraph(0, 5, 3);

    // 1 -> 0
    insertToGraph(1, 0, 10);
    // 1 -> 2
    insertToGraph(1, 2, 1);
    // 1 -> 3
    insertToGraph(1, 3, 2);

    // 2 -> 1
    insertToGraph(2, 1, 1);
    // 2 -> 4
    insertToGraph(2, 4, 12);


    // 3 -> 0
    insertToGraph(3, 0, 6);
    // 3 -> 1
    insertToGraph(3, 1, 2);
    // 3 -> 4
    insertToGraph(3, 4, 16);
    // 3 -> 5
    insertToGraph(3, 5, 1);

    // 4 -> 2
    insertToGraph(4, 2, 12);
    // 4 -> 3
    insertToGraph(4, 3, 16);

    // 5 -> 0
    insertToGraph(5, 0, 3);
    // 5 -> 3
    insertToGraph(5, 3, 1);

}


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}


void exec(){

    clearGraph();

    int src=getRandomNumberInRange(0,5), n=6;

    simulate();

    dijkstra(src, n);

    for(int i=0;i<n;i++){
        cout<<src<<" -> "<<i<<" shortest distance = "<<dist[i]<<"\n";
    }

    cout<<"parents = \n";
    showParents();

}


int main()
{
    exec();

    return 0;
}
