#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
 
        vector<int> lengths(n);
        vector<vector<int>> arrays(n);
        map<int, int> count;
        for (int i = 0; i < n; i++) {
            int length;
            cin >> length;
            lengths[i] = length;
            arrays[i] = vector<int>(lengths[i]);
            for (auto &x: arrays[i]) {
                cin >> x;
                count[x]++;
            }
            sort(arrays[i].begin(), arrays[i].end());
        }
 
        int mex_sum = 0;
        vector<int> mexes(n);
        vector<int> second_mexes(n);
 
        // Calculate mex and second mex for each array
        for (int i = 0; i < n; i++) {
            int current_mex = 0;
            for (int j = 0; j < lengths[i]; j++) {
                if (arrays[i][j] > current_mex) break;
                if (arrays[i][j] == current_mex) current_mex++;
            }
            int second_mex = current_mex+1;
            for (int j = 0; j < lengths[i]; j++) {
                if (arrays[i][j] > second_mex) break;
                if (arrays[i][j] == second_mex) second_mex++;
            }
            mexes[i] = current_mex;
            second_mexes[i] = second_mex;
            mex_sum += current_mex;
        }
 
        ll total = 0;
        // Calculate removals
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < lengths[i]; j++) {
                ll org = total;
                bool is_alone = (j == 0 || arrays[i][j-1] != arrays[i][j]) && (j == lengths[i]-1 || arrays[i][j+1] != arrays[i][j]);
                if (is_alone && arrays[i][j] < mexes[i]) total += ((ll)(mex_sum-mexes[i]+arrays[i][j]))*(n-1);
                else total += (ll)(mex_sum) * (n-1);
            }
        }
        // Calculate additions
        for (int i = 0; i < n; i++) {
            total += (ll)(count[mexes[i]])*(second_mexes[i]-mexes[i]);
        }
 
        cout << total << "\n";
    }
}