#include <bits/stdc++.h>
 
using namespace std;
 
const int NMAX = 3000;
const int modulo = 1e9 + 7;
 
void addSelf(int &x, int y)
{
    x += y;
    if (x >= modulo)
        x -= modulo;
}
 
int add(int x, int y)
{
    addSelf(x, y);
    return x;
}
 
int n, a[NMAX + 5], b[NMAX + 5];///b -> initial array, a -> equivalent permutation
int bit_lin[NMAX + 5][NMAX + 5], bit_col[NMAX + 5][NMAX + 5];///will use an offset of one because of [0..n] range
 
void update_lin(int lin, int pos, int val)
{
    pos++;
    for (int i = pos; i <= n + 1; i += (i & -i))
        addSelf(bit_lin[lin][i], val);
}
 
void update_col(int col, int pos, int val)
{
    pos++;
    for (int i = pos; i <= n + 1; i += (i & -i))
        addSelf(bit_col[col][i], val);
}
 
int query_lin(int lin, int pos)
{
    pos++;
    int rr = 0;
    for (int i = pos; i > 0; i -= (i & -i))
        addSelf(rr, bit_lin[lin][i]);
    return rr;
}
 
int query_col(int col, int pos)
{
    pos++;
    int rr = 0;
    for (int i = pos; i > 0; i -= (i & -i))
        addSelf(rr, bit_col[col][i]);
    return rr;
}
 
void testcase()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
    {
        a[i] = 1;
        for (int j = 1; j < i; j++)
            if (b[j] <= b[i])
                a[i]++;
        for (int j = i + 1; j <= n; j++)
            if (b[j] < b[i])
                a[i]++;
    }
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= n + 1; j++)
            bit_lin[i][j] = bit_col[i][j] = 0;
    update_lin(0, 0, 1);
    update_col(0, 0, 1);
    for (int i = 1; i <= n; i++)
    {
        vector<pair<int, pair<int, int>>> buffs;///where to update at the end
        int x = a[i];
        for (int j = x + 1; j <= n; j++)
        {
            int lin, col, buff;
            lin = j;
            col = x;
            buff = query_lin(j, x - 1);
            buffs.push_back({buff, {lin, col}});
        }
        for (int q = 0; q < x; q++)
        {
            int lin, col, buff;
            lin = x;
            col = q;
            buff = query_col(q, x - 1);
            buffs.push_back({buff, {lin, col}});
        }
        for (auto it : buffs)
        {
            update_lin(it.second.first, it.second.second, it.first);
            update_col(it.second.second, it.second.first, it.first);
        }
    }
    int ans = 0;
    for (int lin = 0; lin <= n; lin++)
        addSelf(ans, query_lin(lin, n));
    cout << ans << '\n';
}
 
int main()
{
    int tc;
    cin >> tc;
    while (tc--)
        testcase();
    return 0;
}