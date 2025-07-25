#include<bits/stdc++.h>
using namespace std;

int main(){
    long long n, k,l,c,d,p,nl,np;
    cin>>n>>k>>l>>c>>d>>p>>nl>>np;
    long long tl = k*l;
    long long ts = c*d;
    long long ans = min(tl/nl,min(ts,p/np));
    ans = ans/n;
    cout<<ans;
    return 0;
}