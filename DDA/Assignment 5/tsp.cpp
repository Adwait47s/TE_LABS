#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

void reduceMatrix(vector<vector<int>>& cost_matrix, vector<int>& row_reduction, vector<int>& col_reduction) {
    int n = cost_matrix.size();

    for (int i = 0; i < n; ++i) {
        int min_val = INF;
        for (int j = 0; j < n; ++j) {
            if (cost_matrix[i][j] < min_val) {
                min_val = cost_matrix[i][j];
            }
        }
        if (min_val != 0) {
            row_reduction[i] = min_val;
            for (int j = 0; j < n; ++j) {
                cost_matrix[i][j] -= min_val;
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        int min_val = INF;
        for (int i = 0; i < n; ++i) {
            if (cost_matrix[i][j] < min_val) {
                min_val = cost_matrix[i][j];
            }
        }
        if (min_val != 0) {
            col_reduction[j] = min_val;
            for (int i = 0; i < n; ++i) {
                cost_matrix[i][j] -= min_val;
            }
        }
    }
}

void branchAndBound(int level, int cost, int bound, vector<int>& path, int& optimal_cost, vector<int>& optimal_path,
                    const vector<vector<int>>& graph, const vector<vector<int>>& cost_matrix,
                    const vector<int>& row_reduction, const vector<int>& col_reduction) {
    int n = graph.size();

    if (level == n - 1) {
        if (graph[path.back()][0] != INF) {
            int current_cost = cost + graph[path.back()][0];
            if (current_cost < optimal_cost) {
                optimal_cost = current_cost;
                optimal_path = path;
            }
        }
        return;
    }

    for (int i = 1; i < n; ++i) {
        if (find(path.begin(), path.end(), i) == path.end() && graph[path.back()][i] != INF) {
            int next_bound = bound - row_reduction[path.back()] - col_reduction[i];

            // Calculate the new cost using the cost_matrix
            int next_cost = cost + graph[path.back()][i] + next_bound ;

            if (next_cost < optimal_cost) {
                path.push_back(i);
                branchAndBound(level + 1, cost + graph[path[level]][i], next_bound, path,
                               optimal_cost, optimal_path, graph, cost_matrix, row_reduction, col_reduction);
                path.pop_back();
            }
        }
    }
}


int main() {
    vector<vector<int>> graph = {
        {INF, 5, 4, 3},
        {3, INF, 8, 2},
        {5, 3, INF, 9},
        {6, 4, 3, INF}
    };

    int n = graph.size();
    vector<vector<int>> cost_matrix = graph;
    vector<int> row_reduction(n, 0);
    vector<int> col_reduction(n, 0);

    reduceMatrix(cost_matrix, row_reduction, col_reduction);

    vector<int> initial_path = {0};
    int optimal_cost = INF;
    vector<int> optimal_path;

    branchAndBound(0, 0, 0, initial_path, optimal_cost, optimal_path,
                   graph, cost_matrix, row_reduction, col_reduction);

    cout << "Optimal path: ";
    for (int node : optimal_path) {
        cout << node << " ";
    }
    cout << optimal_path[0] << "\n";
    cout << "Cost of Optimal path = " << optimal_cost << " units\n";

    return 0;
}
