#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int> v;
    string k;
    cin>>k;
    int n = k.size();
    for(int i=0;i<n;i++){
        if(k[i]!='+'){
            v.push_back(k[i]-'0');
        }
    }
    sort(v.begin(),v.end());
    for(int i=n-1;i>=0;i--){
        if(k[i]=='+') continue;
        else{
            k[i] = v.back() + '0';
            v.pop_back();
        }
    }
    cout<<k;
    return 0;
}