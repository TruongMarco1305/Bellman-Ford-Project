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

void findTwoMin(int G[20][20], int numCities, int i, int &first, int &second);
void branchAndBoundTSP(int G[20][20], int numCities, int (&curr_path)[20], int &curr_bound, int curr_weight, int level, bool (&visited)[20], int &min_cost, int (&final_path)[20]);
string Traveling(int G[20][20], int numCities, char startVertex);