/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Code for Assignment 1 "BELLMAN-FORD ALGORITHM"
* Discrete Structure (CO1007)
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#include "bellman.h"
#include "tsm.h"

void bellmanfordprogram(){     
    int graph[numberOfVertices][numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            if (i == j){
                graph[i][j] = 0;
            }else{
                cout << "Input the weight for edge from vertex " << char(i + 65) << " to vertex " << char(j + 65) << ": ";
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
}

void tspproblem(){
    int cityMap[numberOfVertices][numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            if (i == j){
                cityMap[i][j] = 0;
            }else{
                cout << "Input the distance from city " << char(i + 65) << " to city " << char(j + 65) << ": ";
                cin >> cityMap[i][j];
            }
        } 
    }

    char startCity;
    cout << "Input the start city: ";
    cin >> startCity;

    Traveling(cityMap,startCity);
}

int main(int argc, const char * argv[]){
    bellmanfordprogram();
    tspproblem();
    return 0;
}