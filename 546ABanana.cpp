#include<bits/stdc++.h>
using namespace std;
int main(){
    int k,n,w;
    cin>>k>>n>>w;
    long long sum = 0;
    for(int i=1;i<=w;i++){
        sum += i*k;
    }
    cout<<max((int)(sum-n),0);
    return 0;
}