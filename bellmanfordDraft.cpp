#include<iostream>
#include<stack>
#include<vector>
#define INFINITY INT_MAX;

using namespace std;

const int numberOfVertices = 4;

void BF(int graph[][numberOfVertices], int numberOfVertices, char startVertex, int BellmanFordValue[], int BellmanFordPrevious[]){
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

bool detectNegativeCycle(int graph[][numberOfVertices], int numberOfVertices, char startVertex, int * BellmanFordValue, int * BellmanFordPrevious){
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

void BF_Path(int graph[][numberOfVertices],int numberOfVertices,char startVertex, char goalVertex){
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

//SourceCode: https://github.com/williamfiset/Algorithms/blob/master/src/main/java/com/williamfiset/algorithms/graphtheory/TspDynamicProgrammingIterative.java
//Youtube: https://www.youtube.com/watch?v=09_LlHjoEiY&t=12673s

bool notIn(int elm, int subset){
    return ((1 << elm) & subset) == 0;
}


void initCombinations(int set, int at, int r, int n, vector<int> subsets){
    int elementsLeftToPick = n - at;
    if (elementsLeftToPick < r) return;

    if (r == 0){
        subsets.push_back(set);
    } else {
        for (int i = at; i < n; i++){
            set = set | (1 << i);

            initCombinations(set, i + 1, r - 1, n, subsets);

            set = set & ~ (1 << i);
        }
    }
}

vector<int> combinations(int r, int n){
    vector<int> subsets;
    initCombinations(0,0,r,n,subsets);
    return subsets;
}

void setUp(int graph[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices){
    for (int i = 0; i < numberOfVertices; i++){
        if (i == source){
            continue;
        } else {
            memo[i][1 << source | 1 << i] = graph[source][i];
        }
    }
}

void solve(int graph[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices){
    vector<int> set;
    for (int r = 3; r <= numberOfVertices; r++){
        for(int subset : combinations(r,numberOfVertices)){
            if (notIn(source,subset)) continue;
            for (int next = 0; next < numberOfVertices; next ++){
                if (next == source || notIn(next,subset)) continue;
                int subsetWithoutNext = subset ^ (1 << next);
                int minDist = INFINITY;
                for (int end = 0; end < numberOfVertices; end++){
                    if (end == source || end == next || notIn(end,subset)) continue;
                    int newDistance = memo[end][subsetWithoutNext] + graph[end][next];
                    if (newDistance < minDist){
                        minDist = newDistance;
                    }
                }
                memo[next][subset] = minDist;
            }
        }
    }
}

//int findMinCost(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices){}

string findOptimalTour(int graph[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices){
    int lastIndex = source;
    int state = (1 << numberOfVertices) - 1;
    string tour;
    tour += char(source + 'A');
    tour += " ";
    for (int i = 1; i < numberOfVertices; i++){
        int bestIndex = -1;
        int bestDist = INFINITY;
        for (int j = 0; j < numberOfVertices; j++){
            if (j == source || notIn(j,state)) continue;
            int newDist = memo[j][state] + graph[j][lastIndex];
            if (newDist < bestDist){
                bestIndex = j;
                bestDist = newDist;
            }
        }
        tour += char(bestIndex + 'A');
        tour += " ";
        state = state ^ (1 << bestIndex);
        lastIndex = bestIndex;
    }

    tour += char(source + 'A');

    return tour;
}

void Traveling(int graph[][numberOfVertices],char startVertex){
    vector<vector<int>> memo(numberOfVertices,vector<int>(1 << numberOfVertices,0));
    int source = int(startVertex - 'A');

    setUp(graph,memo,source,numberOfVertices);
    solve(graph,memo,source,numberOfVertices);
    //int cost = findMinCost(graph,memo,startVertex,numberOfVertices);
    
    cout << findOptimalTour(graph,memo,source,numberOfVertices);
}

void bfprogram(){
    int graph[numberOfVertices][numberOfVertices];
    int input[49] = {0,6,5,5,0,0,0,
                    0,0,0,0,-1,0,0,
                    0,-2,0,0,1,0,0,
                    0,0,-2,0,0,-1,0,
                    0,0,0,0,0,0,3,
                    0,0,0,0,0,0,3,
                    0,0,0,0,0,0,0};
    int index = 0;
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            if (i == j){
                graph[i][j] = 0;
            }else{
                //cout << "Input the weight for edge from vertex " << char(i + 1 + 64) << " to vertex " << char(j + 1 + 64) << ": ";
                graph[i][j] = input[index];
            }
            index ++;
        } 
    }

    char startVertex;
    cout << "Input the start vertex: ";
    cin >> startVertex;
    
    char goalVertex;
    cout << "Input the goal vertex: ";
    cin >> goalVertex;

    BF_Path(graph,numberOfVertices,startVertex,goalVertex);
}

void tspprogram(){
    int cityMap[numberOfVertices][numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            cityMap[i][j] = -1;
        }
    }

    int input[6] = {10,15,20,35,25,30};
    int index = 0;
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            if (i == j){
                cityMap[i][j] = 0;
            } else if (cityMap[i][j] != -1){
                continue;
            } else {
                cityMap[i][j] = input[index];
                cityMap[j][i] = input[index];
                index ++;
            }
        }
    }

    char startVertex = 'A';

    Traveling(cityMap,startVertex);
}

int main(){    
    //bfprogram();
    tspprogram();
    return 0;
}