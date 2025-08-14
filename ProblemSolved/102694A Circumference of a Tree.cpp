#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> subans;
#define print(x) for(auto& c: x) cout<<c<<" "; cout<<endl;

void dfs(vector<vector<int>>& adj, int i, int p){
    for(int k: adj[i]){
        if(k==p) continue;
        dfs(adj,k,i);
        subans[i] = max(subans[i], 1 + subans[k]);
    }
}

void dp(vector<vector<int>>& adj, ll& ans, int i, int p, ll p_ans){
    ll currmax = -1, curr2ndmax = -1;
    for(int k: adj[i]){
        if(k==p) continue;
        if(subans[k] > currmax){
            curr2ndmax = currmax;
            currmax = subans[k];
        }else if(subans[k] > curr2ndmax){
            curr2ndmax = subans[k];
        }
    }
    ans = max(ans,2+currmax+curr2ndmax);
    ans = max(ans,1+currmax+p_ans);
    for(int k: adj[i]){
        if(k==p) continue;
        if(subans[k]==currmax){
            dp(adj,ans,k,i,max(1+curr2ndmax,1+p_ans));
        }else{
            dp(adj,ans,k,i,max(1+currmax,1+p_ans));
        }
    }
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> adj(n);
    subans.assign(n,0);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(adj,0,-1);
    ll ans = 0;
    dp(adj,ans,0,-1,0);
    cout<<ans*3;
    return 0;
}