#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// This function checks if a ladder of height 'h' is sufficient
// to visit all platforms.
bool check(ll h, int n, const vector<ll>& a) {
    if (n == 0) {
        return true;
    }

    vector<bool> visited(n, false);
    queue<int> q;
    int visited_count = 0;

    // Start a BFS from all platforms reachable from the ground
    for (int i = 0; i < n; ++i) {
        if (a[i] <= h) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
                visited_count++;
            }
        }
    }

    // Explore the graph from the initial set of reachable platforms
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Check left neighbor
        if (u > 0 && !visited[u - 1] && abs(a[u] - a[u - 1]) <= h) {
            visited[u - 1] = true;
            q.push(u - 1);
            visited_count++;
        }

        // Check right neighbor
        if (u < n - 1 && !visited[u + 1] && abs(a[u] - a[u + 1]) <= h) {
            visited[u + 1] = true;
            q.push(u + 1);
            visited_count++;
        }
    }
    
    // If we visited all N platforms, this height is valid.
    return visited_count == n;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll low = 0;
    ll high = 1e9 + 7; // A safe upper bound
    ll ans = high;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (check(mid, n, a)) {
            // This height works, try for a smaller one
            ans = mid;
            high = mid - 1;
        } else {
            // This height is too small, need a larger ladder
            low = mid + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}