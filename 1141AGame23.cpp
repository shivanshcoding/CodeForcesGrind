#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    if(m%n!=0){
        cout<<-1;
    }else{
        int k = m/n;
        int ans = 0;
        while(k%3==0){
            k = k/3;
            ans++;
        }
        while(k%2==0){
            k = k/2;
            ans++;
        }
        if(k!=1){
            cout<<-1;
        }else{
            cout<<ans;
        }
    }
    return 0;
}