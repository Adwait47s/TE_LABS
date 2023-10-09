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
vector<char>f1,f2,f3;

void printoutput(){

	cout << "F1 : ";
	for(int i=0;i<f1.size();i++){
		cout << f1[i] << " ";
	}
	cout << endl;

	cout << "F2 : ";
	for(int i=0;i<f1.size();i++){
		cout << f2[i] << " ";
	}
	cout << endl;

	cout << "F3 : ";
	for(int i=0;i<f1.size();i++){
		cout << f3[i] << " ";
	}
	cout << endl;
}
int main(){
	cout << "Please enter the size of reference string : ";
	int n;
	cin>>n;
	vector<int>v;
	cout << "Please enter each page " << endl;
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		v.push_back(a);
	}

	while(1){
		cout << "1.FIFO" << endl;
		cout << "2.LRU" << endl;
		cout << "3.Optimal" << endl;
		cout << "4.Exit" << endl;
		cout << "Please make choice : ";
		int choice;
		cin>>choice;
		cout << endl<< endl;
		
		int hit=0,fault=0;

		if(choice==1){

		}
		else if(choice==2){
			cout << "LRU : " << endl;
			vector<int>curr;
			set<int>s;

			for(int i=0;i<n;i++){
				if(s.count(v[i])){
					hit++;
					for(int j=0;j<curr.size();j++){
						if(curr[j]==v[i]){
							curr.erase(curr.begin()+j);
							break;
						}
					}
					curr.push_back(v[i]);
				}
				else{
					fault++;
					if(curr.size()<3){
						curr.push_back(v[i]);
					}
					else{
						s.erase(curr[0]);
						curr.erase(curr.begin()+0);
						curr.push_back(v[i]);
					}
					s.insert(v[i]);
				}
				debug(curr);
				//f1
				//f2
				//f3
				f3.push_back(curr[0]+ '0');
				if(curr.size()>1){
					f2.push_back(curr[1] + '0');
				}
				else{
					f2.push_back('-');
				}
				if(curr.size()>2){
					f1.push_back(curr[2]+ '0');
				}
				else{
					f1.push_back('-');
				}

			}
			debug(f1);
			debug(f2);
			debug(f3);
			printoutput();
			cout << "Page Hits : " << hit << endl;
			cout << "Page Faults : " << fault << endl;
		}
		else if(choice==3){

		}
		else if(choice==4){
			cout << "Exiting the code..." << endl;
			break;
		}
		else{
			cout << "Please enter the correct choice" << endl;
		}
		
		f1.clear();
		f2.clear();
		f3.clear();
		cout << endl;
	}

}

// intput 

// 20
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
// 2
// 4