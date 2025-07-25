#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int l,r;
        cin>>l>>r;
        if(l*2 <= r){
            cout<<l<<" "<<2*l;
        }else{
            cout<<"-1 -1";
        }
        cout<<endl;
    }
    return 0;
}