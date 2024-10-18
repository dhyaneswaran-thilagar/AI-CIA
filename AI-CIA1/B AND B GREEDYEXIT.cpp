
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <tuple>

using namespace std;

pair<vector<char>, int> branchAndBoundGreedyExit(const unordered_map<char, unordered_map<char, int>>& graph, 
                                                  char start, char goal, 
                                                  const unordered_map<char, int>& heuristics) {
    priority_queue<tuple<int, int, char, vector<char>>, vector<tuple<int, int, char, vector<char>>>, greater<tuple<int, int, char, vector<char>>>> queue;
    queue.push(make_tuple(heuristics.at(start), 0, start, vector<char>{start}));

    while (!queue.empty()) {
        auto [h, cost, node, path] = queue.top();
        queue.pop();
                if (node == goal) {
            return {path, cost}; 
                }
        for (const auto& neighbor : graph.at(node)) {
            if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
                int new_cost = cost + neighbor.second; 
                int new_h = heuristics.at(neighbor.first); 
                vector<char> newPath = path;
                newPath.push_back(neighbor.first); 
                queue.push(make_tuple(new_h, new_cost, neighbor.first, newPath)); 
            }
        }
    }

    return {{}, -1}; 
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

    // Heuristic values
    unordered_map<char, int> heuristics = {
        {'S', 10},
        {'A', 7},
        {'B', 6},
        {'C', 4},
        {'D', 3},
        {'E', 2},
        {'G', 0}
    };

    auto result = branchAndBoundGreedyExit(graph, 'S', 'G', heuristics);
    if (!result.first.empty()) {
        cout << "Path from S to G: ";
        for (char node : result.first) {
            cout << node << " ";
        }
        cout << "\nTotal cost: " << result.second << endl;
    } else {
        cout << "No path found from S to G." << endl;
    }

    return 0;
}
