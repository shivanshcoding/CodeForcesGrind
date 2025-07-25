#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int sum = 0;
    int ans =0;
    while(sum<=n){
        sum += ((ans+1)*(ans+2))/2;
        ans++;
    }
    cout<<ans-1;
    return 0;
}