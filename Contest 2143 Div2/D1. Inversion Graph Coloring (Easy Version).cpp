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
int dp[2][NMAX + 1][NMAX + 1];///considering elements 1..i, the biggest value is j, and the biggest value preceeded by a bigger one is q
 
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
    for (int i = 0; i < 2; i++)
        for (int j = 0; j <= n; j++)
            for (int q = 0; q <= n; q++)
                dp[i][j][q] = 0;
    dp[0][0][0] = 1;
    int cr = 0;
    for (int i = 1; i <= n; i++)
    {
        cr ^= 1;
        int x = a[i];
        for (int j = 0; j <= n; j++)
            for (int q = 0; q <= n; q++)
                dp[cr][j][q] = dp[cr ^ 1][j][q];
        for (int j = 0; j <= n; j++)
        {
            for (int q = 0; q <= j; q++)
            {
                if (dp[cr ^ 1][j][q] == 0)
                    continue;
                if (j > x and x > q)
                    addSelf(dp[cr][j][x], dp[cr ^ 1][j][q]);
                else if (x > j)
                    addSelf(dp[cr][x][q], dp[cr ^ 1][j][q]);
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= n; j++)
    {
        for (int q = 0; q <= n; q++)
            addSelf(ans, dp[cr][j][q]);
    }
    cout << ans << '\n';///empty subsequence inclusive
}
 
int main()
{
    int tc;
    cin >> tc;
    while (tc--)
        testcase();
    return 0;
}