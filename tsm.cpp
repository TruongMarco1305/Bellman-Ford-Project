#include"tsm.h"

void findTwoMin(int G[20][20], int numCities, int i, int &first, int &second)
{
    first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < numCities; j++)
    {
        if (i == j)
            continue;
        if (G[i][j] <= first)
        {
            second = first;
            first = G[i][j];
        }
        else if (G[i][j] <= second && G[i][j] != first)
        {
            second = G[i][j];
        }
    }
}

void branchAndBoundTSP(int G[20][20], int numCities, int (&curr_path)[21], int &curr_bound, int curr_weight
, int level, bool (&visited)[20], int &min_cost, int (&final_path)[21])
{
    if (level == numCities)
    {
        if (G[curr_path[level - 1]][curr_path[0]] != 0)
        {
            int curr_res = curr_weight +
                           G[curr_path[level - 1]][curr_path[0]];

            if (curr_res < min_cost)
            {
                for (int i = 0; i < numCities; i++)
                {
                    final_path[i] = curr_path[i];
                }
                final_path[numCities] = curr_path[0];
                min_cost = curr_res;
            }
        }
    }
    else
    {
        for (int i = 0; i < numCities; i++)
        {
            if (G[curr_path[level - 1]][i] != 0 &&
                visited[i] == false)
            {
                int temp = curr_bound;
                curr_weight += G[curr_path[level - 1]][i];

                int firstMinCurr, secondMinCurr;
                findTwoMin(G, numCities, curr_path[level - 1], firstMinCurr, secondMinCurr);
                int firstMinNext, secondMinNext;
                findTwoMin(G, numCities, i, firstMinNext, secondMinNext);

                curr_bound -= ((secondMinCurr + firstMinNext) / 2);

                // curr_bound -= ((secondMin(G, numCities, curr_path[level - 1]) + firstMin(G, numCities, i)) / 2);

                if (curr_bound + curr_weight < min_cost)
                {
                    curr_path[level] = i;
                    visited[i] = true;

                    branchAndBoundTSP(G, numCities, curr_path, curr_bound, curr_weight, level + 1, visited, min_cost, final_path);
                }

                curr_weight -= G[curr_path[level - 1]][i];
                curr_bound = temp;

                for (int i = 0; i < numCities + 1; i++)
                {
                    visited[i] = false;
                }

                for (int j = 0; j <= level - 1; j++)
                {
                    visited[curr_path[j]] = true;
                }
            }
        }
    }
}

string Traveling(int G[20][20], int numCities, char startVertex)
{

    int curr_path[21] = {-1};
    bool visited[20] = {false};
    int final_path[21] = {-1};
    int min_cost = INT_MAX;
    int curr_bound = 0;
    string ans;

    for (int i = 0; i < numCities; i++)
    {
        int first, second;
        findTwoMin(G, numCities, i, first, second);
        curr_bound += (first + second);
        // curr_bound += (firstMin(G,numCities,i) + secondMin(G,numCities,i));
    }

    if (curr_bound % 2 == 0)
    {
        curr_bound = curr_bound / 2;
    }
    else
    {
        curr_bound = curr_bound / 2 + 1;
    }

    visited[int(startVertex - 'A')] = true;
    curr_path[0] = int(startVertex - 'A');

    branchAndBoundTSP(G, numCities, curr_path, curr_bound, 0, 1, visited, min_cost, final_path);

    for (int i = 0; i <= numCities; i++)
    {
        ans += char(final_path[i] + 'A');
        ans += " ";
    }

    return ans;
}
