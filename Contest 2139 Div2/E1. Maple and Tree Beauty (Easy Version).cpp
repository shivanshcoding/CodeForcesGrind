// n^2/w
#include <bits/stdc++.h>
using namespace std;
int solve() {
    int n, k;
    cin >> n >> k;
    vector<int> fa(n, -1), dep(n, 0);
    vector<int> noson(n, 1), cnt(n + 1);
    cnt[0]++;
    for (int i = 1; i < n; i++) {
        cin >> fa[i], fa[i]--;
        dep[i] = dep[fa[i]] + 1;
        cnt[dep[i]]++;
        noson[fa[i]] = 0;
    }
    int mxdep = 1e9;
    for (int i = 0; i < n; i++)
        if (noson[i]) mxdep = min(mxdep, dep[i]);
 
    int sum = 0;
 
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i <= mxdep; i++) {
        for (int j = sum; j >= 0; j--) dp[j + cnt[i]] |= dp[j];
        sum += cnt[i];
    }
    if (sum <= k || sum <= n - k) return mxdep + 1;
    for (int i = 0; i <= sum; i++)
        if (dp[i]) {
            if (i <= k && sum - i <= n - k) return mxdep + 1;
        }
    return mxdep;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) cout << solve() << "\n";
    return 0;
}