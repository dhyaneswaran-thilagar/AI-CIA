#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;
vector<char> bfs(const unordered_map<char, unordered_map<char, int>>& graph, char start, char goal) {
    queue<pair<char, vector<char>>> q;
    unordered_set<char> visited;

    q.push({start, {start}});

    while (!q.empty()) {
        auto [node, path] = q.front();
        q.pop();

        if (visited.find(node) == visited.end()) {
            if (node == goal) {
                return path; 
            }
            visited.insert(node);

            for (const auto& neighbor : graph.at(node)) {
                if (visited.find(neighbor.first) == visited.end()) {
                    vector<char> newPath = path;
                    newPath.push_back(neighbor.first);
                    q.push({neighbor.first, newPath});
                }
            }
        }
    }
    return {}; 
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
    vector<char> path = bfs(graph, 'S', 'G');
    if (!path.empty()) {
        cout << "Path from S to G: ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from S to G." << endl;
    }

    return 0;
}
