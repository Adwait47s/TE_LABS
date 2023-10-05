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
vector<vector<int>> need_act;
vector<int> processes;
bool flag=1;

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

		vector<int>nedd;
		for(int j=0;j<numResources;j++){
			int needd = maxNeed[i][j] - allocation[i][j];
			debug(needd);
			nedd.push_back(needd);
		}
		need_act.push_back(nedd);

	}

	debug(processes);
	debug(allocation);
	debug(maxNeed);
	debug(need_act);
	debug(available);

	auto ori_allocation = allocation;
	auto ori_maxNeed = maxNeed;
	auto ori_available = available;
	auto ori_need = need_act;

	while(1){
		int choice;
		cout << "1.Display resource allocation state" << endl;
		cout << "2.Calculate Need" << endl;
		cout << "3.Safety Algorithm" << endl;
		cout << "4.Request" << endl;
		cout << "5.Exit" << endl;
		cout << "Please make choice :";
		cin>>choice;
		flag=1;
		cout << endl << endl;
		
		if(choice==1){
			cout << "Maximum resources required :" << endl;
			for(int i=0;i<numProcesses;i++){
				cout << "P" << i << ": ";
				for(int j=0;j<numResources;j++){
					cout << maxNeed[i][j]  << " ";
				}
				cout << endl;
				
			}
			cout << endl;
			cout << "Maximum resources allocated :" << endl;
			for(int i=0;i<numProcesses;i++){
				cout << "P" << i << ": ";
				for(int j=0;j<numResources;j++){
					cout << allocation[i][j]  << " ";
				}
				cout << endl;
				
			}
			cout << endl;
			cout << "Resources available :" << endl;
			char c = 'A';
			for(int i=0;i<numResources;i++) {
				cout << c << " : " <<available[i] << endl;
				c++;
			}
			cout << endl;
		}
		else if(choice==2){
			cout << "Need :" << endl;
			for(int i=0;i<numProcesses;i++){
				cout << "P" << i << ": ";
				for(int j=0;j<numResources;j++){
					cout << need_act[i][j] << " ";
				}
				cout << endl;
				
			}
			cout << endl;
		}
		else if(choice==4){
			cout << "Please enter the process for which you want a Request :";
			int reqprocess;
			cin>>reqprocess;
			flag=1;
			cout << "Please enter the resources for the Request :";
			vector<int>request(numResources,0);
			for(int i=0;i<numResources;i++){
				int req;
				cin>>request[i];
				if(request[i]>maxNeed[reqprocess][i] - allocation[reqprocess][i] || request[i]>available[i]){
					flag=0;
				}
				else{
					allocation[reqprocess][i]+= request[i];
					available[i]-=request[i];
					need_act[reqprocess][i]-=request[i];
				}
			}
			cout << endl << endl;
			if(!flag){
				cout << "Request is not valid !" << endl << endl;;
				continue;
			}
			debug(processes);
			debug(allocation);
			debug(maxNeed);
			debug(available);
		}
		else if(choice==5){
			cout << "Exiting code ..." << endl;
			break;
		}
		if((choice==4||choice==3)&&flag){
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
							if (need_act[i][j] > available[j]) {
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
			cout << endl<< endl;
			if (count==processes.size()) {
				if(choice==3){
					cout << "The system is in a safe state." << endl ;
				}
				else{
					cout << "Request Granted ! The system is in a safe state." << endl ;
				}
				
				cout << "Safe execution sequence: ";
				for (int i = 0; i < safeSequence.size(); i++) {
					cout << "P" << safeSequence[i] << " ";
				}
				cout << endl << endl;
			} 
			else {
				cout << "The system is in an unsafe state."<< endl << endl;
			}

			allocation = ori_allocation;
			available = ori_available;
			maxNeed = ori_maxNeed;
			need_act = ori_need;
		}

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

// 1
// 2
// 3
// 4
// 1
// 0 4 2 0
// 5

