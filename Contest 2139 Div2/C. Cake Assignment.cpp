#include <bits/stdc++.h> 
using namespace std;
int main(){
    int t; cin>>t;
    while(t--){
        long long k,x,kk; cin>>k>>x; kk=1ll<<k;
        if (!x||x==kk*2) {cout<<"-1\n"; continue;}
        long long y=kk*2-x;
        vector<int> ans; ans.clear();
        while(x!=kk){
            if (x>y) ans.push_back(2),x-=y,y*=2;
            else ans.push_back(1),y-=x,x*=2;
        }
        cout<<ans.size()<<"\n";
        while(!ans.empty()) cout<<ans.back()<<' ',ans.pop_back();
        cout<<"\n";
    }
    return 0;
}