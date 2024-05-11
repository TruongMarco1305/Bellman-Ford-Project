/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Bellman-Ford related functions
* DISCRETE STRUCTURE May 2024
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#include"bellman.h"

bool notIn(int elm, int subset);
void initCombinations(int set, int at, int r, int n, vector<int> subsets);
vector<int> combinations(int r, int n);

void setUp(int cityMap[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices);
void solve(int cityMap[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices);
string findOptimalTour(int cityMap[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices);

void Traveling(int cityMap[][numberOfVertices] , char startVertex);