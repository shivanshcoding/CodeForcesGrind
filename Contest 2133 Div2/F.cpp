#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define all(x) x.begin(), x.end()
#define vecin(name, len) vector<int> name(len); for (auto &_ : name) cin >> _;
#define vecout(v) for (auto _ : v) cout << _ << " "; cout << endl;

const int INF = 1e9;

struct segtree {
    int n;
    vector<pair<int, int>> tree;
    segtree (int _n) {
        n = 1;
        while (n < _n)
            n *= 2;
        tree = vector<pair<int, int>>(2 * n, {INF, -1});
    }
    void upd(int i, pair<int, int> x) {
        i += n;
        tree[i] = min(tree[i], x);
        while (i > 1) {
            i /= 2;
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }
    pair<int, int> query(int left, int right, int index, int maxl, int maxr) {
        if (left == maxl && right == maxr) {
            return tree[index];
        }
        int mid = (maxl + maxr) / 2;
        pair<int, int> ans = {INF, -1};
        if (left <= mid)
            ans = min(ans, query(left, min(mid, right), 2 * index, maxl, mid));
        if (right > mid)
            ans = min(ans, query(max(left, mid + 1), right, 2 * index + 1, mid + 1, maxr));
        return ans;
    }
    pair<int, int> query(int left, int right) {return query(left, right, 1, 0, n - 1);}
};

struct update {
    int l; int r; int i;
};

void solve() {
    int n; cin >> n;
    vecin(aa, n);
    vector<vector<update>> upd(n + 1);
    for (int i = 0; i < n; i ++) {
        if (aa[i] == 0)
            continue;
        int left = max(0, i + 1 - aa[i]), right = min(n, i + aa[i] - 1);
        upd[i].push_back((update){left, i, i + 1});
        upd[left].push_back((update){left, right, i + 1});
    }
    vector<pair<int, int>> dp(n + 1, {INF, -1});
    dp[0] = {0, -1};
    segtree seg(n + 1);
    seg.upd(0, {1, -1});
    for (int i = 0; i <= n; i ++) {
        if (i > 0)
            seg.upd(min(n, i + aa[i - 1] - 1), {dp[i].first + 1, i});
        for (auto xx : upd[i])
            dp[xx.i] = min(dp[xx.i], seg.query(xx.l, xx.r));
    }
    if (seg.query(n, n).first == INF) {
        cout << -1 << endl; return;
    }
    vector<pair<int, int>> ans;
    int cur = seg.query(n, n).second;
    while (cur != -1) {
        ans.push_back({aa[cur - 1], cur});
        cur = dp[cur].second;
    }
    sort(all(ans));
    cout << ans.size() << endl;
    for (auto a : ans)
        cout << a.second << " ";
    cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tt = 1;

    cin >> tt;

    while (tt--) solve();
    return 0;
}