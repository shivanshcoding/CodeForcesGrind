//Written By Aryan Sanghi
 
#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
const int mod=1e9+7;
 
int modpower(int a, int b)
{
    int r=1;
    
    a=a%mod;
    while(b>0)
    {
        if(b%2==1)
        {
            r*=a;
            r%=mod;
        }
        
        b=b/2;
        a*=a;
        a%=mod;
        
    }
    
    return r;
}
 
 
int32_t main(){
    int t;
    cin>>t;
 
    while(t--){
        int a, b, k;
        cin>>a>>b>>k;
        
        int n=1, m=1;
        
        n*=a-1;
        n%=mod;
        n*=k;
        n%=mod;
        n+=1;
        n%=mod;
        
        m*=b-1;
        m%=mod;
        m*=k;
        m%=mod;
        for(int i=0;i<a;i++){
            m*=(n-i+mod)%mod;
            m%=mod;
            m*=modpower((a-i+mod)%mod, mod-2)%mod;
            m%=mod;
        }
        m+=1;
        m%=mod;
        
        cout<<n<<" "<<m<<"\n";
    }
}