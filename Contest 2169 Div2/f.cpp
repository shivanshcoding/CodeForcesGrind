#include <iostream>
#include <vector>
#include <map>

using namespace std;

long long n, m, k;
vector<int> l;
vector<vector<int>> a;
long long MOD = 998244353;

vector<vector<int>> beautiful_choices;
vector<int> current_choice;

// Recursively generate all L = l_1 * ... * l_k choice tuples (c_1, ..., c_k)
void generate_choices(int index) {
    if (index == k) {
        beautiful_choices.push_back(current_choice);
        return;
    }
    for (int i = 0; i < l[index]; ++i) {
        current_choice[index] = i;
        generate_choices(index + 1);
    }
}

// Helper function to get the actual beautiful array B(choice)
vector<int> get_beautiful_array(const vector<int>& choice) {
    vector<int> b(k);
    for (int i = 0; i < k; ++i) {
        b[i] = a[i][choice[i]];
    }
    return b;
}

// Calculate the next state P' = T(P, v)
vector<int> transition(const vector<int>& p, int v, int num_beautiful) {
    vector<int> next_p = p;
    for (int j = 0; j < num_beautiful; ++j) {
        if (p[j] < k) {
            // b_j[p_j] is a[p_j][beautiful_choices[j][p_j]]
            int required_val = a[p[j]][beautiful_choices[j][p[j]]];
            if (required_val == v) {
                next_p[j]++;
            }
        }
    }
    return next_p;
}

int main() {
    cin >> n >> m >> k;

    l.resize(k);
    for (int i = 0; i < k; ++i) {
        cin >> l[i];
    }

    a.resize(k);
    map<int, int> distinct_values;
    for (int i = 0; i < k; ++i) {
        a[i].resize(l[i]);
        for (int j = 0; j < l[i]; ++j) {
            cin >> a[i][j];
            distinct_values[a[i][j]] = 1;
        }
    }

    vector<int> V;
    for (auto const& [val, _] : distinct_values) {
        V.push_back(val);
    }

    current_choice.resize(k);
    generate_choices(0);

    int num_beautiful = beautiful_choices.size();
    vector<int> start_state(num_beautiful, 0);
    vector<int> final_state(num_beautiful, k);

    map<vector<int>, long long> dp;
    dp[start_state] = 1;

    for (int i = 0; i < n; ++i) {
        map<vector<int>, long long> next_dp;
        for (auto const& [p, count] : dp) {
            if (count == 0) continue;

            // 1. Calculate transitions for v in V
            map<vector<int>, int> transitions_count;
            int values_that_change = 0;
            for (int v : V) {
                vector<int> next_p = transition(p, v, num_beautiful);
                if (next_p != p) {
                    transitions_count[next_p]++;
                    values_that_change++;
                }
            }

            // 2. Add transitions for v in V
            for (auto const& [next_p, num_v] : transitions_count) {
                next_dp[next_p] = (next_dp[next_p] + count * num_v) % MOD;
            }

            // 3. Add transition for x not in V (or v in V that don't change state)
            long long stay_count = (m - values_that_change + MOD) % MOD;
            next_dp[p] = (next_dp[p] + count * stay_count) % MOD;
        }
        dp = next_dp;
    }

    cout << dp[final_state] << endl;

    return 0;
}