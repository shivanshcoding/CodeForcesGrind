#include "bits/stdc++.h"
using namespace std;

const int MAXN = 200005;
const int INF = 1000000005;

inline int fdiv(int num, int denom)
{
    return num / denom - ((num ^ denom) < 0 && num % denom);
}
inline int cdiv(int num, int denom) { return fdiv(num + denom - 1, denom); }

int t;
int n;
int a[MAXN];

vector<int> adj[MAXN];
void add_edge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
bool check(int x)
{
    for (int i = 1; i <= n; i++)
    {
        adj[i].clear();
    }
    set<pair<int, int>> st;
    for (int i = 1; i <= n; i++)
    {
        int cnt = 0;
        for (auto [prv, prv_id] : st)
        {
            if (a[i] - prv >= x)
            {
                add_edge(prv_id, i);
            }
        }
        st.insert({a[i], i});
        if ((int)st.size() > 3)
        {
            st.erase(prev(st.end()));
        }
    }

    int bad_cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if ((int)adj[i].size() >= 2)
        {
            bad_cnt++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int delta = (int)adj[i].size() >= 2;
        for (int v : adj[i])
        {
            if (adj[v].size() == 2)
            {
                delta++;
            }
        }
        if (delta == bad_cnt)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        int lo = -INF, hi = INF;
        while (lo < hi)
        {
            int mid = cdiv(lo + hi, 2);
            if (check(mid))
            {
                lo = mid;
            }
            else
            {
                hi = mid - 1;
            }
        }
        cout << lo << '\n';
    }
    return 0;
}