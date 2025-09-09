#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// A helper struct to store a segment
struct Segment {
    int64 left, right;
    Segment(int64 l=0,int64 r=0) : left(l), right(r) {}
};

// Function to compute prefix sums of a vector
vector<int64> computePrefix(const vector<int64>& v) {
    vector<int64> pre(v.size());
    if(!v.empty()) pre[0] = v[0];
    for(size_t i=1;i<v.size();i++) pre[i] = pre[i-1] + v[i];
    return pre;
}

void solve_case() {
    int n;
    cin >> n;
    vector<Segment> segments(n);
    int64 total_base = 0;
    for(int i=0;i<n;i++){
        int64 l,r;
        cin >> l >> r;
        segments[i] = Segment(l,r);
        total_base += (r-l); // base sum of lengths
    }

    // Prepare arrays A = L+R and R values
    vector<int64> A(n), R(n);
    int64 sumR = 0;
    for(int i=0;i<n;i++){
        A[i] = segments[i].left + segments[i].right;
        R[i] = segments[i].right;
        sumR += R[i];
    }

    // Sort indices by A[i] ascending
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i,int j){ return A[i]<A[j]; });

    // Sorted arrays according to order
    vector<int64> A_sorted(n), R_sorted(n);
    for(int i=0;i<n;i++){
        A_sorted[i] = A[order[i]];
        R_sorted[i] = R[order[i]];
    }

    // Prefix sums of sorted A
    vector<int64> prefA = computePrefix(A_sorted);

    int64 max_add = LLONG_MIN;

    if(n%2==0){
        // Even n: pair first half with second half
        int m = n/2;
        int64 sum_small = (m>0 ? prefA[m-1] : 0);
        max_add = sumR - sum_small;
    } else {
        // Odd n: try leaving each segment unpaired
        int m = (n-1)/2;
        for(int skip=0;skip<n;skip++){
            int64 remainingR = sumR - R_sorted[skip];
            int64 sum_small = 0;
            if(m>0){
                if(skip>=m) sum_small = prefA[m-1];
                else sum_small = prefA[m] - A_sorted[skip];
            }
            int64 candidate = remainingR - sum_small;
            max_add = max(max_add, candidate);
        }
    }

    int64 answer = total_base + max<int64>(0,max_add);
    cout << answer << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while(T--) solve_case();

    return 0;
}
