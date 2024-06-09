/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Traveling Saleman Problem related functions
* DISCRETE STRUCTURE May 2024
* Author: Truong Gia Ky Nam
* ID: 2352787
* Email: nam.truonggiaky@hcmut.edu.vn
*/

#ifndef _TSP_H_
#define _TSP_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>

using namespace std;

void findTwoMin(int G[20][20], int numCities, int firstMin[20], int secondMin[20]);
void branchAndBoundTSP(int G[20][20], int numCities, int (&currentPath)[21], int &currentBound, int currentCost, int level, bool (&visited)[20], int &finalCost, int (&finalPath)[21], int firstMin[20], int secondMin[20]);
string Traveling(int G[20][20], int numCities, char startVertex);

#endif //_TSP_H_