#include<bits/stdc++.h>
using namespace std;

vector<array<int,2>> reduce(string &s){
    int n = s.size();
    vector<array<int,2>> op;

    int p = -1; // position p such that two consecutive characters are same
    for(int i = 0;i < n-1;i++){
        if(s[i] == s[i+1])p = i;
    }
    if(p == -1){ // string is alternating
        op.push_back({0,2}); // substring of first three character must be palindrome
        s[0] ^= 1;s[1] ^= 1;
        p = 2;
    }

    char value = s[p+1];
    int L = p,R = p+1; // We maintain [L,R] such that all position in it have the same value

    while(R+1 < n){
        if(s[R+1] != value)op.push_back({L,R});
        R++;value = s[R];
    }

    while(L){
        if(s[L-1] != value)op.push_back({L,R});
        L--;value = s[L];
    }

    if(value == '1')op.push_back({0,n-1}); // We want to make all zeroes

    return op;
}

void solve(){
    int n;
    cin >> n;
    string s,t;
    cin >> s >> t;

    auto operation_s = reduce(s); // operations to reduce s to all zeroes
    auto operation_t = reduce(t); // operations to reduce t to all zeroes

    reverse(operation_t.begin(),operation_t.end());

    int moves = operation_s.size() + operation_t.size();
    cout << moves << "\n";
    for(auto &[x,y] : operation_s)cout << x+1 << " " << y+1 << "\n";
    for(auto &[x,y] : operation_t)cout << x+1 << " " << y+1 << "\n";

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}