#include <bits/stdc++.h>

using namespace std;

void reduceMatrix(int (&reduced_G)[20][20], int numCities, int &cost)
{
    // Reset cost
    cost = 0;

    // Row reduction
    for (int i = 0; i < numCities; i++)
    {
        int rowMin = INT_MAX;
        for (int j = 0; j < numCities; j++)
        {
            if (reduced_G[i][j] < rowMin)
                rowMin = reduced_G[i][j];
        }
        if (rowMin != INT_MAX && rowMin != 0)
        {
            for (int j = 0; j < numCities; j++)
            {
                if (reduced_G[i][j] != INT_MAX)
                    reduced_G[i][j] -= rowMin;
            }
            cost += rowMin;
        }
    }

    // Column reduction
    for (int j = 0; j < numCities; j++)
    {
        int colMin = INT_MAX;
        for (int i = 0; i < numCities; i++)
        {
            if (reduced_G[i][j] < colMin)
                colMin = reduced_G[i][j];
        }
        if (colMin != INT_MAX && colMin != 0)
        {
            for (int i = 0; i < numCities; i++)
            {
                if (reduced_G[i][j] != INT_MAX)
                    reduced_G[i][j] -= colMin;
            }
            cost += colMin;
        }
    }
}

void branchAndBound(int (&reduced_G)[20][20], int numCities, int (&curr_path)[20], int curr_bound, int curr_weight, int level, bool (&visited)[20], int &min_cost, int (&final_path)[20])
{
    if (level == numCities)
    {
        if (reduced_G[curr_path[level - 1]][curr_path[0]] != INT_MAX)
        {
            int curr_res = curr_weight + reduced_G[curr_path[level - 1]][curr_path[0]];
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
            if (!visited[i] && reduced_G[curr_path[level - 1]][i] != INT_MAX)
            {
                int temp_bound = curr_bound;
                curr_weight += reduced_G[curr_path[level - 1]][i];

                int temp_G[20][20];
                for (int k = 0; k < numCities; k++)
                {
                    for (int j = 0; j < numCities; j++)
                    {
                        temp_G[k][j] = reduced_G[k][j];
                    }
                }

                for (int j = 0; j < numCities; j++)
                {
                    temp_G[curr_path[level - 1]][j] = INT_MAX;
                    temp_G[j][i] = INT_MAX;
                }
                temp_G[i][0] = INT_MAX;

                reduceMatrix(temp_G, numCities, temp_bound);

                if (temp_bound + curr_weight < min_cost)
                {
                    curr_path[level] = i;
                    visited[i] = true;

                    branchAndBound(temp_G, numCities, curr_path, temp_bound, curr_weight, level + 1, visited, min_cost, final_path);
                }

                curr_weight -= reduced_G[curr_path[level - 1]][i];

                fill(visited, visited + numCities, false);
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
    int curr_path[20];
    bool visited[20] = {false};
    int final_path[20];
    int min_cost = INT_MAX;
    int curr_bound = 0;
    string ans;
    int reduced_G[20][20];

    fill(curr_path, curr_path + 20, -1);
    fill(final_path, final_path + 20, -1);

    for (int i = 0; i < numCities; i++)
    {
        for (int j = 0; j < numCities; j++)
        {
            reduced_G[i][j] = G[i][j];
        }
    }

    reduceMatrix(reduced_G, numCities, curr_bound);

    int startIdx = startVertex - 'A';
    visited[startIdx] = true;
    curr_path[0] = startIdx;

    branchAndBound(reduced_G, numCities, curr_path, curr_bound, 0, 1, visited, min_cost, final_path);

    for (int i = 0; i <= numCities; i++)
    {
        if (final_path[i] != -1)
        {
            ans += char(final_path[i] + 'A');
            if (i < numCities)
                ans += " ";
        }
    }
    return ans;
}

int pathlength(int G[20][20], int numCities, string output)
{
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
    int n = 12;
    string output = Traveling(G, n, 'A');
    int cost = pathlength(G, n, output);
    cout << output << endl;
    cout << cost << endl;
    return 0;
}