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
vector<char>f1,f2,f3,f4;

int findOptimal(int idx, vector<int>& v, vector<int>& curr) {
    int n = v.size();
    int farthest = -1;
    int farthestIdx = -1;
    for (int i = 0; i < curr.size(); i++) {
        int j;
        for (j = idx; j < n; j++) {
            if (curr[i] == v[j]) {
                if (j > farthest) {
                    farthest = j;
                    farthestIdx = i;
                }
                break;
            }
        }
        if (j == n) return i; // If a page is not used in the future, replace it
    }
    return farthestIdx; // Replace the page that will be used farthest in the future
}


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

    cout << "Hit: ";
    for(int i=0;i<f1.size();i++){
        if(f4[i]=='1'){
            cout <<  "√" << " ";
        }
        else{
            cout << "×" << " ";
        }
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
        vector<int>curr;
        set<int>s;
        if(choice==1){
            cout << "FIFO : " << endl;
            vector<int>queue; 
            for(int i=0;i<n;i++){
                if(s.count(v[i])){
                    hit++;
                    f4.push_back('1');
                }
                else{
                    fault++;
                    f4.push_back('0');
                    if(curr.size()<3){
                        curr.push_back(v[i]);
                        queue.push_back(v[i]);
                    }
                    else{
                        int firstone = queue[0];
                        debug(firstone);
                        s.erase(firstone);
                        debug(queue);
                        debug(curr);
                        for(int j=0;j<curr.size();j++){
                            if(firstone==curr[j]){
                                curr[j] = v[i];
                                break;
                            }
                        }
                        queue.erase(queue.begin()+0);
                        queue.push_back(v[i]);
                    }
                    s.insert(v[i]);
                }
                //f1
                //f2
                //f3
                f1.push_back(curr[0]+ '0');
                if(curr.size()>1){
                    f2.push_back(curr[1] + '0');
                }
                else{
                    f2.push_back('-');
                }
                if(curr.size()>2){
                    f3.push_back(curr[2]+ '0');
                }
                else{
                    f3.push_back('-');
                }
            }
            debug(f1);
            debug(f2);
            debug(f3);
            printoutput();
            cout << "Page Hits : " << hit << endl;
            cout << "Page Faults : " << fault << endl;
        }
        else if(choice==2){
            cout << "LRU : " << endl;
            for(int i=0;i<n;i++){
                if(s.count(v[i])){
                    hit++;
                    f4.push_back('1');
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
                    f4.push_back('0');
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
        else if (choice == 3) {
            cout << "Optimal : " << endl;
            for (int i = 0; i < n; i++) {
                if (s.count(v[i])) {
                    hit++;
                    f4.push_back('1');
                } else {
                    fault++;
                    f4.push_back('0');
                    if (curr.size() < 3) {
                        curr.push_back(v[i]);
                    } else {
                        int replaceIdx = findOptimal(i, v, curr);
                        s.erase(curr[replaceIdx]);
                        curr[replaceIdx] = v[i];
                    }
                    s.insert(v[i]);
                }
            // f1
            // f2
            // f3
                f1.push_back(curr[0] + '0');
                if (curr.size() > 1) {
                    f2.push_back(curr[1] + '0');
                } else {
                    f2.push_back('-');
                }
                if (curr.size() > 2) {
                    f3.push_back(curr[2] + '0');
                } else {
                    f3.push_back('-');
                }
            }
            debug(f1);
            debug(f2);
            debug(f3);
            printoutput();
            cout << "Page Hits : " << hit << endl;
            cout << "Page Faults : " << fault << endl;
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
        f4.clear();
        s.clear();
        hit=0;
        fault=0;
        cout << endl;
    }

}

// intput 

// 20
// 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
// 1
// 2
// 4
