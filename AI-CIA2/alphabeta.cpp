#include <iostream>
#include <algorithm>
#include <limits.h>

using namespace std;

int node_count = 0; 

int alpha_beta(int depth, int node_index, bool is_maximizing, int leaf_values[], int alpha, int beta) {
    if (depth == 3) {
        node_count++; 
        return leaf_values[node_index];
    }

    if (is_maximizing) {
        int max_score = INT_MIN;
        for (int i = 0; i < 2; i++) { 
            int score = alpha_beta(depth + 1, node_index * 2 + i, false, leaf_values, alpha, beta);
            max_score = max(max_score, score);
            alpha = max(alpha, score);
            if (beta <= alpha) {
                break; 
            }
        }
        return max_score;
    } else {
        int min_score = INT_MAX;
        for (int i = 0; i < 2; i++) {
            int score = alpha_beta(depth + 1, node_index * 2 + i, true, leaf_values, alpha, beta);
            min_score = min(min_score, score);
            beta = min(beta, score);
            if (beta <= alpha) {
                break; 
            }
        }
        return min_score;
    }
}

int main() {
    int leaf_values[] = {4, 8, 9, 3, 2, -2, 9, 1};
    int alpha = INT_MIN;
    int beta = INT_MAX;

    int optimal_value = alpha_beta(0, 0, true, leaf_values, alpha, beta);

    int total_nodes = sizeof(leaf_values) / sizeof(leaf_values[0]); // Total leaf nodes
    int nodes_saved = total_nodes - node_count;
    double percentage_saved = (nodes_saved / (double)total_nodes) * 100;

    cout << "The optimal value after the pruning process is " << optimal_value << endl;
    cout << "Total nodes computed: " << node_count << endl;
    cout << "Percentage of nodes saved by pruning: " << percentage_saved << "%" << endl;

    return 0;
}

