
// 667. Beautiful Arrangement II
// https://leetcode.com/problems/beautiful-arrangement-ii/


class Solution {
public:
    vector<int> constructArray(int n, int k) {
        // constraint: n and k are in the range 1 <= k < n <= 104
        vector<int> ans(n);
        // edge case k == 1 and n == 2
        // edge case k = 9999 and n == 10000

        ans[0] = 1;
        ans[1] = k+1;
        --k;
        for(int i = 3; i <=n; ++i) {
            if( 0 == k ) {
                ans[i-1] = i;
                continue;
            }
            if( i % 2 ) {
                ans[i-1] = ans[i-2] - k;
            } else {
                ans[i-1] = ans[i-2] + k;
            }
            --k;
        }

        return ans;
    }
};
