#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

class TSPBranchAndBound {
public:
    TSPBranchAndBound(const vector<vector<int>>& graph) : graph_(graph), n_(graph.size()) {
        cost_matrix_ = graph;
        row_reduction_.resize(n_, 0);
        col_reduction_.resize(n_, 0);
        reduceMatrix();
    }

    void solve() {
        vector<int> initial_path = {0};
        branchAndBound(0, 0, 0, initial_path);
        cout << "Optimal path: ";
        for (int node : optimal_path_) {
            cout << node << " ";
        }
        cout << optimal_path_[0] << "\n";
        cout << "Cost of Optimal path = " << optimal_cost_ << " units\n";
    }

private:
    void reduceMatrix() {
        for (int i = 0; i < n_; ++i) {
            int min_val = INF;
            for (int j = 0; j < n_; ++j) {
                if (cost_matrix_[i][j] < min_val) {
                    min_val = cost_matrix_[i][j];
                }
            }
            if (min_val != 0) {
                row_reduction_[i] = min_val;
                for (int j = 0; j < n_; ++j) {
                    cost_matrix_[i][j] -= min_val;
                }
            }
        }

        for (int j = 0; j < n_; ++j) {
            int min_val = INF;
            for (int i = 0; i < n_; ++i) {
                if (cost_matrix_[i][j] < min_val) {
                    min_val = cost_matrix_[i][j];
                }
            }
            if (min_val != 0) {
                col_reduction_[j] = min_val;
                for (int i = 0; i < n_; ++i) {
                    cost_matrix_[i][j] -= min_val;
                }
            }
        }
    }

    void branchAndBound(int level, int cost, int bound, vector<int> path) {
        if (level == n_ - 1) {
            if (graph_[path.back()][0] != INF) {
                int current_cost = cost + graph_[path.back()][0];
                if (current_cost < optimal_cost_) {
                    optimal_cost_ = current_cost;
                    optimal_path_ = path;
                }
            }
            return;
        }

        for (int i = 1; i < n_; ++i) {
            if (find(path.begin(), path.end(), i) == path.end() && graph_[path.back()][i] != INF) {
                int next_bound = bound - row_reduction_[path.back()] - col_reduction_[i];
                int next_cost = cost + graph_[path.back()][i] + next_bound;

                if (next_cost < optimal_cost_) {
                    path.push_back(i);
                    branchAndBound(level + 1, cost + graph_[path[level]][i], next_bound, path);
                    path.pop_back();
                }
            }
        }
    }

    vector<vector<int>> graph_;
    vector<vector<int>> cost_matrix_;
    vector<int> row_reduction_;
    vector<int> col_reduction_;
    vector<int> optimal_path_;
    int optimal_cost_ = INF;
    int n_;
};

int main() {
    vector<vector<int>> graph = {
        {INF, 4, 12, 7},
        {5, INF, INF, 18},
        {11, INF, INF, 6},
        {10, 2, 3, INF}
    };

    TSPBranchAndBound tsp(graph);
    tsp.solve();

    return 0;
}
