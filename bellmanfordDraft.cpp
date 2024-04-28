#include<iostream>

using namespace std;

void tsm(int & numCities, int **map){
    for (int i = 0; i < numCities; i++){
        map[i] = new int[numCities];
    }

    int distance = 0;
    for (int i = 0; i < numCities; i++){
        for (int j = 0; j < numCities; j++){
            map[i][j] = distance;
        }
    }

    for (int i = 0; i < numCities; i++){
        for (int j = 0; j < numCities; j++){
            if (i == j){
                continue;
            }else {
                cout << "Input distance from city " << i + 1 << " to city " << j + 1 << ": ";
                cin >> distance;
                map[i][j] = distance;
            }
        } 
    }

    for (int i = 0; i < numCities; i++){
        for (int j = 0; j < numCities; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < numCities; i++){
        delete map[i];
    }
    delete map;

}
int main(){
    int numCities = 7;
    int map[7][7]{{0,6,5,5,0,0,0},
    {0,0,0,0,-1,0,0},
    {0,-2,0,0,1,0,0},
    {0,0,-2,0,0,-1,0},
    {0,0,0,0,0,0,3},
    {0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0}};
    int distance[7];
    int *movingRoad = new int[numCities];
    distance[0] = 0;
    for (int i = 1; i < numCities; i++){
        distance[i] = INT_MAX;
    }
    int relaxTime = 0;
    while (relaxTime < numCities - 1){
        for (int u = 0; u < numCities; u++){
            for (int v = 0; v < numCities; v ++){
                if (map[u][v] == 0){
                    continue;
                } else {
                    if (distance[u] + map[u][v] < distance[v]){
                        distance[v] = distance[u] + map[u][v];
                    }
                }
            }
        }
        relaxTime ++;
    }
    for (int i = 0; i < numCities; i++){
        cout << distance[i] << " ";
    } 
    return 0;
}