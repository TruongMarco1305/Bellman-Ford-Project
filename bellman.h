/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Code for "Bellman-Ford related functions"
* Discrete Structure (CO1007)
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const int numberOfVertices = 7;
const long long SIZE = pow(2,numberOfVertices); 

void BF(int graph[][numberOfVertices], const int numberOfVertices, char startVertex, int BellmanFordValue[], int BellmanFordPrevious[]);
bool detectNegativeCycle(int graph[][numberOfVertices], const int numberOfVertices, char startVertex, int BellmanFordValue[], int BellmanFordPrevious[]);
void BF_Path(int graph[][numberOfVertices], const int numberOfVertices,char startVertex, char goalVertex);