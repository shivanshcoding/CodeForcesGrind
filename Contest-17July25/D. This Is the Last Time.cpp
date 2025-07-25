// #include <bits/stdc++.h>
// using namespace std;

// long long Ans(vector<vector<int>>& arr, int k, vector<int>& temp, int n){

//     long long ans = k;
//     for(int j=0;j<n;j++){
//         if(temp[j]==0 && arr[j][0] <= k and arr[j][1] >= k){
//             temp[j]=1;
//             ans = max(ans,Ans(arr,arr[j][2],temp,n));
//             temp[j] = 0;
//         }
//     }
//     return ans;
// }

// int main() {
//     int t; cin >> t;
//     while(t--) {
//         int n;
//         long long k;
//         cin >> n >> k;
//         vector<vector<int>> arr(n, vector<int> (3));
//         for(int i=0;i<n;i++){
//             cin>>arr[i][0]>>arr[i][1]>>arr[i][2];
//         }
//         vector<int> temp(n,0);
//         cout<<Ans(arr,k,temp,n);
//         cout<<endl;
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k;
        cin >> n >> k;

        vector<tuple<int, int, int>> casinos(n);
        for (int i = 0; i < n; ++i) {
            int l, r, real;
            cin >> l >> r >> real;
            casinos[i] = {l, r, real};
        }

        // Sort casinos by li
        sort(casinos.begin(), casinos.end());

        priority_queue<int> pq;
        int i = 0;

        while (true) {
            // Add all new casinos where li <= k <= ri
            while (i < n && get<0>(casinos[i]) <= k) {
                int l = get<0>(casinos[i]);
                int r = get<1>(casinos[i]);
                int real = get<2>(casinos[i]);
                if (k <= r) {
                    pq.push(real);
                }
                ++i; // Only move forward once
            }

            if (pq.empty()) break;

            k = pq.top();
            pq.pop();
        }

        cout << k << '\n';
    }

    return 0;
}


