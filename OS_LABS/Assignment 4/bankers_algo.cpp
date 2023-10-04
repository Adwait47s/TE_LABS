#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

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

int numResources;
vector<int> totalResources;
vector<int> available;
vector<vector<int>> allocation;
vector<vector<int>> maxNeed;
vector<int> processes;



int main() {
    int numResources, numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;

    cout << "Enter the total quantity of each resource: ";
    for (int i = 0; i < numResources; i++) {
        int r;
        cin>>r;
        totalResources.push_back(r);
    }
    vector<int> available =  totalResources;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; i++) {
        int processId =i;
        processes.push_back(processId);
        vector<int> allc(numResources);
        cout << "Enter already allocated resources for process " << processId << ": ";
        for (int j = 0; j < numResources; j++) {

            cin >> allc[j];
            available[j] -= allc[j];
        }

        allocation.push_back(allc);

        vector<int> maxx(numResources);
        cout << "Enter max resources needed for process " << processId << ": ";
        for (int j = 0; j < numResources; j++) {
            cin >> maxx[j];
        }
        maxNeed.push_back(maxx);
    }

    debug(processes);
    debug(allocation);
    debug(maxNeed);
    debug(available);

    vector<int> safeSequence;
    vector<bool> finish(processes.size(), 0);
    int count = 0;
    while (count < processes.size()) {
        bool found = false;
        debug(count);
        for (int i = 0; i < processes.size(); i++) {
            int processId = i;
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < numResources; j++) {
                    if (maxNeed[processId][j] - allocation[processId][j] > available[j]) {
                        debug(available[j],maxNeed[processId][j]);
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < numResources; j++) {
                        available[j] += allocation[processId][j];
                    }
                    safeSequence.push_back(processId);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

    }
    if (count==processes.size()) {
        cout << "The system is in a safe state.\n";
        cout << "Safe execution sequence: ";
        for (int i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i] << " ";
        }
        cout << endl;
    } else {
        cout << "The system is in an unsafe state.\n";
    }

    return 0;
}

// input 

// 4
// 3 14 12 12

// 5

// 0 0 1 2
// 0 0 1 2

// 1 0 0 0
// 1 7 5 0

// 1 3 5 4
// 2 3 5 6

// 0 6 3 2
// 0 6 5 2

// 0 0 1 4
// 0 6 5 6


