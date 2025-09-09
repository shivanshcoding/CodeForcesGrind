#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// Ye function alternating sum nikalta hai
// Pattern: a1 - a2 + a3 - a4 + ...
int64 getAlternatingSum(const vector<int64>& arr) {
    int64 total = 0;
    for (int i = 0; i < (int)arr.size(); i++) {
        if (i % 2 == 0) total += arr[i];  // odd position (1-based)
        else total -= arr[i];             // even position (1-based)
    }
    return total;
}

// Agar same parity ke indices (odd-odd ya even-even) swap karte ho,
// alternating sum change nahi hota, sirf cost = (r-l) add hota hai.
// To best gain hamesha max distance hoga between first & last same parity.
int64 getSameParityGain(int n) {
    array<int, 2> first = {-1, -1};
    array<int, 2> last  = {-1, -1};

    for (int i = 0; i < n; i++) {
        int parity = i % 2;
        if (first[parity] == -1) first[parity] = i;
        last[parity] = i;
    }

    int64 best = 0;
    for (int p = 0; p < 2; p++) {
        if (first[p] != -1 && last[p] > first[p]) {
            best = max(best, (int64)(last[p] - first[p]));
        }
    }
    return best;
}

// Agar odd index aur even index swap karte ho,
// alternating sum badal jata hai. Yaha do alag cases hote hain:
//
// 1) jab even index bada ya equal ho odd se (e >= o)
//    gain = (2*a[e] + e) - (2*a[o] + o)
// 2) jab even index chhota ho odd se (e < o)
//    gain = (2*a[e] - e) - (2*a[o] - o)
//
// Dono cases ko handle karke max gain choose karte hain.
int64 getCrossParityGain(const vector<int64>& arr) {
    const int64 INF = (1LL << 60);
    int n = arr.size();
    int64 best = LLONG_MIN;

    // Case 1: e >= o
    int64 minOddExpr = INF;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) { // 1-based odd index
            minOddExpr = min(minOddExpr, 2 * arr[i] + (i + 1));
        } else {          // 1-based even index
            if (minOddExpr < INF) {
                best = max(best, (2 * arr[i] + (i + 1)) - minOddExpr);
            }
        }
    }

    // Case 2: e < o
    int64 maxEvenExpr = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 1) { // 1-based even index
            maxEvenExpr = max(maxEvenExpr, 2 * arr[i] - (i + 1));
        } else {          // 1-based odd index
            if (maxEvenExpr > LLONG_MIN) {
                best = max(best, maxEvenExpr - (2 * arr[i] - (i + 1)));
            }
        }
    }
    return best;
}

// Single testcase solve karne ka function
void solveCase() {
    int n;
    cin >> n;
    vector<int64> arr(n);
    for (auto &val : arr) cin >> val;

    // Step 1: base alternating sum
    int64 base = getAlternatingSum(arr);

    // Step 2: possible gains
    int64 sameGain  = getSameParityGain(n);
    int64 crossGain = getCrossParityGain(arr);

    // Step 3: final best value
    int64 bestGain = max<int64>({0, sameGain, crossGain});
    cout << base + bestGain << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solveCase();
    }
    return 0;
}
