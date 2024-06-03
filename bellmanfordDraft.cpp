#include<iostream>
#include<stack>
#include<vector>

using namespace std;

const int INFINITY = 100000000;

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
    return ans;
}

int main(){    
    int G[20][20] = {{0,72,89,77,2,58,13,69},//A
                     {77,0,69,31,57,93,83,48},//B
                     {52,21,0,62,8,77,32,14},//C
                     {33,1,40,0,72,99,72,59},//D
                     {89,24,1,61,0,12,78,63},//E
                     {36,91,98,79,26,0,28,1},//F
                     {18,77,49,36,98,77,0,45},//G
                     {75,9,59,7,77,65,45,0}};//H
    int BFValue[20];
    int BFPrev[20];
    int n=8;
    for(int i=0;i<n;i++){
        BFValue[i]=-1;
        BFPrev[i]=-1;
    }
    for(int i=0;i<n;i++){
        BF(G,n,'D',BFValue,BFPrev);
        cout<<"step"<<i+1<<":"<<endl;
        for(int j=0;j<n;j++){
            cout<<BFValue[j]<<" ";
        }
        cout<<endl;
        for(int j=0;j<n;j++){
            cout<<BFPrev[j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}