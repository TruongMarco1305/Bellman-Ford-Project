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

void BF(int graph[][numberOfVertices], const int numberOfVertices, char startVertex, int BellmanFordValue[], int BellmanFordPrevious[]){
    for (int i = 0; i < numberOfVertices; i++){
        BellmanFordValue[i] = INFINITY;
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
                        BellmanFordPrevious[v] = u;
                    }
                }
            }
        }
    }
}

bool detectNegativeCycle(int graph[][numberOfVertices], const int numberOfVertices, char startVertex, int BellmanFordValue[], int BellmanFordPrevious[]){
   for (int u = 0; u < numberOfVertices; u++){
        for(int v = 0; v < numberOfVertices; v++){
            if (graph[u][v] == 0){
                continue;
            } else {
                if (BellmanFordValue[u] + graph[u][v] < BellmanFordValue[v]){
                    return true;
                }
            }
        }
    }
    return false;
}

void BF_Path(int graph[][numberOfVertices], const int numberOfVertices,char startVertex, char goalVertex){
    string ans;
    bool negativeCycle;
    int BellmanFordValue[numberOfVertices];
    int BellmanFordPrevious[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
    }
    BF(graph,numberOfVertices,startVertex,BellmanFordValue,BellmanFordPrevious);
    negativeCycle = detectNegativeCycle(graph,numberOfVertices,startVertex,BellmanFordValue,BellmanFordPrevious);
    if (negativeCycle){
        cout << "Errors: Contains circuit of negative weight";
    } else {
        stack <int> path;
        int source = int(startVertex - 'A');
        int goal = int(goalVertex - 'A');    
        path.push(goal);
        int tmp = goal;
        while (tmp != source){
            path.push(BellmanFordPrevious[tmp]);
            tmp = BellmanFordPrevious[tmp];
        }
        while (!path.empty()){
            ans += char(path.top() + 'A');
            ans += " ";
            path.pop();
        }
    }
    cout << ans;
}

