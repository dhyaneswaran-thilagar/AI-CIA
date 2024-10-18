#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm> 
#include <tuple>

using namespace std;
pair<vector<char>, int> branchAndBound(const unordered_map<char, unordered_map<char, int>>& graph, 
                                        char start, char goal) {
    priority_queue<tuple<int, char, vector<char>>, vector<tuple<int, char, vector<char>>>, greater<tuple<int, char, vector<char>>>> queue;
    queue.push(make_tuple(0, start, vector<char>{start}));

    int best_cost = INT_MAX;
    vector<char> best_path;

    while (!queue.empty()) {
        auto [cost, node, path] = queue.top();
        queue.pop();
        if (node == goal) {
            if (cost < best_cost) {
                best_cost = cost;
                best_path = path; 
            }
            continue; 
        }
        for (const auto& neighbor : graph.at(node)) {
            if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
                vector<char> newPath = path;
                newPath.push_back(neighbor.first); // Extend path
                queue.push(make_tuple(cost + neighbor.second, neighbor.first, newPath)); // Push to the queue
            }
        }
    }

    return {best_path, best_cost}; 
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
    auto result = branchAndBound(graph, 'S', 'G');

    // Print the result
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
