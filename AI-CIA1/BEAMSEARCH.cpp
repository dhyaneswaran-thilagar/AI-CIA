#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int heuristic;
    char name;
    vector<char> path;

    bool operator>(const Node& other) const {
        return heuristic > other.heuristic;
    }
};
vector<char> beamSearch(const unordered_map<char, unordered_map<char, int>>& graph, char start, char goal, 
                        const unordered_map<char, int>& heuristics, int beamWidth = 2) {
    priority_queue<Node, vector<Node>, greater<Node>> beam;
    beam.push({heuristics.at(start), start, {start}});

    while (!beam.empty()) {
        vector<Node> newBeam;
        for (int i = 0; i < min(beamWidth, (int)beam.size()); ++i) {
            Node current = beam.top();
            beam.pop();

            if (current.name == goal) {
                return current.path; 
            }

            for (const auto& neighbor : graph.at(current.name)) {
                if (find(current.path.begin(), current.path.end(), neighbor.first) == current.path.end()) {
                    int h = heuristics.at(neighbor.first);
                    vector<char> newPath = current.path;
                    newPath.push_back(neighbor.first);
                    newBeam.push_back({h, neighbor.first, newPath});
                }
            }
        }
        for (const auto& node : newBeam) {
            beam.push(node);
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
    vector<char> path = beamSearch(graph, 'S', 'G', heuristics);
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

