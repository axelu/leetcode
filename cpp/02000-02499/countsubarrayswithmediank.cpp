
// 2488. Count Subarrays With Median K
// https://leetcode.com/problems/count-subarrays-with-median-k/




class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        // locate k
        int kpos; // it is guaranteed the nums contains k at least once, and only once
        for(int i = 0; i < n-1; ++i)
            if( nums[i] == k ) {
                kpos = i;
                break;
            }

        int ans = 1;

        if( kpos == 0 ) {
            // we only need to look to the right
            // if nums[i] > k +1, if nums[i] < k -1
            // if we have a sum of 0 or 1, we have a subarray with k being the median
            int rs = 0;
            for(int i = 1; i < n; ++i) {
                rs += nums[i] > k ? 1 : -1;
                if( rs == 0 || rs == 1 )
                    ++ans;
            }

        } else if( kpos == n-1 ) {
            // we only need to look to the left
            // if nums[i] > k +1, if nums[i] < k -1
            // if we have a sum of 0 or 1, we have a subarray with k being the median
            int rs = 0;
            for(int i = n-2; i >= 0; --i) {
                rs += nums[i] > k ? 1 : -1;
                if( rs == 0 || rs == 1 )
                    ++ans;
            }

        } else {
            // build a map of running sum frequencies to the right of k
            unordered_map<int,int> um;
            um[0] = 1;
            int rgt_rs = 0;
            for(int i = kpos+1; i < n; ++i) {
                rgt_rs += nums[i] > k ? 1 : -1;
                if( rgt_rs == 0 || rgt_rs == 1 )
                    ++ans;
                ++um[rgt_rs];
            }
            // now go to the left of kpos and count
            int lft_rs = 0;
            for(int i = kpos-1; i >= 0; --i) {
                lft_rs += nums[i] > k ? 1 : -1;
                ans += um[lft_rs * (-1)];
                ans += um[lft_rs * (-1) + 1];
            }
        }

        return ans;
    }
};
