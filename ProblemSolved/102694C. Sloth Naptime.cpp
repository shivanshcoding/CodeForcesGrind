#include<bits/stdc++.h>
using namespace std;


#include<bits/stdc++.h>
using namespace std;
 
int n, q;
vector<vector<int>> up(300001, vector<int>(20,-1));
vector<int> lvl;
 
void dfs(int i, int p, int l){
    lvl[i] = l;
    for(int k: adj[i]){
        if(k==p) continue;
        dfs(k,i,l+1);
    }
}
 
void binarylifting(int i, int p){
    up[i][0] = p;
    for(int j=1;j<20;j++){
        if(up[i][j-1]!=-1){
            up[i][j] = up[up[i][j-1]][j-1];
        }else{
            up[i][j] = -1;
        }
    }
    for(int k: adj[i]){
        if(k==p) continue;
        binarylifting(k,i);
    }
}
 
int GoUp(int i, int k){
    int count = 0;
    int ans = i;
    while(k!=0 and ans!=-1){
        if((k&1)==1){
            ans = up[ans][count];
        }
        k  = k>>1;
        count++;
    }
    return ans;
}
 
int Ans(int a, int b){
    if(lvl[a] < lvl[b]){
        swap(a,b);
    }
    a = GoUp(a,lvl[a]-lvl[b]);
    if(a==b){
        return a;
    }
    for(int i=19;i>=0;i--){
        if(up[a][i]!=up[b][i]){
            a = up[a][i];
            b = up[b][i];
        }
    }
    return GoUp(a,1);
}


vector<vector<int>> adj;

int solve(int& a, int& b, int& c){
    int ans = Ans(a,b);
    if(ans <= c){
        return b;
    }else{
        if(c <= lvl[])
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    adj.resize(n+1);
    lvl.assign(n+1,0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,-1,1);
    binarylifting(1,-1);
    int q;
    cin>>q;
    while(q--){
        int a, int b, int c;
        cin>>a>>b>>c;
        cout<<solve(a,b,c);
    }
    return 0;
}