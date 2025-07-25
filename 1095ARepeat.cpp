#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,i =0;
    cin>>n;
    string k;
    cin>>k;
    string ans;
    while(i<n){
        ans.push_back(k[i]);
        i += ans.size();
    }
    cout<<ans;
    return 0;
}