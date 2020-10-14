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


///------------------- dijstkra start -------------------///


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
    operator < (const node& p) const { return cost > p.cost; }

};



// representation of the graph
// edgesOfEachNode[u][i] is the i-th edge of the node 'u'
// distanceOfEachEdge[u][i] is the distance between node 'u' and it's i-th edge
vector<int> edgesOfEachNode[10000];
vector<int> distanceOfEachEdge[10000];
// distance of each node in the graph while traversing from 'source'
int dist[10000];


void dijstkra(int source, int numberOfNodes)
{
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

            if( dist[currNode] + distanceOfAdjNodeFromCurrNode < dist[adjNode] ){

                dist[adjNode] = dist[currNode] + distanceOfAdjNodeFromCurrNode;

                q.push( node(adjNode, dist[adjNode]) );

            }

        }

    }

}


///------------------- dijstkra end -------------------///


void simulateGraph(){

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
    edgesOfEachNode[0].push_back(1);
    distanceOfEachEdge[0].push_back(10);
    // 0 -> 3
    edgesOfEachNode[0].push_back(3);
    distanceOfEachEdge[0].push_back(6);
    // 0 -> 5
    edgesOfEachNode[0].push_back(5);
    distanceOfEachEdge[0].push_back(3);

    // 1 -> 0
    edgesOfEachNode[1].push_back(0);
    distanceOfEachEdge[1].push_back(10);
    // 1 -> 2
    edgesOfEachNode[1].push_back(2);
    distanceOfEachEdge[1].push_back(1);
    // 1 -> 3
    edgesOfEachNode[1].push_back(3);
    distanceOfEachEdge[1].push_back(2);

    // 2 -> 1
    edgesOfEachNode[2].push_back(1);
    distanceOfEachEdge[2].push_back(1);
    // 2 -> 4
    edgesOfEachNode[2].push_back(4);
    distanceOfEachEdge[2].push_back(12);


    // 3 -> 0
    edgesOfEachNode[3].push_back(0);
    distanceOfEachEdge[3].push_back(6);
    // 3 -> 1
    edgesOfEachNode[3].push_back(1);
    distanceOfEachEdge[3].push_back(2);
    // 3 -> 4
    edgesOfEachNode[3].push_back(4);
    distanceOfEachEdge[3].push_back(16);
    // 3 -> 5
    edgesOfEachNode[3].push_back(5);
    distanceOfEachEdge[3].push_back(1);

    // 4 -> 2
    edgesOfEachNode[4].push_back(2);
    distanceOfEachEdge[4].push_back(12);
    // 4 -> 3
    edgesOfEachNode[4].push_back(3);
    distanceOfEachEdge[4].push_back(16);

    // 5 -> 0
    edgesOfEachNode[5].push_back(0);
    distanceOfEachEdge[5].push_back(3);
    // 5 -> 3
    edgesOfEachNode[5].push_back(3);
    distanceOfEachEdge[5].push_back(1);

}


void exec(){

    int src=0, n=6;

    simulateGraph();

    dijstkra(src, n);

    for(int i=0;i<n;i++){
        cout<<src<<" -> "<<i<<" shortest distance = "<<dist[i]<<"\n";
    }

}


int main()
{
    exec();

    return 0;
}
