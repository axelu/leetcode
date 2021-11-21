

// 1658. Minimum Operations to Reduce X to Zero
// https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/


class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        if( n == 1 )
            return nums[0] == x ? 1 : -1;

        long sum = 0;
        for(int i = 0; i < n; ++i)
            sum += (long)nums[i];
        if( sum == x ) return n;
        if( sum <= x ) return -1;

        int r = -1;
        long target = sum - x;
        sum = 0;
        int s = 0;
        for(int i = 0; i < n; ++i) {
            sum += (long)nums[i];
            // sliding window
            if( sum > target )
                while( sum > target && s < i ) {
                    sum -= nums[s];
                    ++s;
                }
            if( sum == target )
                r = max(r,i - s + 1);
        }

        return r != -1 ? n - r : -1;
    }
};
