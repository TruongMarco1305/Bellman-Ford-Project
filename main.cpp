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

void program(){
    int numberOfVertices;
    cout << "Input the number of vertices: ";
    cin >> numberOfVertices;     
    int **graph = new int *[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        graph[i] = new int[numberOfVertices];
    }
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            if (i == j){
                graph[i][j] = 0;
            }else{
                cout << "Input the weight for edge between vertex " << i + 1 << " to vertex " << j + 1 << ": ";
                cin >> graph[i][j];
            }
        } 
    }

    int *BellmanFordValue = new int[numberOfVertices];
    int *BellmanFordPrevious = new int[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++){
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
    }
    char startVertex;
    cout << "Input the start vertex: ";
    cin >> startVertex;

    BF(graph,numberOfVertices,startVertex,BellmanFordValue,BellmanFordPrevious);
    
    char goalVertex;
    cout << "Input the goal vertex: ";
    cin >> goalVertex;

    BF_Path(graph,numberOfVertices,startVertex,goalVertex);
    
    for (int i = 0; i < numberOfVertices; i++){
        delete graph[i];
    }
    delete graph;

    delete BellmanFordValue;
    delete BellmanFordPrevious;

}

int main(int argc, const char * argv[]){
    program();
    return 0;
}