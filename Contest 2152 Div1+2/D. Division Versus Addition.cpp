#include <bits/stdc++.h>
using namespace std;

struct D {
    int n;
    vector<int> p, x;
    D(int n=0): n(n), p(n), x(n,0) { for(int i=0;i<n;++i) p[i]=i; }
    pair<int,int> f(int a){
        if(p[a]==a) return {a,0};
        auto r = f(p[a]);
        p[a] = r.first;
        x[a] ^= r.second;
        return {p[a], x[a]};
    }
    bool u(int a,int b,int w){
        auto pa = f(a);
        auto pb = f(b);
        int ra = pa.first, rb = pb.first;
        int xa = pa.second, xb = pb.second;
        if(ra==rb) return ((xa ^ xb) == w);
        p[ra] = rb;
        x[ra] = xa ^ xb ^ w;
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if(!(cin >> t)) return 0;
    while(t--){
        int n; cin >> n;
        string s; cin >> s;
        vector<int> a(n, -1);
        vector<int> z;
        for(int i=0;i<n;++i) if(s[i]=='0'){ a[i] = (int)z.size(); z.push_back(i); }
        int m = (int)z.size();
        D d(m+1);
        bool ok = true;
        int S = m;
        for(int j=0;j<n && ok;++j){
            if(s[j]=='1'){
                int l = (j-1>=0 && s[j-1]=='0') ? a[j-1] : -1;
                int r = (j+1<n  && s[j+1]=='0') ? a[j+1] : -1;
                if(l!=-1 && r!=-1){
                    if(!d.u(l, r, 1)) ok = false;
                } else if(l!=-1){
                    if(!d.u(l, S, 0)) ok = false;
                } else if(r!=-1){
                    if(!d.u(r, S, 1)) ok = false;
                }
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}