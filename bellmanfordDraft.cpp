#include<iostream>
#include<stack>

using namespace std;

void initCityMap(int & numCities, int ** map){
    for (int i = 0; i < numCities; i++){
        map[i] = new int[numCities];
    }

    for (int i = 0; i < numCities; i++){
        for (int j = 0; j < numCities; j++){
            if (i == j){
                map[i][j] = 0;
            }else{
                cout << "Input distance from city " << char(i + 1 + 64) << " to city " << char(j + 1 + 64) << ": ";
                cin >> map[i][j];
            }
        } 
    }
}

void relaxation(int*distance,int*prev,int**map,int numCities){
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
}

int main(){
    int numCities = 3;
    int **map = new int *[numCities];
    initCityMap(numCities,map);

    int *distance = new int[numCities];
    int *prev = new int[numCities];
    int source;
    char input;
    cout << "Input the source city: ";
    cin >> input;
    source = int(input) - 64;
    for (int i = 0; i < numCities; i++){
        distance[i] = 1000;
        prev[i] = -1;
    }
    distance[source - 1] = 0;
    int relaxTime = 0;
    while (relaxTime < numCities - 1){
        relaxation(distance,prev,map,numCities);
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
        int finish = source;
        int tmp;
        while (finish <= numCities){
            path.push(finish);
            int length = distance[finish - 1];
            tmp = finish;
            while (tmp != source){
                path.push(prev[tmp-1]);
                tmp = prev[tmp-1];
            }
            cout << "The shortest distance from source city to city " << char(finish + 64) << ": " << length << endl;
            cout << "The path from source city to city " << char(finish + 64) << " with shortest distance: ";
            cout << path.top();
            while (!path.empty()){
                path.pop();
                if (path.empty()) break;
                cout << "->" << path.top();
            }
            cout << "\n";
            finish ++;
        }
    }
    delete distance;
    delete prev;
    return 0;
}