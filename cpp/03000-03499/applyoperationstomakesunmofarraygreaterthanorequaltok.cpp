
// 3091. Apply Operations to Make Sum of Array Greater Than or Equal to k
// https://leetcode.com/problems/apply-operations-to-make-sum-of-array-greater-than-or-equal-to-k/




class Solution {
public:
    int minOperations(int k) {
        int ans = k - 1; // worst case

        for(int i = 1; i * 2 <= k; ++i) {
            int t = 1 + i;
            int q = k / t;
            if( k % t )
                ++q;
            ans = min(ans, i + q - 1);
        }

        return ans;
    }
};
