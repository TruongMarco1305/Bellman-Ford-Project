/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Code for "Travelling salesman related functions"
* Discrete Structure (CO1007)
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#include"tsm.h"

void setUp(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices){
    for (int i = 0; i < numberOfVertices; i++){
        if (i == int(startVertex - 'A')){
            continue;
        }

    }
}

void solve(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices){

}

int findMinCost(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices){

}

void findOptimalTour(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices){

}

void Traveling(int graph[][numberOfVertices],char startVertex){
    string ans;
    vector<vector<int>> memo(numberOfVertices,vector<int>(SIZE,0));

    setUp(graph,memo,startVertex,numberOfVertices);
    solve(graph,memo,startVertex,numberOfVertices);
    findMinCost(graph,memo,startVertex,numberOfVertices);
    findOptimalTour(graph,memo,startVertex,numberOfVertices);


}

