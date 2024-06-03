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
    int graph[20][20];
    int numberOfVertices;
    cin >> numberOfVertices;
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

void tsp(){
    // Adjacency matrix for the given G
    /*int G[20][20] = {{0, 141, 134, 152, 173, 289, 326, 329, 285, 401, 388, 366, 343, 305, 276},
                     {141, 0, 152, 150, 153, 312, 354, 313, 249, 324, 300, 272, 247, 201, 176},
                     {134, 152, 0, 24, 48, 168, 210, 197, 153, 280, 272, 257, 237, 210, 181},
                     {152, 150, 24, 0, 24, 163, 206, 182, 133, 257, 248, 233, 214, 187, 158},
                     {173, 153, 48, 24, 0, 160, 203, 167, 114, 234, 225, 210, 190, 165, 137},
                     {289, 312, 168, 163, 160, 0, 43, 90, 124, 250, 264, 270, 264, 267, 249},
                     {326, 354, 210, 206, 203, 43, 0, 108, 157, 271, 290, 299, 295, 303, 287},
                     {329, 313, 197, 182, 167, 90, 108, 0, 70, 164, 183, 195, 194, 210, 201},
                     {285, 249, 153, 133, 114, 124, 157, 70, 0, 141, 147, 148, 140, 147, 134},
                     {401, 324, 280, 257, 234, 250, 271, 164, 141, 0, 36, 67, 88, 134, 150},
                     {388, 300, 272, 248, 225, 264, 290, 183, 147, 36, 0, 33, 57, 104, 124},
                     {366, 272, 257, 233, 210, 270, 299, 195, 148, 67, 33, 0, 26, 73, 96},
                     {343, 247, 237, 214, 190, 264, 295, 194, 140, 88, 57, 26, 0, 48, 71},
                     {305, 201, 210, 187, 165, 267, 303, 210, 147, 134, 104, 73, 48, 0, 30},
                     {276, 176, 181, 158, 137, 249, 287, 201, 134, 150, 124, 96, 71, 30, 0}};*/

    int G[20][20] = {{0, 0, 0, 0, 50, 77, 49, 83, 24, 0, 0, 0},     // A
                     {66, 0, 0, 55, 58, 23, 79, 64, 0, 91, 0, 0},   // B
                     {26, 0, 0, 95, 0, 0, 67, 81, 0, 0, 9, 94},     // C
                     {0, 0, 0, 0, 22, 33, 77, 6, 76, 0, 5, 0},      // D
                     {46, 56, 0, 0, 0, 71, 55, 75, 24, 98, 77, 45}, // E
                     {77, 0, 48, 0, 0, 0, 0, 0, 33, 0, 0, 0},       // F
                     {4, 97, 74, 8, 21, 0, 0, 19, 70, 0, 0, 49},    // G
                     {89, 0, 19, 0, 51, 29, 0, 0, 20, 89, 41, 0},   // H
                     {81, 38, 0, 0, 9, 65, 0, 50, 0, 28, 0, 0},     // I
                     {27, 94, 9, 76, 0, 12, 0, 0, 0, 0, 47, 0},     // J
                     {42, 0, 78, 28, 0, 59, 0, 3, 0, 100, 0, 0},    // K
                     {17, 0, 74, 38, 60, 0, 17, 19, 0, 66, 0, 0}};  // L
    int n = 12;
    string output = Traveling(G, n, 'A');
    int length = 0;
    for (int i = 0; i < output.length() - 2; i += 2)
    {
        int a = int(output[i]) - 65;
        int b = int(output[i + 2]) - 65;
        length += G[a][b];
    }
    cout << output << endl;
    cout << length;
}

//g++ -o main main.cpp bellman.cpp tsm.cpp -I . -std=c++11 && ./main

int main(int argc, const char * argv[]){
    //bellmanfordprogram();
    tsp();
    return 0;
}