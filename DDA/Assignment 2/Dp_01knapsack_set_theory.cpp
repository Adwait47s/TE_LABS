#include <bits/stdc++.h>
using namespace  std;
#define print(v) {for(int i=0;i<(int)v.size();++i)cout<<v[i]<<" ";nl;}


pair<int,int>anss;
set<pair<int,int>>combine(set<pair<int,int>>fir,set<pair<int,int>>sec,int m){
    vector<pair<int,int>>v;
    for(auto it:fir){
        if(it.second>m){
            continue;
        }
        v.push_back(it);
    }
    for(auto it:sec){
        if(it.second>m){
            continue;
        }
        v.push_back(it);
    }
    sort(v.begin(),v.end());
    int currcost=v[0].first,currweight=v[0].second;
    for(int i=1;i<v.size();i++){
        if(v[i].first>currcost && v[i].second>currweight){
            currcost=v[i].first;
            currweight = v[i].second;
        }
        else{
            v.erase(v.begin()+i-1);
            i--;    
            currcost=v[i-1].first;
            currweight = v[i-1].second;
        }
    }
    set<pair<int,int>>add;
    for(auto it:v){
        anss=it;
        add.insert(it);
    }
    return add;
}


int main(){
    int n;
    cout << "Please enter the total number of objects : ";
    cin>>n;
    cout << "Please enter the capacity of Knapsack : "; 
    int m;
    cin>>m;
    vector<pair<int,int>>v,vv;
    cout << "Please enter the weight and price of objects" << endl;
    for(int i=0;i<n;i++){
        int a,b;
        cout << "Profit of object "<< i+1 << ": ";
        cin>>a;
        cout << "Weight of object "<< i+1<< ": ";
        cin>>b;
        v.push_back({a,b});
    }
    vv=v;
    cout << endl;
    sort(v.begin(),v.end());
    vector<set<pair<int,int>>>ans;
    set<pair<int,int>>s; // profit weight
    s.insert({0,0});
    for(int i=0;i<n;i++){
        set<pair<int,int>>newset;
        for(auto it:s){
            newset.insert({it.first+v[i].first,it.second+v[i].second});
        }
        s = combine(s,newset,m);
        ans.push_back(s);
    }

    cout << "Max Profit : " << anss.first << endl;
    cout << "Knapsack capacity used :" << anss.second << endl;
    vector<int>taken(n,0);
    pair<int,int> p = {anss.first,anss.second};
    int i = n-1;
    while(i>=0 && p.first>0 && p.second>0){
        if(ans[i].count(p)){
            i--;
        }
        else{
            taken[i+1]=1;
            p.first-=v[i+1].first;
            p.second -= v[i+1].second;
        }
    }
    if(p.first!=0){
        taken[0]=1;
    }
    int ii=0;
    for(auto it:v){
        cout << it.first << " " << it.second << "      " << taken[ii] << endl;
        ii++;
    }
}