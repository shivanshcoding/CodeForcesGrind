#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        cout<<endl;
    }
    return 0;
}