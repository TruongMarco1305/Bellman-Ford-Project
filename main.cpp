/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Main code for Assignment 1 "BELLMAN-FORD ALGORITHM"
* Discrete Structure (CO1007)
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

//Running command: g++ -o main main.cpp bellman.cpp tsm.cpp -I . -std=c++11 && ./main

#include "bellman.h"
#include "tsm.h"

void bellmanford(){
    int G[20][20] = {
        {0, 72, 89, 77, 2, 58, 13, 69},
        {77, 0, 69, 31, 57, 93, 83, 48},
        {52, 21, 0, 62, 8, 77, 32, 14},
        {33, 1, 40, 0, 72, 99, 72, 59},
        {89, 24, 1, 61, 0, 12, 78, 63},
        {36, 91, 98, 79, 26, 0, 28, 1},
        {18, 77, 49, 36, 98, 77, 0, 45},
        {75, 9, 59, 7, 77, 65, 45, 0},
    };

    int numberOfVertices = 8;

    cout << "QUESTION 01: BELLMAN-FORD STEP" << endl;
    int BellmanFordValue[20];
    int BellmanFordPrevious[20];
    for(int i = 0; i < numberOfVertices; i++){
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
    }

    for(int i = 0; i < numberOfVertices; i++){
        BF(G,numberOfVertices,'D',BellmanFordValue,BellmanFordPrevious);
        cout << "step " << i+1 << ":" << endl;
        for(int j = 0; j < numberOfVertices; j++){
            cout << BellmanFordValue[j] << " ";
        }
        cout << endl;
        for(int j = 0; j < numberOfVertices; j++){
            cout << BellmanFordPrevious[j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "QUESTION 02: BELLMAN-FORD PATH" << endl;
    cout << BF_Path(G,numberOfVertices,'A','D') << endl;
    cout << endl;
}

void tsp(){
    cout << "QUESTION 03: TRAVELING SALEMAN PROBLEM" << endl;
    // Adjacency matrix for the given G
    int G[20][20] = {{0, 141, 134, 152, 173, 289, 326, 329, 285, 401, 388, 366, 343, 305, 276},
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
                     {276, 176, 181, 158, 137, 249, 287, 201, 134, 150, 124, 96, 71, 30, 0}};
    //Number of Cities
    int n = 15;
    char startVertex = 'A';
    string output = Traveling(G, n, startVertex);
    int length = 0;
    if(output.length() != 1){
        for (int i = 0; i < output.length() - 2; i += 2)
        {
            int a = int(output[i]) - 65;
            int b = int(output[i + 2]) - 65;
            length += G[a][b];
        }
    }
    cout << "The optimal path from city A is: " << output << endl;
    cout << "Optimal cost: " << length;
}

int main(int argc, const char * argv[]){
    bellmanford();
    tsp();
    return 0;
}