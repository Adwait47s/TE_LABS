#include <bits/stdc++.h>
using namespace std;
int main(){
    cout << "Please enter the totol number of items : ";
    int n;
    cin>>n;
    cout << "Please enter the profit of all the items :" << endl;
    vector<double>profit,weight;
    map<pair<int,int>,int>items;
    for(int i=0;i<n;i++){
        int a; cin>>a;
        profit.push_back(a);
    } 
    cout << "Please the cost of all the items :" << endl;
    for(int i=0;i<n;i++){
        double a;
        cin>>a;
        weight.push_back(a);
        items[{profit[i],a}]=i+1;
    }
    map<double,set<pair<int,int>>>m;
    for(int i=0;i<n;i++){
        double cost = profit[i]/ weight[i];
        m[-cost].insert({profit[i],weight[i]});
    }
    cout << "Please enter the size of knapsack :" << endl;
    double mm;
    cin>>mm;
    vector<pair<int,int>>ans;
    vector<double>quantity;
    for(auto it:m){
    	for(auto itt:it.second){
    		double weightt = itt.second;
    		if(weightt<=mm){
    			mm-=weightt;
    			ans.push_back({itt.first,itt.second});
    			quantity.push_back(1);
    		}
    		else{
    			double taken = mm/itt.second;
    			ans.push_back({itt.first,itt.second});
    			quantity.push_back(taken);
    			mm=0;
    			break;
    		}
    	}
    }
    double profitt=0;
    double weighttt=0;
    for(int i=0;i<ans.size();i++){
    	profitt+= (ans[i].first*quantity[i]);
    	weighttt += (ans[i].second*quantity[i]);
    }
    cout << "Items taken and Quantity" << endl;
    for(int i=0;i<ans.size();i++){
    	cout << items[ans[i]] << "  " << quantity[i] << endl;
    }
    cout << endl;
    cout << "Profit is : " << profitt << endl;
    cout << "Weight is : " << weighttt << endl;
}
