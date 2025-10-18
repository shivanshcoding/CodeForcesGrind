#include<bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
const int N = 1000043;
 
int add(int x, int y)
{
    x += y;
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
    return x;
}
 
int mul(int x, int y)
{
    return (x * 1ll * y) % MOD;
}   
 
int binpow(int x, int y)
{
    int z = 1;
    while(y > 0)
    {
        if(y % 2 == 1) z = mul(z, x);
        x = mul(x, x);
        y /= 2;
    }
    return z;
}
 
vector<int> get(const vector<int>& a)
{
    int cur = -1;
    vector<int> res;
    for(auto x : a)
        if(x > cur)
        {
            res.push_back(x);
            cur = x;
        }
    return res;
}
 
struct SegTree
{
    vector<int> f;
    vector<int> t;
    int n;
 
    int getVal(int v, int pos)
    {
        return mul(t[pos], binpow(2, f[v]));
    }   
 
    void push(int v)
    {
        if(f[v] != 0)
        {
            f[2 * v + 1] += f[v];
            f[2 * v + 2] += f[v];
            f[v] = 0;
        }
    }
 
    void resolve(int v, int pos)
    {
        if(f[v] != 0)
        {
            t[pos] = mul(t[pos], binpow(2, f[v]));
            f[v] = 0;    
        }
    }
 
    int get(int v, int l, int r, int pos)
    {
        if(l == r - 1)
            return getVal(v, pos);
        else
        {
            push(v);
            int m = (l + r) / 2;
            if(pos < m)
                return get(v * 2 + 1, l, m, pos);
            else
                return get(v * 2 + 2, m, r, pos);
        }
    }
 
    int get(int pos)
    {
        return get(0, 0, n, pos);
    }
 
    void inc(int v, int l, int r, int pos, int val)
    {
        if(l == r - 1)
        {
            resolve(v, pos);
            t[pos] = add(t[pos], val);
        }
        else
        {
            push(v);
            int m = (l + r) / 2;
            if(pos < m)
                inc(v * 2 + 1, l, m, pos, val);
            else
                inc(v * 2 + 2, m, r, pos, val);
        }
    }
 
    void inc(int pos, int val)
    {
        return inc(0, 0, n, pos, val);
    }
 
    void mulBy2(int v, int l, int r, int L, int R)
    {
        if(L >= R) return;
        if(l == L && r == R)
            f[v]++;
        else
        {
            push(v);
            int m = (l + r) / 2;
            mulBy2(v * 2 + 1, l, m, L, min(R, m));
            mulBy2(v * 2 + 2, m, r, max(L, m), R);
        }
    }
 
    void mulBy2(int l, int r)
    {
        mulBy2(0, 0, n, l, r);   
    }
 
    SegTree(int n = 0)
    {
        this->n = n;
        f.resize(4 * n);
        t.resize(n);
    }
};
 
vector<int> calc(const vector<int>& a, const vector<int>& b)
{
    int n = a.size();
    int m = b.size();
    SegTree tree(m + 1);
    tree.inc(0, 1);
    vector<int> res(n);
    int maxVal = b.back();
    for(int i = 0; i < n; i++)
    {
        int x = a[i];
        if(x > maxVal) continue;
        else
        {
            if (x == maxVal) res[i] = tree.get(m - 1);
            int lf = lower_bound(b.begin(), b.end(), x) - b.begin();
            tree.mulBy2(lf + 1, m + 1);
            if(b[lf] == x)
            {
                int cur = tree.get(lf);
                tree.inc(lf + 1, cur);
            }
        }
    }
    return res; 
}   
 
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    auto left_view = get(a);
    reverse(a.begin(), a.end());
    auto right_view = get(a);
    reverse(a.begin(), a.end());
 
    auto dpL = calc(a, left_view);
    reverse(a.begin(), a.end());
    auto dpR = calc(a, right_view);
    reverse(a.begin(), a.end());
    reverse(dpR.begin(), dpR.end());
 
    int maxVal = *max_element(a.begin(), a.end());
    int ans = 0;
    int sumLeft = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] > maxVal) continue;
        else
        {   
            if(a[i] == maxVal) ans = add(ans, mul(add(sumLeft, dpL[i]), dpR[i]));
            sumLeft = mul(sumLeft, 2);
            if(a[i] == maxVal) sumLeft = add(sumLeft, dpL[i]);
        }
    }
    cout << ans << endl;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);    
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) solve();
}