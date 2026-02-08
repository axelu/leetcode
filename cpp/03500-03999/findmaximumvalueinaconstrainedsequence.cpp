
// 3796. Find Maximum Value in a Constrained Sequence
// https://leetcode.com/problems/find-maximum-value-in-a-constrained-sequence/


class Solution {
public:
    int findMaxVal(int n, vector<vector<int>>& restrictions, vector<int>& diff) {
        // diff.size() == n-1

        int restr_sz = restrictions.size(); // 1 <= restrictions.length <= n - 1

        // edge case restr_sz == n-1, and we know a[0] has to be 0

        sort(begin(restrictions), end(restrictions));

        // construct a going left to right
        vector<long long> a(n);
        a[0] = 0LL;
        int idx_restr = 0;
        long long pre = 0LL; // a[0] = 0LL;
        for(int i = 1; i < n; ++i) {
            long long addend = diff[i-1];
            long long cand = pre + addend;
            if( idx_restr < restr_sz && restrictions[idx_restr][0] == i ) {
                // the smaller wins
                if( cand > (long long)restrictions[idx_restr][1] )
                    cand = (long long)restrictions[idx_restr][1];
                ++idx_restr;
            }
            a[i] = cand;
            pre = cand;
        }

        // verify a going right to left
        long long mx = a[n-1];
        long long nxt = a[n-1];
        for(int i = n-2; i >= 0; --i) {
            long long addend = diff[i];
            long long cand = a[i+1] + addend;
            if( a[i] > cand )
                a[i] = cand;
            mx = max(mx, a[i]);
        }

        return mx;
    }
};
