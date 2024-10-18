#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

class Graph {
public:
    unordered_map<char, vector<char>> adjList;

    void addEdge(char u, char v) {
        adjList[u].push_back(v);
    }

    vector<char> dfs(char start, char goal) {
        stack<pair<char, vector<char>>> s;
        unordered_set<char> visited;
        s.push({start, {start}});

        while (!s.empty()) {
            auto [node, path] = s.top();
            s.pop();

            if (visited.find(node) == visited.end()) {
                if (node == goal) {
                    return path;
                }

                visited.insert(node);

                for (char neighbor : adjList[node]) {
                    if (visited.find(neighbor) == visited.end()) {
                        vector<char> newPath = path;
                        newPath.push_back(neighbor);
                        s.push({neighbor, newPath});
                    }
                }
            }
        }
        return {};
    }
};

int main() {
    Graph graph;

    graph.addEdge('S', 'A');
    graph.addEdge('S', 'B');
    graph.addEdge('A', 'B');
    graph.addEdge('A', 'D');
    graph.addEdge('B', 'C');
    graph.addEdge('C', 'E');
    graph.addEdge('D', 'G');

    vector<char> path = graph.dfs('S', 'G');

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
