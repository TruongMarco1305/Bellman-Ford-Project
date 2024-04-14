#include<iostream>
#include<string>

using namespace std;

int main(){
    int vertices, edges, starting, end;
    cin >> vertices >> edges >> starting >> end;
    int ** weightGraph = new int*[edges];
    for (int i = 0; i < vertices; i ++){
        for (int j = 0; j < vertices; j++){
            weightGraph[i][j] = 0;
        }
    }
    for (int i = 0; i < vertices; i ++){
        for (int j = 0; j < vertices; j++){
            cout << weightGraph[i][j];
        }
    }
    /*int a,b,c;
    for (int i = 0; i < edges; i++){
        cin >> a >> b >> c;
        weightGraph[a - 1][b - 1] = c; 
    }*/

    for (int i = 0; i < edges; i++){
        delete weightGraph[i];
    }
    delete weightGraph;
    return 0;
}