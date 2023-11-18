
// 2897. Apply Operations on Array to Maximize Sum of Squares
// https://leetcode.com/problems/apply-operations-on-array-to-maximize-sum-of-squares/





class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int n = nums.size();
        long mod = 1000000007;

        // the binary operations AND and OR we can perform on pairs
        // will maintain the overall count of set and unset bits
        // example pair 2 8
        //     bit       4 3 2 1 0
        //     8         0 1 0 0 0
        //     2         0 0 0 1 0
        //     8 OR 2    0 1 0 1 0  -> 10
        //     8 AND 2   0 0 0 0 0  ->  0
        // AND operation: off bits of bigger number will move to smaller number
        // OR operation:  on bits of smaller number move to bigger number
        // but key insight: overall count of set bits remains


        // 1 <= nums[i] <= 10^9
        // 10^9 binary: 111011100110101100101000000000 -> 30bits
        int cnt[30];memset(cnt,0,sizeof cnt); // count of set bits per bit position
        for(int x: nums) {
            for(int i = 0; i < 30; ++i) {
                if( x & (1<<i) )
                    ++cnt[i];
            }
        }

        long ans = 0L;

        // make k numbers as big as possible
        // by transferring set bits to them as long as we have any
        for(int i = 0; i < k; ++i) {
            long t = 0;
            for(int j = 0; j < 30; ++j) {
                if( cnt[j] > 0 ) {
                    t |= (1<<j);
                    --cnt[j];
                }
            }
            ans = (ans + ((t*t) % mod)) % mod;
        }

        return ans;
    }
};
