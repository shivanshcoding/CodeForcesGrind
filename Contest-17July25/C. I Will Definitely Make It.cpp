#include<bits/stdc++.h>
using namespace std;

bool Ans(int n, int k, vector<int>& h){
    int prev = h[k-1];
    sort(h.begin(),h.end());
    int i=0;
    while(i<n and h[i]<=prev){
        i++;
    }
    int wl = 1;
    while(i<n){
        if(h[i]-prev > prev+1-wl) return false;
        wl+=h[i]-prev;
        prev = h[i];
        i++;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n, k;
        cin>>n>>k;
        vector<int> h(n);
        for(int i=0;i<n;i++) cin>>h[i];
        if(Ans(n,k,h)){
            cout<<"YES";
        }else{
            cout<<"NO";
        }
        cout<<endl;
    }
    return 0;
}