#include<bits/stdc++.h>
using namespace std;

int Ans(int x){
    int ans = 10;
    while(x>0){
        int dig = x%10;
        ans = min(ans,dig);
        x = x/10;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n;
        cin>>n;
        cout<<Ans(n);
        cout<<endl;
    }
    return 0;
}