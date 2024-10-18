#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> hill_climbing(const unordered_map<char, unordered_map<char, int>>& graph, 
                           char start, char goal, 
                           const unordered_map<char, int>& heuristics) {
    char current = start;
    vector<char> path = {current};

    while (current != goal) {
        const auto& neighbors = graph.at(current);
        
        if (neighbors.empty()) {
            return {};
        }

        vector<pair<char, int>> sorted_neighbors;
        for (const auto& neighbor : neighbors) {
            sorted_neighbors.push_back({neighbor.first, heuristics.at(neighbor.first)});
        }

        sort(sorted_neighbors.begin(), sorted_neighbors.end(), 
             [](const pair<char, int>& a, const pair<char, int>& b) {
                 if (a.second == b.second) return a.first < b.first;
                 return a.second < b.second;
             });

        char next_node = sorted_neighbors[0].first;
        current = next_node;
        path.push_back(current);
    }

    return path;
}

int main() {
    unordered_map<char, unordered_map<char, int>> graph = {
        {'S', {{'A', 8}, {'B', 6}}},
        {'A', {{'D', 5}}},
        {'B', {{'A', 7}, {'C', 12}}},
        {'C', {}},
        {'D', {{'G', 5}}},
        {'G', {}}
    };
    unordered_map<char, int> heuristics = {
        {'S', 10},
        {'A', 7},  
        {'B', 6},   
        {'C', 20}, 
        {'D', 5},  
        {'G', 0}   
    };
    vector<char> result = hill_climbing(graph, 'S', 'G', heuristics);
    if (!result.empty() && result.back() == 'G') {
        cout << "Path from S to G: ";
        for (char node : result) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from S to G." << endl;
    }

    return 0;
}
