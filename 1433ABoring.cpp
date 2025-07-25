#include<bits/stdc++.h>
using namespace std;

unordered_map<string,int> mpp;

int main(){
    int t;
    cin>> t;
    while(t--){
        string x;
        cin>>x;
        int n = x.size();
        if(mpp.find(x)==mpp.end()){
            int ans = 0;
            ans += (x[0]-'1')*10;
            ans += (n*(n+1))/2;
            mpp[x] = ans;
        }
        cout<<mpp[x]<<endl;
    }
    return 0;
}