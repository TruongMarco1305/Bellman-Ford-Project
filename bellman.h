/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Bellman-Ford related functions
* DISCRETE STRUCTURE May 2024
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#ifndef _BELLMAN_H_
#define _BELLMAN_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#define INFINITY INT_MAX;

using namespace std;

const int numberOfVertices = 7;
const long long SIZE = 2 << (numberOfVertices - 1); 

void BF(int graph[][numberOfVertices], const int numberOfVertices, char startVertex, int BellmanFordValue[], int BellmanFordPrevious[]);
bool detectNegativeCycle(int graph[][numberOfVertices], const int numberOfVertices, char startVertex, int BellmanFordValue[], int BellmanFordPrevious[]);
void BF_Path(int graph[][numberOfVertices], const int numberOfVertices,char startVertex, char goalVertex);

#endif