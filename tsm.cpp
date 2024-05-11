#include"tsm.h"

bool notIn(int elm, int subset){
    return ((1 << elm) & subset) == 0;
}

void initCombinations(int set, int at, int r, int n, vector<int> subsets){
    int elementsLeftToPick = n - at;
    if (elementsLeftToPick < r) return;

    if (r == 0){
        subsets.push_back(set);
    } else {
        for (int i = at; i < n; i++){
            set = set | (1 << i);

            initCombinations(set, i + 1, r - 1, n, subsets);

            set = set & ~ (1 << i);
        }
    }
}

vector<int> combinations(int r, int n){
    vector<int> subsets;
    initCombinations(0,0,r,n,subsets);
    return subsets;
}

void setUp(int cityMap[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices){
    for (int i = 0; i < numberOfVertices; i++){
        if (i == source){
            continue;
        } else {
            memo[i][1 << source | 1 << i] = cityMap[source][i];
        }
    }
}

void solve(int cityMap[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices){
    vector<int> set;
    for (int r = 3; r <= numberOfVertices; r++){
        for(int subset : combinations(r,numberOfVertices)){
            if (notIn(source,subset)) continue;
            for (int next = 0; next < numberOfVertices; next ++){
                if (next == source || notIn(next,subset)) continue;
                int subsetWithoutNext = subset ^ (1 << next);
                int minDist = INFINITY;
                for (int end = 0; end < numberOfVertices; end++){
                    if (end == source || end == next || notIn(end,subset)) continue;
                    int newDistance = memo[end][subsetWithoutNext] + cityMap[end][next];
                    if (newDistance < minDist){
                        minDist = newDistance;
                    }
                }
                memo[next][subset] = minDist;
            }
        }
    }
}

string findOptimalTour(int cityMap[][numberOfVertices], vector<vector<int>> memo, int source, int numberOfVertices){
    int lastIndex = source;
    int state = (1 << numberOfVertices) - 1;
    string tour;
    tour += char(source + 'A');
    tour += " ";
    for (int i = 1; i < numberOfVertices; i++){
        int bestIndex = -1;
        int bestDist = INFINITY;
        for (int j = 0; j < numberOfVertices; j++){
            if (j == source || notIn(j,state)) continue;
            int newDist = memo[j][state] + cityMap[j][lastIndex];
            if (newDist < bestDist){
                bestIndex = j;
                bestDist = newDist;
            }
        }
        tour += char(bestIndex + 'A');
        tour += " ";
        state = state ^ (1 << bestIndex);
        lastIndex = bestIndex;
    }

    tour += char(source + 'A');

    return tour;
}

void Traveling(int cityMap[][numberOfVertices],char startVertex){
    vector<vector<int>> memo(numberOfVertices,vector<int>(1 << numberOfVertices,0));
    int source = int(startVertex - 'A');

    setUp(cityMap,memo,source,numberOfVertices);
    solve(cityMap,memo,source,numberOfVertices);
    
    cout << findOptimalTour(cityMap,memo,source,numberOfVertices);
}

