#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>> t;
    while(t--){
        int n;
        cin>>n;
        int maxiloc = 0, miniloc = 0, maxi = 0, mini = n;
        for (int i = 1; i <= n; i++){
            int ch;
            cin>>ch;
            if(ch>maxi){
                maxiloc = i;
                maxi = ch;
            }
            if(ch<mini){
                miniloc = i;
                mini = ch;
            }
        }
        int ans = 0;
        int t1 = min(miniloc, n-miniloc+1);
        int t2 = min(maxiloc, n-maxiloc+1);
        if(t1>t2){
            ans += t2;
            ans += min(miniloc-t2,n-miniloc+1);
        }else{
            ans+= t1;
            ans += min(maxiloc-t1,n-maxiloc+1);
        }
        cout<<ans<<endl;
    }
    return 0;
}