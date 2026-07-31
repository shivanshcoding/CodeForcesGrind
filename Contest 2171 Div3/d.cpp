#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define vi vector<ll>
#define py cout<<"YES"<<endl
#define pn cout<<"NO"<<endl
#define mod (ll)1e9

void input(vi &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        ll j;
        cin >> j;
        arr.push_back(j);
    }
}

void print(vi &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}


void prime(vi &v){
vector<bool>prime(1e7,1);
    prime[1]=0;
    prime[0]=0;
    for(ll i=2;i<1e7;i++){
        if(prime[i]){
        for(ll j=i*i;j<1e7;j+=i){
            prime[j]=0;
        }
    }
}
    for(int i=2 ;i<1e7;i++){
        if(prime[i])
        v.push_back(i);
    }
}

ll power(ll base, ll exponent)
{
    ll result = 1;
    base %= mod;
    while (exponent > 0)
    {
        if (exponent & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

void dijkstra(vector<vector<pair<ll, ll>>> &arr, vector<ll> &dist, ll src, vector<bool> &vis)
{
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({0, src});
    dist[src] = 0;
    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();
        ll node = it.second;
        ll dis = it.first;
        if (vis[node])
            continue;
        vis[node] = true;
        for (auto i : arr[node])
        {
            if (dis + i.second < dist[i.first] && !vis[i.first])
            {
                dist[i.first] = dis + i.second;
                pq.push({dist[i.first], i.first});
            }
        }
    }
}



void solve()
{
    ll n;
    cin>>n;
    vi v;
    input(v,n);
    set<ll>s;
    for(int i=0 ;i<n;i++){
        if(!s.size()||*s.begin()>v[i]){
            s.insert(v[i]);
        }
    }

    for(int i = n-1 ;i>=0 ;i--){
        ll p = 0;
        if(v[i]==*s.begin()){
            pn;
            return;
        }
        while(s.size()&&*s.begin()<v[i]){
            p = *s.begin();
            s.erase(*s.begin());
            // cout<<"p"<<p<<" ";
        }
        // cout<<endl;
        if(s.size()==0){
            py;
            return;
        }
        if(p!=0){
            s.insert(p);
        }
    }
    pn;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {

        solve();
    }
    return 0;
}