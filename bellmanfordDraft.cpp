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

// 0 83 16 21 27 68 97 19 15 89 53 82
// 99 0 81 43 81 90 88 94 79 99 18 34
// 8 8 0 27 54 70 35 29 10 21 78 27
// 8 4 95 0 72 23 76 60 42 57 24 89
// 67 4 79 20 0 64 57 18 82 92 26 90
// 85 46 26 19 41 0 36 6 18 63 82 89
// 23 53 78 99 79 19 0 22 2 8 89 6
// 87 8 36 9 94 17 67 0 86 74 51 32
// 100 37 39 35 43 24 99 91 0 12 21 43
// 91 87 21 76 8 23 84 63 96 0 36 37
// 31 12 30 15 79 83 89 30 14 88 0 67
// 19 22 76 43 87 67 56 75 76 12 61 0

// int G[20][20];
// int G2[20][20];
// int BFValue[20];
// int BFPrev[20];
// fin.open("inputMat16_1.txt");
// int n=16;
// for(int i=0;i<n;i++){
// BFValue[i]=-1;
// BFPrev[i]=-1;
// for(int j=0;j<n;j++){
// fin>>G[i][j];
// }
// }
// fin.close();
// fin.open("inputMat16_2.txt");
// for(int i=0;i<n;i++){
// for(int j=0;j<n;j++){
// fin>>G2[i][j];
// }
// }
// for(int i=0;i<n;i++){
// if(i%2)
// BF(G,n,15+'A',BFValue,BFPrev);
// else
// BF(G2,n,15+'A',BFValue,BFPrev);
// cout<<"step"<<i+1<<":"<<endl;
// for(int j=0;j<n;j++){
// cout<<BFValue[j]<<" ";
// }
// cout<<endl;
// for(int j=0;j<n;j++){
// cout<<BFPrev[j]<<" ";
// }
// cout<<endl;
// }
// fin.close();