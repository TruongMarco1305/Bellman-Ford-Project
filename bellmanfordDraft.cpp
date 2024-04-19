#include<iostream>
#include<string>

using namespace std;

int main(){
    int vertices, edges, starting, end;
    cin >> vertices >> edges >> starting >> end;
    int weightGraph[100][100];
    for (int i = 0; i < vertices; i ++){
        for (int j = 0; j < vertices; j++){
            weightGraph[i][j] = -1;
        }
    }

    int a,b,c;
    for (int i = 0; i < edges; i++){
        cin >> a >> b >> c;
        weightGraph[a - 1][b - 1] = c; 
    }
    for (int i = 0; i < vertices; i ++){
        for (int j = 0; j < vertices; j++){
            cout << weightGraph[i][j] << " ";
        }
        cout << endl;
    }

    int arr[100] = {0};
    for (int i = 0; i < )
    int relaxedTime = 0;
    while (relaxedTime < vertices - 1){

    }

    int distance = INT_MAX;
    
    return 0;
}