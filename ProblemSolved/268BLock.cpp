#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int ans = 0;
    for(int i=n;i>0;i--){
        ans += (i-1)*(n-i) + i;
    }
    cout<<ans;
    return 0;
}