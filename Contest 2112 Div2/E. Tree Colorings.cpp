#include<bits/stdc++.h>

using namespace std;

const int N = 500043;

vector<int> divisors[N];

int dp[N], dp2[N];

int calc(int x);

int calc2(int x)
{
    if(dp2[x] != -1) return dp2[x];
    if(x == 1) return dp2[x] = 0;
    dp2[x] = calc(x);
    for(auto y : divisors[x]) dp2[x] = min(dp2[x], calc(y) + calc2(x / y));
    return dp2[x];
}

int calc(int x)
{
    if(dp[x] != -1) return dp[x];
    if(x == 1) return dp[x] = 0;
    if(x == 3) return dp[x] = 1;
    return dp[x] = calc2(x - 2) + 1;
}                       

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 2; i < N; i++)
        for(int j = i * 2; j < N; j += i)
            divisors[j].push_back(i);
    for(int i = 0; i < N; i++) dp[i] = dp2[i] = -1;

    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        int x;
        cin >> x;
        if(x % 2 == 0) cout << -1 << endl;
        else cout << calc(x + 2) << endl;
    }
    return 0;
}