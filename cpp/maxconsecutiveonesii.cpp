
// 487. Max Consecutive Ones II
// https://leetcode.com/problems/max-consecutive-ones-ii/





class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();


        int ans = 0;

        // sliding window
        int windowsize      = 0;
        int windowstartidx  = 0;
        int windowzeros     = 0; // number of 0s in the window
        bool has1           = false;

        for(int i = 0; i < n; ++i) {
            ++windowsize;

            if( nums[i] == 0 )
                ++windowzeros;
            else
                has1 = true;

            if( windowzeros > 1 ) {
                // shrink the window
                while( windowsize > 0 ) {
                    if( windowstartidx >= n ) break;
                    if( nums[windowstartidx] == 0 )
                        --windowzeros;
                    ++windowstartidx;
                    --windowsize;
                    if( windowzeros <= 1 ) break;
                }
            }

            ans = max(ans,windowsize);
        }

        return !has1 ? 1 : ans;

    }
};
