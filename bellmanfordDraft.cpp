#include<iostream>
#include<stack>

using namespace std;

void initCityMap(int & numCities, int **map){
    cout << "Input the number of city: ";
    cin >> numCities;
    for (int i = 0; i < numCities; i++){
        map[i] = new int[numCities];
    }
    int initial = 0;
    for (int i = 0; i < numCities; i++){
        for (int j = 0; j < numCities; j++){
            map[i][j] = initial;
        }
    }

    for (int i = 0; i < numCities; i++){
        for (int j = 0; j < numCities; j++){
            if (i == j){
                continue;
            }else{
                cout << "Input distance from city " << i + 1 << " to city " << j + 1 << ": ";
                cin >> initial;
                map[i][j] = initial;
                map[j][i] = initial;
            }
        } 
    }
}

int main(){
    int numCities;
    int **map = new int *[numCities];
    initCityMap(numCities,map);

    int *distance = new int[numCities];
    int *prev = new int[numCities];
    int source;
    cout << "Input the source city: ";
    cin >> source;
    int finish;
    cout << "Input the finish city: ";
    cin >> finish;
    for (int i = 0; i < numCities; i++){
        distance[i] = 1000;
        prev[i] = -1;
    }
    distance[source - 1] = 0;
    int relaxTime = 0;
    while (relaxTime < numCities - 1){
        for (int u = 0; u < numCities; u++){
            for (int v = 0; v < numCities; v ++){
                if (map[u][v] == 0){
                    continue;
                } else {
                    if (distance[u] + map[u][v] < distance[v]){
                        distance[v] = distance[u] + map[u][v];
                        prev[v] = u + 1;
                    }
                }
            }
        }
        relaxTime ++;
    }
    bool negativeCycle = false;
    for (int u = 0; u < numCities; u++){
        for(int v = 0; v < numCities; v++){
            if (map[u][v] == 0){
                continue;
            } else {
                if (distance[u] + map[u][v] < distance[v]){
                    negativeCycle = true;
                }
            }
        }
    }
    if (negativeCycle){
        cout << "Error: Contains circuit of negative weight";
    } else{
        stack<int> path;
        path.push(finish);
        int length = distance[finish - 1];
        while (finish != source){
            path.push(prev[finish-1]);
            finish = prev[finish-1];
        }
        cout << "The shortest distance from source city to finish city: " << length << endl;
        cout << "The path from source city to finish city with shortest distance: " << endl;
        cout << path.top();
        while (!path.empty()){
            path.pop();
            if (path.empty()) break;
            cout << "->" << path.top();
        }
    }
    delete distance;
    delete prev;
    return 0;
}