#include"tsm.h"

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
            if(secondMin[i] >= G[i][j] && G[i][j] >= firstMin[i]) secondMin[i] = G[i][j];
        }
    }
}

void branchAndBoundTSP(int G[20][20], int numCities, int (&currentPath)[21], int &currentBound, int currentCost, int level, bool (&visited)[20], int &finalCost, int (&finalPath)[21], int firstMin[20], int secondMin[20])
{
    //Base case: When the search tree has reached the level N
    //which mean the algorithm has covered all nodes
    if (level == numCities)
    {
        //Check if there is a path from last vertex in the current path to the start vertex
        if (G[currentPath[level - 1]][currentPath[0]] != 0)
        {
            //The total weight of the current path
            int currentResult = currentCost + G[currentPath[level - 1]][currentPath[0]];

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

                //Different computation for level 1 from others
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
    //Check for special case
    if (numCities == 1){
        string ans;
        ans += startVertex;
        return ans;
    }
    //Initialization 
    int currentPath[21] = {-1};
    bool visited[20] = {false};
    int finalPath[21] = {-1};
    int finalCost = 100000;
    int currentBound = 0;
    string ans;

    //Fill in the minimum and second minimum weight edge for each vertex
    int firstMin[20] = {-1};
    int secondMin[20] = {-1};
    findTwoMin(G,numCities,firstMin,secondMin);

    //Calculate the bound for any tour by formula:
    //1/2 * (sum of first minimum and second minimum of all vertices)
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
