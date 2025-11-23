#include <bits/stdc++.h>
using namespace std;


int main(){
    int t;
    cin >> t;
    while(t--){
      int n;
      cin>>n;
      unordered_map<int,int>mp;
      int ct = 0;
      for(int i=0;i<n;i++){
            int m;
            cin>>m;
            mp[m]++;
      }
      for(auto m : mp){
        if(m.second!=m.first){
             int f = m.first;
             int s = m.second;
             if(m.second>m.first)ct+=(s-f);
             else ct+=m.second;  
        } 
      }
      cout<<ct<<'\n';
    }
}