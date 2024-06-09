#include <bits/stdc++.h>

using namespace std;

//Finding two minimum edges function having an end at vertex i and store it in minimum arrays
void findTwoMin(int G[20][20], int numCities, int firstMin[20], int secondMin[20]){
    for(int i = 0; i < numCities; i++){
        firstMin[i] = 100000;
        secondMin[i] = 100000;
        //Find the first minimum value
        for(int j = 0; j < numCities; j++){
            if(i == j) continue;
            if(firstMin[i] >= G[i][j]) firstMin[i] = G[i][j];
        }
        //Find the second minimum value
        for(int j = 0; j < numCities; j++){
            if(i == j) continue;
            if(secondMin[i] >= G[i][j] && G[i][j] > firstMin[i]) secondMin[i] = G[i][j];
        }
    }
}

void branchAndBoundTSP(int G[20][20], int numCities, int (&currentPath)[21], int &currentBound, int currentCost
, int level, bool (&visited)[20], int &finalCost, int (&finalPath)[21], int firstMin[20], int secondMin[20])
{
    //Base case: When the search tree has reached the level N
    //which mean the algorithm has covered all nodes
    if (level == numCities)
    {
        //Check if there is a path from last vertex in the current path to the start vertex
        if (G[currentPath[level - 1]][currentPath[0]] != 0)
        {
            //The total weight of the current path
            int currentResult = currentCost +
                           G[currentPath[level - 1]][currentPath[0]];

            //Update the final cost and final path
            //if the current path is more optimal
            if (currentResult < finalCost)
            {
                //Make the current path is the final path
                for (int i = 0; i < numCities; i++)
                {
                    finalPath[i] = currentPath[i];
                }
                finalPath[numCities] = currentPath[0];
                finalCost = currentResult;
            }
        }
    }
    else //While the algorithm doesn't reach level N
    {
        //Iterate for all vertices to build the tree recursively
        for (int i = 0; i < numCities; i++)
        {
            //Consider the next vertex 
            //if it is not visited 
            //and it connects to the last vertex within the current path
            if (G[currentPath[level - 1]][i] != 0 &&
                visited[i] == false)
            {
                //Using a temporary to store the current bound
                //For backtracking
                int temp = currentBound;

                //Add the weight of the consider edges to the current path's cost
                currentCost += G[currentPath[level - 1]][i];

                if(level == 1){
                    currentBound -= (firstMin[currentPath[level - 1]] + firstMin[i])/2;
                } else {
                    currentBound -= (secondMin[currentPath[level - 1]] + firstMin[i])/2;
                }

                //Check if the actual lower bound smaller than the minimum cost, explore the node further
                if (currentBound + currentCost < finalCost)
                {
                    currentPath[level] = i;
                    visited[i] = true;

                    branchAndBoundTSP(G, numCities, currentPath, currentBound, currentCost, level + 1, visited, finalCost, finalPath, firstMin, secondMin);
                }

                //Else prune the node by resetting all change to current cost and current bound
                //Or if the exploration success, backtracking to explore other solutions  
                currentCost -= G[currentPath[level - 1]][i];
                currentBound = temp;

                //Reset the visited array
                for (int i = 0; i < numCities + 1; i++)
                {
                    visited[i] = false;
                }

                for (int j = 0; j <= level - 1; j++)
                {
                    visited[currentPath[j]] = true;
                }
            }
        }
    }
}

string Traveling(int G[20][20], int numCities, char startVertex)
{
    if (numCities == 1){
        string ans;
        ans += startVertex;
        return ans;
    }
    //Initialization 
    int currentPath[21] = {-1};
    bool visited[20] = {false};
    int finalPath[21] = {-1};

    int firstMin[20] = {-1};
    int secondMin[20] = {-1};

    int finalCost = 100000;
    int currentBound = 0;
    string ans;

    //Calculate the bound for any tour
    for (int i = 0; i < numCities; i++)
    {
        currentBound += (firstMin[i] + secondMin[i]);
    }

    //Rounding off the bound
    if (currentBound % 2 == 0)
    {
        currentBound = currentBound / 2;
    }
    else
    {
        currentBound = currentBound / 2 + 1;
    }

    //Store the starting vertex to the beginning of the current path
    visited[int(startVertex - 'A')] = true;
    currentPath[0] = int(startVertex - 'A');

    //Call to branchAndBound with current path cost is 0 and explore the tree from level 1. 
    branchAndBoundTSP(G, numCities, currentPath, currentBound, 0, 1, visited, finalCost, finalPath, firstMin, secondMin);

    //After the optimal solution is found
    //Return it in the string form
    for (int i = 0; i <= numCities; i++)
    {
        ans += char(finalPath[i] + 'A');
        if (i == numCities) break;
        ans += " ";
    }

    return ans;
}

int pathlength(int G[20][20], int numCities, string output)
{
    if(output.length() == 1) return 0;
    int length = 0;
    for (int i = 0; i < output.length() - 2; i += 2)
    {
        int a = int(output[i]) - 65;
        int b = int(output[i + 2]) - 65;
        length += G[a][b];
    }
    return length;
}

// Driver code
int main()
{
    // Adjacency matrix for the given G
// int G[20][20] = {
//       {0, 8, 24, 63, 22, 51, 20, 20, 24, 19, 24, 78, 37, 57, 48, 57},
//       {62, 0, 74, 100, 77, 46, 97, 79, 27, 23, 57, 33, 79, 94, 97, 85},
//       {83, 4, 0, 75, 45, 93, 25, 31, 80, 15, 16, 70, 94, 20, 26, 7},
//       {77, 88, 81, 0, 43, 30, 94, 39, 75, 20, 28, 98, 19, 6, 92, 82},
//       {58, 74, 52, 32, 0, 85, 45, 24, 15, 24, 5, 99, 60, 99, 18, 86},
//       {73, 95, 39, 19, 37, 0, 69, 12, 42, 44, 100, 70, 41, 18, 77, 99},
//       {0, 0, 38, 52, 99, 22, 0, 63, 22, 4, 87, 28, 2, 12, 93, 20},
//       {98, 65, 81, 36, 51, 85, 72, 0, 63, 26, 82, 62, 97, 22, 47, 39},
//       {88, 47, 5, 25, 65, 3, 14, 28, 0, 93, 85, 81, 20, 53, 94, 79},
//       {39, 57, 10, 19, 94, 61, 70, 31, 90, 0, 97, 12, 52, 59, 0, 99},
//       {64, 54, 11, 69, 80, 76, 38, 60, 70, 30, 0, 10, 17, 16, 63, 10},
//       {96, 68, 67, 72, 87, 26, 32, 23, 23, 21, 19, 0, 35, 39, 44, 2},
//       {3, 7, 56, 14, 42, 1, 57, 80, 27, 93, 10, 37, 0, 9, 26, 66},
//       {86, 88, 33, 53, 59, 87, 45, 57, 9, 69, 45, 95, 70, 0, 84, 38},
//       {72, 88, 11, 95, 68, 53, 96, 91, 32, 23, 84, 8, 26, 93, 0, 1},
//       {93, 79, 89, 25, 98, 14, 11, 8, 71, 87, 43, 15, 81, 80, 66, 0}};
    //Bkel
    int G[20][20] = {{0, 0, 0, 0, 50, 77, 49, 83, 24, 0, 0, 0},     // A
                     {66, 0, 0, 55, 58, 23, 79, 64, 0, 91, 0, 0},   // B
                     {26, 0, 0, 95, 0, 0, 67, 81, 0, 0, 9, 94},     // C
                     {0, 0, 0, 0, 22, 33, 77, 6, 76, 0, 5, 0},      // D
                     {46, 56, 0, 0, 0, 71, 55, 75, 24, 98, 77, 45}, // E
                     {77, 0, 48, 0, 0, 0, 0, 0, 33, 0, 0, 0},       // F
                     {4, 97, 74, 8, 21, 0, 0, 19, 70, 0, 0, 49},    // G
                     {89, 0, 19, 0, 51, 29, 0, 0, 20, 89, 41, 0},   // H
                     {81, 38, 0, 0, 9, 65, 0, 50, 0, 28, 0, 0},     // I
                     {27, 94, 9, 76, 0, 12, 0, 0, 0, 0, 47, 0},     // J
                     {42, 0, 78, 28, 0, 59, 0, 3, 0, 100, 0, 0},    // K
                     {17, 0, 74, 38, 60, 0, 17, 19, 0, 66, 0, 0}};  // L
    //int G[20][20] = {{0}};
    int n = 12;
    string output = Traveling(G, n, 'A');
    int cost = pathlength(G, n, output);
    cout << output << endl;
    cout << cost;
       return 0;
}