#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int MAXN = 250000;

int a[MAXN + 100];
ll prf[MAXN + 100][4];

void solve(){
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i=1;i<=n;i++) scanf("%d", a+i);
    
    for (int i=1;i<=n;i++){
        for (int j=0;j<3;j++) prf[i][j] = prf[i-1][j];
        
        int typ = 2;
        if (popcount((unsigned)a[i]) == 1) typ = 0;
        else if (popcount((unsigned)a[i]-1) == 1) typ = 1;

        prf[i][typ]++;

        prf[i][3] = prf[i-1][3] + (31 - countl_zero((unsigned)a[i]));
    }

    while(q--){
        int l, r;
        scanf("%d %d", &l, &r);

        ll cnt[3] = {0};
        for (int j=0;j<3;j++) cnt[j] = prf[r][j] - prf[l-1][j];

        ll ans = prf[r][3] - prf[l-1][3] + cnt[2] + cnt[1] / 2;
        printf("%lld\n", ans);
    }
}

int main(){
    int t;
    scanf("%d", &t);

    while(t--) solve();
}