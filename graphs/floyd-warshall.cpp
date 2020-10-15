/**

    Floyd-Warshall Algorithm
    shortest path traversal using adjacency matrix
    Time Complexity: O(n^3) when to use it?

**/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///------------------- floyd-warshall start -------------------///

// number of nodes the algorithm will support
const int MAX_NUMBER_OF_NODES = 1000;


// variables to represent the graph
// each element contains direct distance from one to other
// infinity if not connected
int adjacencyMatrix[MAX_NUMBER_OF_NODES][MAX_NUMBER_OF_NODES];
void clearGraph(){
// reset the graph representation variable, must be called for each new graph
    for(int i=0;i<MAX_NUMBER_OF_NODES;i++)
        for(int j=0;j<MAX_NUMBER_OF_NODES;j++)
            (i==j) ? adjacencyMatrix[i][j] = 0 : adjacencyMatrix[i][j] = INT_MAX;
}

// result variables: shortest path distance, shortest path itself
// targetMatrix[u][v] = shortest path distance from u to v
int targetMatrix[MAX_NUMBER_OF_NODES][MAX_NUMBER_OF_NODES];
// nextNode[u][v] = the node you have to go through to go from u to v in the shortest path distance
int nextNode[MAX_NUMBER_OF_NODES][MAX_NUMBER_OF_NODES];


void floydWarshall(int numberOfNodes)
{
// call this function from main code

    for(int i=0;i<numberOfNodes;i++)
        for(int j=0;j<numberOfNodes;j++){
            targetMatrix[i][j] = adjacencyMatrix[i][j];
            (adjacencyMatrix[i][j]==INT_MAX) ? nextNode[i][j] = -1 : nextNode[i][j] = j;
        }

    for(int k=0;k<numberOfNodes;k++)
        for(int i=0;i<numberOfNodes;i++)
            for(int j=0;j<numberOfNodes;j++){

                unsigned long long distanceFromItoJ, distanceFromItoK, distanceFromKtoJ;

                distanceFromItoJ = (unsigned long long)targetMatrix[i][j];
                distanceFromItoK = (unsigned long long)targetMatrix[i][k];
                distanceFromKtoJ = (unsigned long long)targetMatrix[k][j];

                if( distanceFromItoJ > distanceFromItoK + distanceFromKtoJ ){
                    targetMatrix[i][j] = targetMatrix[i][k] + targetMatrix[k][j];
                    nextNode[i][j] = nextNode[i][k];
                }

            }

}


string pathFromUtoV(int u, int v){
// return the shortest path from u to v
// call this function in main code only after floydWashell() was called

    string path;

    while(true){
        path += to_string(u);

        if(u==v)
            break;
        else if(u==-1){
            path = "no path found";
            break;
        }

        path+=" -> ";

        u = nextNode[u][v];
    }

    return path;

}

///------------------- floyd-warshall end -------------------///


void simulate(){
// simulate input to test the algorithm being implemented

/** simulation graph:

                  (10)    (1)
                0-------1-----2
                |\(6)  /      |
             (3)| \   /(2)    |(12)
                |  \ /        |
                5---3---------4
                 (1)    (16)
*/

    // node 0
    adjacencyMatrix[0][1] = 10;
    adjacencyMatrix[0][3] = 6;
    adjacencyMatrix[0][5] = 3;

    // node 1
    adjacencyMatrix[1][0] = 10;
    adjacencyMatrix[1][2] = 1;
    adjacencyMatrix[1][3] = 2;

    // node 2
    adjacencyMatrix[2][1] = 1;
    adjacencyMatrix[2][4] = 12;

    // node 3
    adjacencyMatrix[3][0] = 6;
    adjacencyMatrix[3][1] = 2;
    adjacencyMatrix[3][4] = 16;
    adjacencyMatrix[3][5] = 1;

    // node 4
    adjacencyMatrix[4][2] = 12;
    adjacencyMatrix[4][3] = 16;

    // node 5
    adjacencyMatrix[5][0] = 3;
    adjacencyMatrix[5][3] = 1;

}


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}


void exec(){
// execute the algorithm

    // must be called before each new graph setup
    clearGraph();

    simulate();

    floydWarshall(6);

    for(int i=0;i<6;i++)
    for(int j=0;j<6;j++){}

    int src = getRandomNumberInRange(0, 2), destination = getRandomNumberInRange(3, 5);

    cout<<"shortest distance from '"<<src<<"' to '"<<destination<<"' = "<<targetMatrix[src][destination]<<"\n";
    cout<<"the full path = "<<pathFromUtoV(src, destination)+"\n";

}


int main()
{
    exec();

    return 0;
}
