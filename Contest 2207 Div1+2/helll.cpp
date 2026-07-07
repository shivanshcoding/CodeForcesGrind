#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> deg(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }

    vector<bitset<4005>> dp(n + 1);
    
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        int d = deg[i];
        for (int x = i; x >= 1; x--) {
            dp[x] |= (dp[x - 1] << d);
        }
    }

    long long ans = 0;
    for (int x = 0; x <= n; x++) {
        ans += dp[x].count(); 
    }

    cout << ans << "\n";
    return 0;
}