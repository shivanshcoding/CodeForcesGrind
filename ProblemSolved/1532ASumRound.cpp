#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>> t;
    while(t--){
        string k;
        cin>>k;
        reverse(k.begin(),k.end());
        int n = k.size();
        int ans = 0;
        for (int i = 0; i < n; i++){
            if(k[i]!='0'){
                ans++;
            }
        }
        cout<<ans<<endl;
        for (int i = 0; i < n; i++){
            if(k[i]=='0') continue;
            cout<<(k[i]-'0')*pow(10,i)<<" ";
        }
        cout<<endl;
    }
    return 0;
}