#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
    // DP arrays:
    // [index][prev_digit][prev2_digit][tight_constraint][leading_zeros]
    // 11 is used as a sentinel for "no digit yet"
    long long memoCnt[17][12][12][2][2];
    long long memoSum[17][12][12][2][2];
    string S;

    // Returns {count of valid numbers, sum of waviness}
    pair<long long, long long> dp(int idx, int prev, int prev2, bool tight, bool leading) {
        if (idx == S.size()) {
            // We formed 1 valid number with 0 additional waviness from the "end"
            return {1, 0};
        }

        if (memoCnt[idx][prev][prev2][tight][leading] != -1) {
            return {memoCnt[idx][prev][prev2][tight][leading], memoSum[idx][prev][prev2][tight][leading]};
        }

        long long totalCount = 0;
        long long totalWaviness = 0;

        int limit = tight ? (S[idx] - '0') : 9;

        for (int d = 0; d <= limit; d++) {
            bool next_tight = tight && (d == limit);
            bool next_leading = leading && (d == 0);

            // Determine the next previous values
            int next_prev, next_prev2;

            if (next_leading) {
                // If we are still in leading zeros, history remains empty (10)
                next_prev = 10;
                next_prev2 = 10;
            } else {
                // If we are placing a digit (and not a leading zero):
                // The current 'd' becomes 'prev' for the next step
                // The current 'prev' becomes 'prev2' for the next step
                // If 'prev' was 10 (empty), this is the first digit, so next_prev2 remains 10.
                next_prev = d;
                next_prev2 = (prev == 10) ? 10 : prev;
            }

            // Calculate if placing 'd' creates a peak or valley at 'prev'
            int isWave = 0;
            // We can only form a wave if we have valid history (prev, prev2) 
            // and we are not currently processing leading zeros.
            if (!leading && prev != 10 && prev2 != 10) {
                if (prev > prev2 && prev > d) isWave = 1; // Peak
                if (prev < prev2 && prev < d) isWave = 1; // Valley
            }

            pair<long long, long long> res = dp(idx + 1, next_prev, next_prev2, next_tight, next_leading);

            // Accumulate results
            totalCount += res.first;
            
            // The total waviness is:
            // 1. Waviness coming from the suffix (res.second)
            // 2. Plus the wave formed HERE (isWave) applied to all valid suffixes (isWave * res.first)
            totalWaviness += res.second + (isWave * res.first);
        }

        memoCnt[idx][prev][prev2][tight][leading] = totalCount;
        memoSum[idx][prev][prev2][tight][leading] = totalWaviness;
        
        return {totalCount, totalWaviness};
    }

    long long solve(long long n) {
        if (n < 0) return 0;
        if (n == 0) return 0; // 0 has waviness 0
        
        S = to_string(n);
        
        // Reset DP tables
        // prev and prev2 can go up to 10 (sentinel), tight 0-1, leading 0-1
        memset(memoCnt, -1, sizeof(memoCnt));
        memset(memoSum, -1, sizeof(memoSum));

        // Initial call: idx=0, prev=10, prev2=10, tight=true, leading=true
        return dp(0, 10, 10, true, true).second;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};

int main(){
    Solution s;
    cout<<s.totalWaviness(12,1000000000000000);
}