#include<bits/stdc++.h>
using namespace std;



int main(){
    int n, m;
    cin>>n>>m;
    int s = n%2==0? n/2 : (n+1)/2;
    int e = n;
    for(int i=s;i<=e;i++){
        if(i%m==0){
            cout<<i;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}