#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

int calculatePathCost(const unordered_map<char, unordered_map<char, int>>& graph, const vector<char>& path) {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        if (graph.at(path[i]).count(path[i + 1])) {
            cost += graph.at(path[i]).at(path[i + 1]);
        } else {
            return numeric_limits<int>::max();
        }
    }
    return cost;
}

void findAllPaths(const unordered_map<char, unordered_map<char, int>>& graph, char current, char goal, 
                  vector<char>& path, vector<vector<char>>& allPaths) {
    path.push_back(current);

    if (current == goal) {
        allPaths.push_back(path);
    } else {
        for (const auto& neighbor : graph.at(current)) {
            findAllPaths(graph, neighbor.first, goal, path, allPaths);
        }
    }

    path.pop_back();
}

pair<vector<char>, int> britishMuseumSearch(const unordered_map<char, unordered_map<char, int>>& graph, char start, char goal) {
    vector<vector<char>> allPaths;
    vector<char> path;
    findAllPaths(graph, start, goal, path, allPaths);

    vector<char> bestPath;
    int bestCost = numeric_limits<int>::max();

    for (const auto& p : allPaths) {
        int cost = calculatePathCost(graph, p);
        if (cost < bestCost) {
            bestCost = cost;
            bestPath = p;
        }
    }

    return {bestPath, bestCost};
}

int main() {
    unordered_map<char, unordered_map<char, int>> graph = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'B', 4}, {'D', 3}}},
        {'B', {{'C', 4}}},
        {'C', {{'E', 6}}},
        {'D', {{'G', 5}}},
        {'E', {}},
        {'G', {}}
    };

    auto result = britishMuseumSearch(graph, 'S', 'G');

    if (!result.first.empty()) {
        cout << "Best path from S to G: ";
        for (char node : result.first) {
            cout << node << " ";
        }
        cout << "\nTotal cost: " << result.second << endl;
    } else {
        cout << "No path found from S to G." << endl;
    }

    return 0;
}
