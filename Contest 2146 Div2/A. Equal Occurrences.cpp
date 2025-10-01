#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        long long n, m , r, c;
        cin>>n>>m>>r>>c;
        cout<<m*(n-r)+n*m-((r-1)*m+c)-(n-r)<<"\n";
    }
    return 0;
}