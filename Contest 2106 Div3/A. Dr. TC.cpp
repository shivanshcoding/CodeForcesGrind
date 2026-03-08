#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>> t;
    while(t--){
        int n;
        cin>> n;
        string s;
        cin>> s;
        int count = 0, ans =0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1'){
                count++;
            }
        }
        for(int i = 0; i < n; i++){
            if(s[i] == '0'){
                ans += count+1;
            } else {
                ans += count-1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}