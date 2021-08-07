
// 209. Minimum Size Subarray Sum
// https://leetcode.com/problems/minimum-size-subarray-sum/





class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();

        int ans = INT_MAX;

        // best possible answer is 1

        long s = 0;
        int  l;
        int  i = 0;                  // left idx
        for(int j = 0; j < n; ++j) { // right idx
            s += (long)nums[j];
            if( s < (long)target )
                continue;

            // sliding window
            while( i <= j && s >= (long)target ) {
                l = j-i+1;
                if( l == 1 )
                    return 1;
                ans = min(ans,l);

                s -= (long)nums[i];
                ++i;
            }


        }

        return ans == INT_MAX ? 0 : ans;
    }
};
