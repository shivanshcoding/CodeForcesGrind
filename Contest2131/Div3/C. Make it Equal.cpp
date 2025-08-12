#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(a) (a).begin(), (a).end()
#define endl "\n"
#define vec vector
#define pii pair<int, int>
#define se second
#define fi first
#define pb push_back
#define maxel(v) *max_element(v.begin(), v.end())
#define minel(v) *min_element(v.begin(), v.end())
#define yes cout << "YES\n";
#define m1 cout << "-1\n";
#define no cout << "NO\n";

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    if (!(cin >> tt))
        return 0;
    while (tt--)
    {
        int n;
        ll k;
        cin >> n >> k;
        vec<ll> s(n), t(n);
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> t[i];
        }
        if (k == 0)
        {
            sort(all(s));
            sort(all(t));
            if (s == t)
                yes else no continue;
        }
        unordered_map<ll, int> cnt;
        // cnt.reserve(n * 2);
        for (auto &x : s)
        {
            ll r = x % k;
            // if (r < 0)
            //     r += k;
            ll nr = min(r, k - r);
            cnt[nr]++;
        }
        for(auto& curr: cnt){
            cout<<curr.first<<" : "<<curr.second<<endl;
        }
        for (auto &x : t)
        {
            ll r = x % k;
            // if (r < 0)
            //     r += k;
            ll nr = min(r, k - r);
            cnt[nr]--;
        }
        for(auto& curr: cnt){
            cout<<curr.first<<" : "<<curr.second<<endl;
        }
        bool ok = true;
        for (auto &p : cnt)
            if (p.second != 0)
            {
                ok = false;
                break;
            }
        if (ok)
            yes else no
    }
    return 0;
}