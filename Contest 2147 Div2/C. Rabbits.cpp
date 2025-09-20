#include <bits/stdc++.h>
using namespace std;

// bool isZeroSegmentPossible(int firstPos, const vector<bool>& canLeft, const vector<bool>& canRight) {
//     // Returns bitmask of possible placements for a single zero
//     int cur = (canLeft[firstPos] ? 1 : 0) | (canRight[firstPos] ? 2 : 0);
//     return cur;
// }

bool validateSegment(const deque<int>& segment, const vector<bool>& canLeft, const vector<bool>& canRight) {
    // Validate a contiguous segment of zeros with ones in between
    int cur = (canLeft[segment.front()] ? 1 : 0) | (canRight[segment.front()] ? 2 : 0);
    if (!cur) return false;

    for (size_t i = 1; i < segment.size(); ++i) {
        int pos = segment[i];
        int next = 0;
        if ((cur & 1) && canRight[pos]) next |= 2;
        if ((cur & 2) && canLeft[pos]) next |= 1;
        cur = next;
        if (!cur) return false;
    }
    return true;
}

bool cp_solution(const string& s) {
    int n = s.size();
    deque<int> zeros;
    for (int i = 0; i < n; ++i) if (s[i] == '0') zeros.push_back(i);
    if (zeros.empty()) return true;

    vector<bool> canLeft(n, false), canRight(n, false);
    for (int i : zeros) {
        canLeft[i]  = (i == 0) || (s[i-1] == '0') || (i >= 2 && s[i-1] == '1' && s[i-2] == '0');
        canRight[i] = (i == n-1) || (s[i+1] == '0') || (i + 2 < n && s[i+1] == '1' && s[i+2] == '0');
    }

    size_t idx = 0;
    while (idx < zeros.size()) {
        deque<int> segment;
        segment.push_back(zeros[idx]);
        size_t j = idx;
        while (j + 1 < zeros.size() && zeros[j+1] == zeros[j] + 2 && s[zeros[j] + 1] == '1') {
            segment.push_back(zeros[j+1]);
            ++j;
        }

        if (!validateSegment(segment,canLeft, canRight)) return false;
        idx = j + 1;
    }
    return true;
}

void processTestCases() {
    int T;
    if (!(cin >> T)) return;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        cout << (cp_solution(s) ? "YES" : "NO") << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    processTestCases();
    return 0;
}
