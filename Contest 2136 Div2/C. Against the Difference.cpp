
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

int n;
vector<int> arr;
vector<vector<pii>> blocks;
vector<int> memo;

int dfs(int i) {
    if (i >= n) return 0;
    int &res = memo[i];
    if (res != -1) return res;
    res = dfs(i+1); // skip
    for (auto [r, w] : blocks[i]) {
        res = max(res, w + dfs(r+1));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        cin >> n;
        arr.assign(n, 0);
        for (int i=0;i<n;i++) cin >> arr[i];

        // collect positions
        vector<vector<int>> occ(n+1);
        for (int i=0;i<n;i++) if (arr[i] <= n) occ[arr[i]].push_back(i);

        blocks.assign(n+1, {});
        for (int val=1; val<=n; val++) {
            auto &idx = occ[val];
            if ((int)idx.size() < val) continue;
            for (int j=0; j+val-1 < (int)idx.size(); j++) {
                blocks[idx[j]].push_back({idx[j+val-1], val});
            }
        }

        memo.assign(n+1, -1);
        cout << dfs(0) << "\n";
    }
}
