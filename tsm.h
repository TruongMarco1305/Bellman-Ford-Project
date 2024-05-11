/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Code for "Travelling salesman related functions"
* Discrete Structure (CO1007)
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#include"bellman.h"

void setUp(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices);
void solve(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices);
int findMinCost(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices);
void findOptimalTour(int graph[][numberOfVertices], vector<vector<int>> memo, char startVertex, int numberOfVertices);
void Traveling(int graph[][numberOfVertices] , char startVertex);
