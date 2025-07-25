#include<bits/stdc++.h>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>> t;
    while(t--){
        string k;
        cin>>k;
        k.pop_back();
        k.pop_back();
        k.push_back('i');
        cout<<k;
        cout<<endl;
    }
    return 0;
}