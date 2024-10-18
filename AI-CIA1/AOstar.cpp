#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <queue>
#include <set>

using namespace std;

struct Node {
    char id;              
    int cost;              
    int heuristic;        
    vector<Node*> children; 
    Node(char id, int cost, int heuristic)
        : id(id), cost(cost), heuristic(heuristic) {}
};

vector<char> aoStar(Node* start, char goal) {
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> openSet;
    unordered_map<char, int> bestCosts; 
    unordered_map<char, Node*> parent; 

 
    openSet.push({start->cost + start->heuristic, start});
    bestCosts[start->id] = start->cost;

    while (!openSet.empty()) {
        auto currentPair = openSet.top();
        openSet.pop();
        Node* currentNode = currentPair.second;

        if (currentNode->id == goal) {
            vector<char> path;
            char curr = goal;

            while (curr != start->id) {
                path.push_back(curr);
                curr = parent[curr]->id;
            }
            path.push_back(start->id);
            reverse(path.begin(), path.end());
            return path;
        }

        for (Node* child : currentNode->children) {
            int newCost = currentNode->cost + child->cost;

            if (bestCosts.find(child->id) == bestCosts.end() || newCost < bestCosts[child->id]) {
                bestCosts[child->id] = newCost;
                parent[child->id] = currentNode;
                openSet.push({newCost + child->heuristic, child});
            }
        }
    }

    return {};
}

int main() {
    Node* S = new Node('S', 0, 10);
    Node* A = new Node('A', 3, 7);
    Node* B = new Node('B', 5, 6);
    Node* C = new Node('C', 4, 4);
    Node* D = new Node('D', 3, 3);
    Node* E = new Node('E', 6, 2);
    Node* G = new Node('G', 5, 0);

    S->children = {A, B};
    A->children = {B, D};
    B->children = {C};
    C->children = {E};
    D->children = {G};

    vector<char> result = aoStar(S, 'G');


    if (!result.empty()) {
        cout << "Path from S to G: ";
        for (char node : result) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from S to G." << endl;
    }
    delete S;
    delete A;
    delete B;
    delete C;
    delete D;
    delete E;
    delete G;

    return 0;
}
