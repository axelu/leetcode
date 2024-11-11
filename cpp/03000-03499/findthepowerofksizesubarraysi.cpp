
// 3254. Find the Power of K-Size Subarrays I
// https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/




class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n == nums.length <= 500

        vector<int> ans;

        // small constraint -> brute force
        for(int i = 0; i <= n-k; ++i) {
            bool is_consecutive = true;
            for(int j = i+1; j < i+k; ++j) {
                if( nums[j-1] + 1 != nums[j] )
                    is_consecutive = false;
            }
            if( is_consecutive )
                ans.push_back(nums[i+k-1]);
            else
                ans.push_back(-1);
        }

        return ans;
    }
};
