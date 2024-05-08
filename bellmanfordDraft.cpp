#include<iostream>
#include<stack>

using namespace std;

void BF(int ** graph, int numberOfVertices, char startVertex, int * BellmanFordValue, int * BellmanFordPrevious){
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
                        BellmanFordPrevious[v] = u;
                    }
                }
            }
        }
    }
}

bool detectNegativeCycle(int ** graph, int numberOfVertices, char startVertex, int * BellmanFordValue, int * BellmanFordPrevious){
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

void BF_Path(int ** graph,int numberOfVertices,char startVertex, char goalVertex){
    bool negativeCycle;
    int *BellmanFordValue = new int[numberOfVertices];
    int *BellmanFordPrevious = new int[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
    }
    BF(graph,numberOfVertices,startVertex,BellmanFordValue,BellmanFordPrevious);
    negativeCycle = detectNegativeCycle(graph,numberOfVertices,startVertex,BellmanFordValue,BellmanFordPrevious);
    if (negativeCycle){
        cout << "Contains circuit of negative weight";
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
        cout << path.top();
        path.pop();
        while (!path.empty()){
            cout << "->" << path.top();
            path.pop();
        }
    }
    delete BellmanFordValue;
    delete BellmanFordPrevious;    
}

int main(){
    int numberOfVertices = 3;     
    int **graph = new int *[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        graph[i] = new int[numberOfVertices];
    }
    //int input[6] = {15,3,15,3,3,3};
    //int index = 0;
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            if (i == j){
                graph[i][j] = 0;
            }else{
                cout << "Input the weight for edge from vertex " << char(i + 1 + 64) << " to vertex " << char(j + 1 + 64) << ": ";
                cin >> graph[i][j];
            }
        } 
    }

    char startVertex;
    cout << "Input the start vertex: ";
    cin >> startVertex;
    
    char goalVertex;
    cout << "Input the goal vertex: ";
    cin >> goalVertex;

    BF_Path(graph,numberOfVertices,startVertex,goalVertex);
    
    for (int i = 0; i < numberOfVertices; i++){
        delete graph[i];
    }
    delete graph;
    return 0;
}