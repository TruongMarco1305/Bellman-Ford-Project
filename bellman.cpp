#include "bellman.h"

void BF(int graph[20][20], int numberOfVertices, char startVertex, int BellmanFordValue[20], int BellmanFordPrevious[20]){
    int source = int(startVertex - 'A');
    int unrelaxBellmanFordValue[20];
    bool init = false;

    for (int i = 0; i < numberOfVertices; i++){
        if (BellmanFordValue[i] != -1){
            init = true;
            break;
        }
    }

    if (init == false){
        for (int i = 0; i < numberOfVertices; i++){
            BellmanFordValue[i] = 100000000;
            unrelaxBellmanFordValue[i] = BellmanFordValue[i];
        }
        BellmanFordValue[source] = 0;
        unrelaxBellmanFordValue[source] = BellmanFordValue[source];
    } else {
        for (int i = 0; i < numberOfVertices; i++){
            if(BellmanFordValue[i] == -1){
                BellmanFordValue[i] = 100000000;
            }
            unrelaxBellmanFordValue[i] = BellmanFordValue[i];
        }

    }

    for(int u = 0; u < numberOfVertices; u++){
        for (int v = 0; v < numberOfVertices; v++){
            if (graph[u][v] == 0 || unrelaxBellmanFordValue[u] == 100000000){
                continue;
            } else if (unrelaxBellmanFordValue[u] + graph[u][v] < BellmanFordValue[v]){
                BellmanFordValue[v] = unrelaxBellmanFordValue[u] + graph[u][v];
                BellmanFordPrevious[v] = u;
            }
        }
    }

    for(int i = 0; i < numberOfVertices; i++){
        if(BellmanFordValue[i] == 100000000){
            BellmanFordValue[i] = -1;
        }
    }
}

bool detectNegativeCycle(int graph[20][20], int numberOfVertices, char startVertex, int BellmanFordValue[20], int BellmanFordPrevious[20]){
   for (int u = 0; u < numberOfVertices; u++){
        for(int v = 0; v < numberOfVertices; v++){
            if (graph[u][v] == 0){
                continue;
            } else if (BellmanFordValue[u] + graph[u][v] < BellmanFordValue[v]){
                return true;
            }
        }
    }
    return false;
}

string BF_Path(int graph[20][20],int numberOfVertices,char startVertex, char goalVertex){
    string ans;
    bool negativeCycle;
    int BellmanFordValue[20];
    int BellmanFordPrevious[20];
    for(int i = 0; i < numberOfVertices; i++){
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
    }

    for(int i = 0; i < numberOfVertices; i++){
        BF(graph,numberOfVertices,startVertex,BellmanFordValue,BellmanFordPrevious);
    }
    
    negativeCycle = detectNegativeCycle(graph,numberOfVertices,startVertex,BellmanFordValue,BellmanFordPrevious);

    if (negativeCycle){
        ans = "Errors: Contains circuit of negative weight";
    } else {
        int source = int(startVertex - 'A');
        int goal = int(goalVertex - 'A');
        ans += goalVertex;
        ans += " ";
        int tmp = goal;
        while(tmp != source){
            ans += char(BellmanFordPrevious[tmp] + 'A');
            ans += " ";
            tmp = BellmanFordPrevious[tmp];
        }
        ans.pop_back();
        for(int i = 0; i < ans.length()/2; i++){
            swap(ans[i],ans[ans.length() - i - 1]);
        }
    }
    return ans;
}

