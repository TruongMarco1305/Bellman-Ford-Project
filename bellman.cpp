/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Code for "Bellman-Ford related functions"
* Discrete Structure (CO1007)
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#include "bellman.h"

void BF(int ** graph, int numberOfVertices, char startVertex, int * BellmanFordValue, int * BellmanFordPrevious){
    int source = int(startVertex) - 64;
    for (int i = 0; i < numberOfVertices; i++){
        BellmanFordValue[i] = INT_MAX;
    }
    BellmanFordValue[int(startVertex - 'A')] = 0;
    for (int i = 0; i < numberOfVertices - 1; i ++){
        for (int u = 0; u < numberOfVertices; u++){
            for (int v = 0; v < numberOfVertices; v++){
                if (graph[u][v] == 0){
                    continue;
                } else {
                    if (BellmanFordValue[u] + graph[u][v] < BellmanFordValue[v]){
                        BellmanFordValue[v] = BellmanFordValue[u] + graph[u][v];
                        BellmanFordPrevious[v] = u + 1;
                    }
                }
            }
        }
    }
}

string BF_Path(int ** graph,int numberOfVertices,char startVertex, char goalVertex){
    string ans;
    ans += startVertex;
     
}

