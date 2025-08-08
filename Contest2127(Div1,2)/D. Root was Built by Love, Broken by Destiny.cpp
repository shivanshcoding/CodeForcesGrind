#include<bits/stdc++.h>
using namespace std;
// int MOD = 1e9 + 7;

// typedef long long ll;


// ll fact(int n) {
//     ll res = 1;
//     for (int i = 2; i <= n; i++) {
//         res = (res * i) % MOD;
//     }
//     return res;
// }

// bool isCyclic(vector<vector<int>>& adj, int n) {
//     vector<bool> visited(n, false);
    
//     for (int start = 0; start < n; ++start) {
//         if (!visited[start]) {
//             queue<pair<int, int>> q;
//             q.push({start, -1});
//             visited[start] = true;

//             while (!q.empty()) {
//                 int node = q.front().first;
//                 int parent = q.front().second;
//                 q.pop();

//                 for (int neighbor : adj[node]) {
//                     if (!visited[neighbor]) {
//                         visited[neighbor] = true;
//                         q.push({neighbor, node});
//                     } else if (neighbor != parent) {
//                         return true; // Found a back edge => cycle
//                     }
//                 }
//             }
//         }
//     }

//     return false;
// }


// ll solve(vector<vector<int>>& adj, int n, vector<int>& deg) {
//     ll ans = 1;
//     for(int i = 0; i < n; i++) {
//         if(deg[i]==1) continue;
//         int count =0, non = 0;
//         for(int k: adj[i]){
//             if(deg[k] <= 1) {
//                 non++;
//             } else {
//                 count++;
//                 if(count>2){
//                     return 0;
//                 }
//             }
//         }
//         if(count == 0) {
//             ans *= fact(non)%MOD;
//         } else if(count == 1) {
//             if(non > 0) {
//                 ans*= (2*fact(non))%MOD; // No valid configuration if only one neighbor has degree > 1
//             }
//         } else {
//             ans *= (2 * fact(non))%MOD;
//         }
//     }
//     return 2*ans%MOD;
// }

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int t;
//     cin>> t;
//     while(t--){
//         int n, m;
//         cin >> n >> m;
//         vector<vector<int>> adj(n);
//         vector<int> deg(n, 0);
//         for(int i = 0; i < m; i++){
//             int u, v;
//             cin >> u >> v;
//             u--; v--;
//             adj[u].push_back(v);
//             adj[v].push_back(u);
//             deg[u]++;
//             deg[v]++;
//         }
//         if(isCyclic(adj,n)){
//             cout<<0<<endl;
//             continue;
//         }
//         cout<<solve(adj, n,deg);
//         cout<<endl;
//     }
//     return 0;
// }


#define SZ(x) int(x.size())

const int  MOD    = 1e9  + 7;
const int MXN    = 2e5  + 5;

int n, m, fact[MXN];
vector<int> adj[MXN];

int32_t main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    fact[0] = 1;
    for (int i = 1; i < MXN; i++) 
        fact[i] = (1ll * fact[i-1] * i) % MOD;
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        long long ans = 2;
        int tl = 0;
        if (m >= n) ans = 0;
        for (int u = 1; u <= n; u++) {
            if (adj[u].size() > 1) {
                int x = 0;
                for (int v : adj[u]) {
                    x += (SZ(adj[v]) == 1);
                }
                if (x >= SZ(adj[u]) - 2) (ans *= fact[x]) %= MOD;
                else ans = 0;
            } else tl ++;
        }
        if (tl < n-1) tl = 2; else tl = 1;
        cout << (ans * tl % MOD) << '\n';
    }
    return 0;
}