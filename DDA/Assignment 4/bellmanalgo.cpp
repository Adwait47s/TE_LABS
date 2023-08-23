#include <bits/stdc++.h>
using namespace  std;
#define print(v) {for(int i=0;i<(int)v.size();++i)cout<<v[i]<<" ";nl;}

/*==================== Debug =======================================================*/
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
// void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
 
template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif
/*=======================================================================================*/
 
 
/*
   *********************SOLVE****************************
*/   


void BellmanFord(vector<vector<int>>& edges, int V, int E, int source) {
    vector<int> distances(V+1, INT_MAX);
    distances[source] = 0;

    for (int i = 1; i <= V -1; ++i) {
        for (const vector<int>& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    // Check for negative cycles
    for (const vector<int>& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];

        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            cout << "Graph contains a negative cycle associated with edge : " ;
            cout << u << "--" << v<< " having weight " << weight << endl;
            return;
        }
    }

    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 1; i <= V; ++i) {
        cout << i << "\t" << distances[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> edges(E, vector<int>(3));
    cout << "Enter source, destination, and weight for each edge:" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;
    cout << endl;
    BellmanFord(edges, V, E, source);
}

// input
// 7 10
// 1 2 6
// 1 3 2
// 1 4 5
// 3 2 -2
// 2 5 -1
// 3 5 1
// 4 3 -2
// 4 6 -1
// 6 7 3
// 5 7 3
// 1

// input for -ve edge cycle 
// 4 4
// 1 2 1
// 2 3 2
// 3 4 3
// 4 1 -7
// 1

// or 

// 5 9
// 1 2 2
// 1 3 7
// 2 3 9
// 4 2 -3
// 2 4 5
// 3 4 -8
// 5 4 5
// 3 5 10
// 5 1 2
// 1
