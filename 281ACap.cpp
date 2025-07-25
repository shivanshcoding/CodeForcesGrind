#include<bits/stdc++.h>
using namespace std;

int main{
    string k;
    cin>>k;
    if(k[0]>90){
        k[0] = k[0]-32;
    }
    cout<<k;
    return 0;
}