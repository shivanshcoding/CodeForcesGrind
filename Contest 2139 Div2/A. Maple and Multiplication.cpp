#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int solve(){
    int a,b;
    cin >> a >> b;
    if(a == b) return 0;
    if(a % b == 0 || b % a == 0) return 1;
    return 2;
}
 
int main(){
    ios::sync_with_stdio(false);
    int TC;
    cin >> TC;
    while(TC --){
        cout << solve() << '\n';
    }
    return 0;
}