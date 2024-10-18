#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

pair<vector<char>, int> oracle_algorithm(const unordered_map<char, unordered_map<char, int>>& graph, 
                                         char start, char goal) {
    vector<char> optimal_path = {'S', 'A', 'D', 'G'};
    int optimal_cost = 0;

    for (size_t i = 0; i < optimal_path.size() - 1; ++i) {
        char current = optimal_path[i];
        char next = optimal_path[i + 1];
        optimal_cost += graph.at(current).at(next); 
    }

    return {optimal_path, optimal_cost}; 
}

int main() {
    // Graph 
    unordered_map<char, unordered_map<char, int>> graph = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'B', 4}, {'D', 3}}},
        {'B', {{'C', 4}}},
        {'C', {{'E', 6}}},
        {'D', {{'G', 5}}},
        {'E', {}},
        {'G', {}}
    };
    auto [path, cost] = oracle_algorithm(graph, 'S', 'G');
    cout << "Optimal Path: ";
    for (char node : path) {
        cout << node << " ";
    }
    cout << "\nOptimal Cost: " << cost << endl;

    return 0;
}
