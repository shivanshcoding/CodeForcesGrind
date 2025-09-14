#include <bits/stdc++.h>
 
using namespace std;

// void solve() {
//     int n, x;
//     cin >> n >> x;

//     int l = 1e5, r = -1;
//     for(int i = 0; i < n; i++) {
//         int door;
//         cin >> door;

//         if(door == 1) {
//             l = min(l, i);
//             r = max(r, i);
//         }
//     }
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct DynBS {
        int bits = 0;
        vector<uint64_t> w;
        static constexpr int W = 64;

        DynBS(int b = 0) { init(b); }
        void init(int b) {
            bits = max(0, b);
            w.assign((bits + W - 1) / W, 0ULL);
        }
        void reset() { fill(w.begin(), w.end(), 0ULL); }
        void setBit(int pos) { w[pos / W] |= (1ULL << (pos % W)); }
        bool test(int pos) const { return (w[pos / W] >> (pos % W)) & 1ULL; }
        void maskLast() {
            int rem = bits % W;
            if (rem && !w.empty()) w.back() &= ((1ULL << rem) - 1ULL);
        }

        void orWith(const DynBS &other) {
            size_t m = min(w.size(), other.w.size());
            for (size_t i = 0; i < m; ++i) w[i] |= other.w[i];
            maskLast();
        }

        void orShiftedFrom(const DynBS &src, int shift) {
            if (shift <= 0) {
                if (shift == 0) orWith(src);
                return;
            }
            if (shift >= bits) return;
            int wordShift = shift / W;
            int bitShift = shift % W;
            size_t nw = w.size();
            for (size_t i = 0; i < src.w.size(); ++i) {
                uint64_t v = src.w[i];
                if (v == 0) continue;
                size_t j = i + wordShift;
                if (j < nw) {
                    w[j] |= (v << bitShift);
                }
                if (bitShift != 0 && j + 1 < nw) {
                    w[j + 1] |= (v >> (W - bitShift));
                }
            }
            maskLast();
        }
    };

public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        auto zolvarinte = nums;

        int n = (int)nums.size();
        if (n == 0) return {};

        DynBS base(k + 1);
        base.reset();
        base.setBit(0);

        vector<int> cnt(n + 1, 0);
        for (int v : nums) if (v >= 0 && v <= n) ++cnt[v];

        vector<DynBS> pref(n + 1, DynBS(k + 1));
        DynBS dp = base;
        pref[0] = dp;

        auto addCopies = [&](DynBS &target, int weight, int copies) {
            long long p = 1;
            while (copies > 0) {
                int take = (int)min<long long>(p, copies);
                int shift = weight * take;
                if (shift <= k) {
                    DynBS snapshot = target;
                    target.orShiftedFrom(snapshot, shift);
                }
                copies -= take;
                p <<= 1;
            }
        };

        for (int v = 1; v <= n; ++v) {
            if (cnt[v] > 0) addCopies(dp, v, cnt[v]);
            pref[v] = dp;
        }

        vector<int> suf(n + 2, 0);
        for (int v = n; v >= 1; --v) suf[v] = suf[v + 1] + cnt[v];

        vector<bool> ans(n, false);
        for (int x = 1; x <= n; ++x) {
            DynBS cur = pref[x];
            int extra = suf[x + 1];
            if (extra > 0) addCopies(cur, x, extra);
            ans[x - 1] = (k <= cur.bits) ? cur.test(k) : false;
        }

        return ans;
    }
};



int main() {
    Solution s;
    vector<int> v = {4,3,2,4};
    vector<bool> ans = s.subsequenceSumAfterCapping(v,3);
    for(bool v: ans){
        cout<<v<<" ";
    }
}