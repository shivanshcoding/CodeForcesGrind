#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> v(n,0);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    long long ans = 0;
    int prev = 1e9+1;
    for(int i = n-1; i>=0;i--){
        ans += min(v[i],prev);
        prev = min(v[i],prev)-1;
        if(prev<=0) break;
    }
    cout<<ans;
    return 0;
}