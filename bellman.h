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
#include <vector>

using namespace std;

void BF(int graph[20][20], int numberOfVertices, char startVertex, int BellmanFordValue[20], int BellmanFordPrevious[20]);
bool detectNegativeCycle(int graph[20][20], int numberOfVertices, char startVertex, int BellmanFordValue[20], int BellmanFordPrevious[20]);
string BF_Path(int graph[20][20], int numberOfVertices,char startVertex, char goalVertex);

#endif