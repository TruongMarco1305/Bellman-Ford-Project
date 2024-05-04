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

using namespace std;

void BF(int ** graph, int numberOfVertices, char startVertex, int * BellmanFordValue, int * BellmanFordPrevious);
string BF_Path(int ** graph,int numberOfVertices,char startVertex, char goalVertex);
